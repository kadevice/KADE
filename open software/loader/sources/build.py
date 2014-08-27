# Build program for KADE Loader
# "python build.py py2exe" - at the command line
#------------------------------------------------------------------------------
#
#      .k8GOGGNqkSFS5XkqXPSkSkkqXXFS5kSkSS15U22F2515U2uujuu1U1u2U1U2uUuFS.     
#    :0qE     JS5uuJuuFFX51jU2SSk12jU2SSXF5uuu15SFS5k12ujj21S5kFS5S12jJYu11    
#   5XS:        1UYYLu.   vUUX    U22r     SUF         SUF           ;YYLuU5   
#  1F5i  NNSkS7  2uLJui   51u     S5.      .PX         .XX           LJvLLu1.  
#  kUk  0iLk5FFu vuYY2:   5F    Xkk7        78    E0    i0    GEXPXk2uLLvLLuk  
# X25, 8O   2kX0  5YJUi   M    555    PkXk   i    q1FU   7    ONNkP12YLvLvLYS  
# S25  8888  888  5uY5         FuS    PS50   .    FuUU   7          uJvLvLLJ2i 
# kUF             SJjU.      P02UF    P25k   .    Su2Y   v          2LLvLvLL17 
# S21  XJj88  0u  1uY2.        X2k           .    k11E   v    7;ii:JuJvLvLvJ2: 
# 2257 jqv   Pqq  1LJur         PP.          7    EX:    q    OqqXP51JYvLvYYS.  
#  X2F  kXkXSXk  kJYLU:   O     ,Z    0PXZ   i    ii    q0    i:::,,.jLLvLLuF'  
#  ik1k  ;qkPj  .uJvYu:   UN      :   XU2F   :         S5S           iJLLvjUF8   
#   :PSq       72uLLLui   uSi    .;   2uY1   r.       72j1           LYYLYJSU88
#     XqE2   rP12juJuu1FX55U5FqXXSXkXF1juUkkPSXSPXPXPF1Jju5FkFSFXFSF5uujUu5j28V
#       .uGOZESS5S5SFkkPkPkXkPXqXPXqXXFkSkkPXPXPkqSkSS1521252121U2u2u12Suv7 
#
# (build.py)
#
# KADE Loader by Jon Wilson
# A firmware loader and configuration tool for KADE - Kick Ass Dynamic Encoder
#
# Copyright (c) 2013 
# Jon Wilson    - degenatrons@gmail.com
# Bruno Freitas - bruno@brunofreitas.com
# Kevin Mackett - kevin@sharpfork.com
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#
# ADDITIONAL TERMS per GNU GPL Section 7
# No trademark or publicity rights are granted. This license does NOT give you 
# any right, title or interest in the KADE brand. You may not distribute any 
# modification of this program using the KADE name or KADE logo or claim any 
# affiliation or association with KADE or the KADE development team.
#
# Any propagation or conveyance of this program must include this copyright 
# notice and these terms.
#
# You may not misrepresent the origins of this program; modified versions of the 
# program must be marked as such and not identified as the original program.
import warnings
warnings.filterwarnings("ignore")
from distutils.core import setup
from sqlite3 import dbapi2 as sqlite
import shutil
import py2exe
import os
import glob   

def sql_command(sql):
  con = sqlite.connect("data")
  cursor = con.cursor()
  cursor.execute( sql )		
  result = cursor.fetchall()
  con.commit()
  con.close()
  return result

def import_hex(key, hex_path, test=False):
  if os.path.exists(hex_path):
    with open(hex_path, 'r') as f:
      data = f.read()
      f.closed
    print "Updating %s" % key
    if test:
      sql_command('UPDATE firmwares SET hex_test = "%s" WHERE name = "%s"' % (data, key))
    else:
      sql_command('UPDATE firmwares SET hex = "%s" WHERE name = "%s"' % (data, key))
      
def generate_keymaps(firmware, out_path):
  f = open(out_path,'w')
  f.write('//Generated %s key mappings\n' % firmware)
  library = sql_command('SELECT * FROM library WHERE system = "%s"' % firmware)
  for func in library:
    f.write('if (ass[pos]==%s){keyboard_keys[keycount++] = %s;}\n' % (func[1], func[5]))
  f.close()
      
def refresh_params():
  sql_command('UPDATE parameters SET value = ""')  

#start with clean dist subfolders
if os.path.exists('dist\\programmer'): os.system('rmdir dist\\programmer /S /Q')
if os.path.exists('dist\\documents'): os.system('rmdir dist\\documents /S /Q')
if os.path.exists('dist\\templates'): os.system('rmdir dist\\templates /S /Q')
if os.path.exists('dist\\images'): os.system('rmdir dist\\images /S /Q')
os.system('del dist\\*.exe')

#miniArcade Sources-------------------------------------------
sources_folder = "..\\..\\firmwares\\KADE miniArcade\\sources"

#generate key mappings for keyboard based firmwares -to do: add other firmwares
generate_keymaps("kade-rotary-custom", os.path.join(sources_folder, "kade-rotary-custom\\keymaps.c"))

