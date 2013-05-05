# Build program for Keyboard Test Utility
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
# Keyboard Test Utility by Jon Wilson
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
import warnings
warnings.filterwarnings("ignore")
from distutils.core import setup
import shutil
import py2exe
import os
import glob   

setup(
    data_files = [(r'images', glob.glob(r'images\\*')),
                  (r'', glob.glob(r'version.txt')),
                  (r'', glob.glob(r'readme.txt')),
                  (r'', glob.glob(r'license.txt')),
                  (r'', glob.glob(r'saystatic.exe')),
                  (r'', glob.glob(r'kade.jpg'))],
    
    options = {"py2exe": {"compressed": 1,
                          "bundle_files": 2}},
    zipfile = None,
    windows=[{"script":'keytest.py', 'icon_resources':[(0, 'images\\icons.ico')]}]
)

#post steps to clean up unwanted files...
if os.path.exists('build'): os.system('rmdir build /S /Q')