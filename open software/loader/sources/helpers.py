# Some helper functions for KADE Loader program
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
# (helpers.py)
#
# KADE Loader by Jon Wilson
# A firmware loader and configuration tool for KADE - Kick Ass Dynamic Encoder
#
# Copyright (c) 2013 
# Jon Wilson    - degenatrons@gmail.com
# Bruno Freitas - bootsector@ig.com.br
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
import os
import sys
import subprocess
from sqlite3 import dbapi2 as sqlite
from urllib2 import urlopen, HTTPError
from webbrowser import open as browse

def execute(mode, command):
  success = True
  from win32process import CREATE_NO_WINDOW
  out = open("NUL","w")
  p = subprocess.Popen(command, stdout=out, stderr=subprocess.PIPE, creationflags = CREATE_NO_WINDOW)
  stdout, stderr = p.communicate()
  if p.returncode != 0:
    success = False
    log(stderr.splitlines())
  return success

def b2i(bool):
  return (False, True).index(bool)

def get_title(beta=False):
  return 'Kade Loader %s(version %s)' % (("","BETA ")[b2i(beta)], get_installed_version())

def get_installed_version():
  try:
    with open(get_path("VERSION"), 'r') as f:
      read_data = f.read()
    f.closed      
    version = read_data.split("\n")[1]
  except IOError:
    version = 'Unknown'
  return version

def get_latest_version(beta=False):  
  try:
    version_file = "http://kadevice.com/loader/" + ("version_public.txt", "version.txt")[b2i(beta)]
    latest = urlopen(version_file, None, 2.5).read().split()[0].replace(" ","")
    if not latest.replace(".","").isdigit():
      latest = "0.0.0.0"
  except:
    latest = "0.0.0.0"
  return latest

def sql_command(sql, commit=False):
  con = sqlite.connect(get_path("DATA"))
  cursor = con.cursor()
  cursor.execute( sql )
  result = cursor.fetchall()
  if commit: 
    con.commit()
  con.close()
  return result

def sql_single(sql):
  data = sql_command(sql)
  if data:
    value = data[0][0]
  else:
    value = ""
  return value

def get_message(messageID):
  return sql_single('SELECT msgtext FROM messages WHERE id = "%s"' % messageID)

def read_param(key):
  return sql_single('SELECT value FROM parameters WHERE key = "%s"' % key)

def write_param(key, value):
  sql_command('UPDATE parameters SET value = "%s" WHERE key = "%s"' % (value, key), True)

def get_path(name="ROOT"):  
  #This is the ROOT (and default)
  location = os.environ['ALLUSERSPROFILE']
  if '\\Documents and Settings' in location: 
    location = os.path.join(location,'Application Data')
  location = os.path.join(location,'Kade Loader')
  
  #These are ROOT subfolders
  if name == "DATA":     
    location = os.path.join(location, "data")
  elif name == "VERSION":  
    location = os.path.join(location, "version")    
  elif name == "NOCHECK":  
    location = os.path.join(location, "nocheck")
  elif name == "BETA":  
    location = os.path.join(location, "beta")
  elif name == "AVR":      
    location = "programmer\\avrdude\\avrdude"
  elif name == "DFU":      
    location = "programmer\\dfu\\dfu-programmer"
  elif name == "BLH":      
    location = "programmer\\bootloadHID\\commandline\\bootloadHID"
  elif name == "USERDOCS":
    #this is not under ROOT
    location = os.environ['HOMEPATH']
    for path in (os.path.join(location, "documents"), os.path.join(location, "my documents")):
      if os.path.exists(path): 
        location = path
        break
  return location

def open_file(path):
  if os.path.exists(path):			
    os.startfile(path)
  
def delete_file(filename):
  try:
    os.remove(filename)
  except:
    pass  

def copy_file(src, dst):
  from subprocess import call
  try:
    call('copy /Y "'+ src + '" "' + dst + '"', shell=True)
  except:
    pass
def mkdir(dir_path):
  try: 
    os.mkdir(dir_path)
  except: 
    pass

def rmdir(dir_path):
  try: 
    os.rmdir(dir_path)
  except: 
    pass
    
def get_template(firmware, filetype, extended=None):
  system = firmware.split("-")[1]
  if filetype == 'HTML':
    template = 'templates\\mapping_template.htm'
    if extended:
      template = 'templates\\mapping_template_extended.htm'      
    with open(template, 'r') as f:
      read_data = f.read().replace("{system}", system)
    f.closed  
  else:
    with open('templates\\xml\\%s.%s' % (firmware, filetype), 'r') as f:
      read_data = f.read()
    f.closed  
  return read_data