#import latest hex into DB before building
import_hex("kade-mame",          os.path.join(sources_folder, "kade-mame\\KADE-MAME.hex"))
import_hex("kade-mame-2p",       os.path.join(sources_folder, "kade-mame-2p\\KADE-MAME-2P.hex"))
import_hex("kade-gen",           os.path.join(sources_folder, "kade-gen\\KADE-GEN.hex"))
import_hex("kade-icade",         os.path.join(sources_folder, "kade-icade\\KADE-iCADE.hex"))
import_hex("kade-rotary-custom", os.path.join(sources_folder, "kade-rotary-custom\\KADE-ROTARY-CUSTOM.hex"))
import_hex("kade-led-demo",      os.path.join(sources_folder, "kade-led-demo\\kade-led-demo.hex"))
import_hex("kade-pin-custom",    os.path.join(sources_folder, "kade-pin-custom\\KADE-PIN-CUSTOM.hex"))
import_hex("kade-xbox-custom",   os.path.join(sources_folder, "kade-xbox-custom\\KADE-XBOX-CUSTOM.hex"))
import_hex("kade-ps3-custom",    os.path.join(sources_folder, "kade-ps3-custom\\KADE-PS3-CUSTOM.hex"))
import_hex("kade-joy-custom",    os.path.join(sources_folder, "kade-ps3-custom\\KADE-PS3-CUSTOM.hex"))
import_hex("kade-psx-custom",    os.path.join(sources_folder, "kade-psx-custom\\KADE-PSX-CUSTOM.hex"))
import_hex("kade-mame-custom",   os.path.join(sources_folder, "kade-mame-custom\\KADE-MAME-CUSTOM.hex"))
import_hex("kade-mame-extended", os.path.join(sources_folder, "kade-mame-extended\\KADE-MAME-EXTENDED.hex"))
import_hex("kade-key-custom",    os.path.join(sources_folder, "kade-key-custom\\KADE-KEY-CUSTOM.hex"))
import_hex("kade-track-usbjoy",  os.path.join(sources_folder, "kade-trackball-usbjoy\\kade-trackball-usbjoy.hex"))
import_hex("kade-track-mouse",   os.path.join(sources_folder, "kade-trackball-mouse\\kade-trackball-mouse.hex"))

#third-party hex
import_hex("kade-ps360",         os.path.join(sources_folder, "third-party\\ps360_plus\\OfficialVer1.3.hex"))
import_hex("kade-dualstrike",    os.path.join(sources_folder, "third-party\\dualstrike\\dual_strike_firmware_atmega168_V3.3.1.hex"))
import_hex("kade-dualstrikeSMD", os.path.join(sources_folder, "third-party\\dualstrike\\dual_strike_firmware_atmega168_smd_V3.3.1.hex"))

#import blink tests
import_hex("kade-test-m",        os.path.join(sources_folder, "tests\\minimus\\KADE-TEST-M.hex"))
import_hex("kade-test-a",        os.path.join(sources_folder, "tests\\arduino\\KADE-TEST-A.hex"))

#import test hex - were relevant
import_hex("kade-xbox-custom",   os.path.join(sources_folder, "kade-xbox-custom\\KADE-XBOX-CUSTOM-T.hex"),True)

#import EZ-programming hex
import_hex("kade-program",       os.path.join(sources_folder, "kade-program\\KADE-PROGRAM.hex"))

#maxArcade Sources-------------------------------------------
sources_folder = "..\\..\\firmwares\\KADE maxArcade\\sources"

#import maxArcade hex
import_hex("kade-mamex4",        os.path.join(sources_folder, "mamex4\\KADE-MAMEx4.hex"))
import_hex("kade-usbhidx2",      os.path.join(sources_folder, "usbhidx2\\KADE-USBHIDx2.hex"))
import_hex("kade-usbhidx4",      os.path.join(sources_folder, "usbhidx4\\KADE-USBHIDx4.hex"))

#clear the parameters
refresh_params()

#copy folder structure
shutil.copytree("programmer", "dist\\programmer")
shutil.copytree("documents", "dist\\documents")
shutil.copytree("templates", "dist\\templates")

#now go build
setup(
  data_files = [(r'images', glob.glob(r'images\\*')),
                (r'', glob.glob(r'data')),
                (r'', glob.glob(r'version.txt')),
                (r'', glob.glob(r'release.txt')),
                (r'', glob.glob(r'license.txt')),
                (r'', glob.glob(r'kp.exe')),
                (r'', glob.glob(r'dpinst.exe')),
                (r'', glob.glob(r'dpinst64.exe')),
                (r'', glob.glob(r'loader.ico')),
                (r'', glob.glob(r'kade.jpg'))],

  options={"py2exe": {"compressed": 1,
                      "dll_excludes": ['powrprof.dll', 'mswsock.dll'], # To resolve XP Issue
                      "bundle_files": 2}},

  zipfile = None,
  windows=[{"script":'loader.py', 'icon_resources':[(0, 'images\\icons.ico')]}]
)

#post steps to clean up unwanted files...
if os.path.exists('build'): os.system('rmdir build /S /Q')