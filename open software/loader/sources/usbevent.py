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
# (usbevent.py)
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
import win32api
import win32con
import win32gui
import time
import wx
from ctypes import *
from helpers import *

WORD = c_ushort
DWORD = c_ulong

class DEV_BROADCAST_HDR (Structure):
  _fields_ = [
    ("dbch_size", DWORD),
    ("dbch_devicetype", DWORD),
    ("dbch_reserved", DWORD)
  ]

class Notification:

  def __init__(self, gui):
    self.clock = time.clock()
    
    message_map = {
      win32con.WM_DEVICECHANGE : self.onDeviceChange
    }
    self.gui = gui
    wc = win32gui.WNDCLASS ()
    hinst = wc.hInstance = win32api.GetModuleHandle (None)
    wc.lpszClassName = "USBDeviceChange"
    wc.lpfnWndProc = message_map
    classAtom = win32gui.RegisterClass (wc)
    style = win32con.WS_OVERLAPPED | win32con.WS_SYSMENU
    self.hwnd = win32gui.CreateWindow (
      classAtom,
      "Device Change",
      style,
      0, 0,
      win32con.CW_USEDEFAULT, win32con.CW_USEDEFAULT,
      0, 0,
      hinst, None
    )

  def detect(self, initial=False):
    #show activity
    try:
      self.gui.m_usb.SetLabel("--- Detecting USB ---")
      image = wx.Image("images\\usb_on.png", wx.BITMAP_TYPE_PNG)
      self.gui.m_usb_icon.SetBitmap(wx.BitmapFromImage(image))            
    except:
      #v1.1.0.0 - catch unknown error when attempting to load hex for an uninitialised device
      pass
    
    #limit to one event every 2 seconds
    self.clock = time.clock() - 2
    
    #USB device inserted/removed so check to see if we know what is connected
    #check for AVR
    #If device is different to the one selected then popup message and change
    if not os.path.exists(get_path("BETA")):
      boards = sql_command('SELECT name, product FROM boards WHERE public = "True" AND detect = "True"')
    else:
      boards = sql_command('SELECT name, product FROM boards WHERE detect = "True"')
    connected = False
    for board in boards:
      check = execute("check",'"%s" %s get family' % (get_path("DFU"), board[1]) )
      if check:
        
        connected = True
        self.gui.m_usb.SetLabel("%s connected" % board[0])
        #do we need to change board option
        if board[0] != self.gui.m_choice.GetStringSelection():
          self.gui.m_choice.SetStringSelection(board[0])   
          self.gui.updateBoards(notify=not(initial))
        time.sleep(2)
        image = wx.Image("images\\usb_on.png", wx.BITMAP_TYPE_PNG)
        self.gui.m_usb_icon.SetBitmap(wx.BitmapFromImage(image))                        
        break
    if not connected:
      self.gui.m_usb.SetLabel("")          
      image = wx.Image("images\\usb_off.png", wx.BITMAP_TYPE_PNG)
      self.gui.m_usb_icon.SetBitmap(wx.BitmapFromImage(image))            
    
    
  def onDeviceChange (self, hwnd, msg, wparam, lparam):
    dev_broadcast_hdr = DEV_BROADCAST_HDR.from_address (lparam)
    if wparam == 7:
      if (time.clock() - self.clock) > 2:
        self.detect()
      