def read_xml(xml, field, shifted=False):
  value = 0
  try:
    if shifted:
      xml = xml[xml.find("<SHIFTED>"):]
    p1 = xml.find(">",xml.find("<%s>" % field))+1
    p2 = xml.find("<",p1)
    if p1 > 0 and p2 > 0:
      value = int(xml[p1:p2])
  except:
    value = 0
  return value    

def get_pins(family="minimus"):
  pins = sql_command('SELECT pins_normal, pins_shifted, pins_all FROM families WHERE family = "%s"' % family)
  if pins:
    return pins[0][0], pins[0][1], pins[0][2]
  else:
    return "","",""

def get_firmware_title(firmware):
  desc = sql_single('SELECT desc FROM firmwares WHERE name = "%s"' % firmware)
  return (desc,"Unknown")[b2i(desc=="")]

def get_firmware_notes(firmware):
  return sql_single('SELECT notes FROM firmwares WHERE name = "%s"' % firmware)

def get_reserved(firmware):
  return sql_command('SELECT pin, class, description FROM reserved WHERE firmware = "%s"' % firmware)

def generate_html(firmware, mappings, extra=None, extended=None):
  pin_labels = get_pins()[2].split(",")
    
  user_html_file = os.path.join(get_path("ROOT"), "%s.htm" % firmware)  
  html = get_template(firmware, "HTML", extended)
  html = html.replace("{title}",get_firmware_title(firmware))
  html = html.replace("{notes}",get_firmware_notes(firmware))
  for rsv in get_reserved(firmware):
    html = html.replace('{%sC}' % rsv[0], 'class="%s"' % rsv[1])    
    html = html.replace('{%sM}' % rsv[0], 'No')    
    html = html.replace('{%s}' % rsv[0], rsv[2])      

  #Handle any extra settings
  if extra:
    #Reserve trackball lines if they are enabled          
    if int(extra[3]) == 1: 
      html = html.replace('{A3C}', 'class="input"')    
      html = html.replace('{A7C}', 'class="input"')    
      html = html.replace('{A3}','Trackball/Mouse 1: DATA Line')
      html = html.replace('{A7}','Trackball/Mouse 1: CLOCK Line')
    if int(extra[4]) == 1: 
      html = html.replace('{A4C}', 'class="track"')    
      html = html.replace('{A8C}', 'class="track"')    
      html = html.replace('{A4}','Trackball/Mouse 2: DATA Line')
      html = html.replace('{A8}','Trackball/Mouse 2: CLOCK Line')
    
  for pin in mappings: html = html.replace('{%s}' % pin_labels[pin[0]-1], pin[2])      
  for pin in pin_labels: html = html.replace('{%sC}' % pin, '')
  for pin in pin_labels: html = html.replace('{%sM}' % pin, 'Yes')
  for pin in pin_labels: html = html.replace('{%s}' % pin, '')
  
  #show extended mappings (if there are any)
  if extended:
    desc = sql_command('SELECT long_description FROM library WHERE system = "%s"' % firmware)
    ext_pins = 'P1_1','P1_2','P1_3','P2_1','P2_2','P2_3','P3_1','P3_2','P3_3','P4_1','P4_2','P4_3','P1_1S','P1_2S','P1_3S','P2_1S','P2_2S','P2_3S','P3_1S','P3_2S','P3_3S','P4_1S','P4_2S','P4_3S'
    cnt = 0
    for pin in ext_pins:
      html = html.replace('{%s}' % pin, desc[extended[cnt]][0])
      cnt += 1
  else:
    html = html.replace('{%s}' % pin, '')
  
  html = html.replace("(Unused)", "")
      
  f = open(user_html_file, 'w') 
  f.write(html)
  f.close()   
  return user_html_file

def write_data_keys(datafile, records):
  """write 2 columns of pipe delimited data to a file: key and data"""
  f = open(datafile, 'w') 
  for record in records:
    f.write("%s|%s\n" % (record[0], record[1]))
  f.close()         

def read_data_keys(datafile):
  """return data from a pipe delimited data to a file: key and data"""
  records = []
  if os.path.exists(datafile):
    with open(datafile, 'r') as f:
      read_data = f.read()
    f.closed  
    for record in read_data.split():
      records.append((record.split("|")[0], record.split("|")[1]))    
  return records

def donate_link():
  browse("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=EXQQ6WC5VR666")
  
def program_label(family):
  return "Program %s with Selected Firmware" % ("Device", "KADE")[b2i(family=="minimus")]

def log(text):
  success = True
  try:
    with open(get_path("LOG"), "a") as f:
      f.write(stderr.splitlines())
  except:
    success = False
  return success

def call_keyboard_test():
  if os.path.exists("dist\keytest.exe"):  #dev environment      
    open_file("dist\keytest.exe")
  else:
    open_file("keytest.exe")