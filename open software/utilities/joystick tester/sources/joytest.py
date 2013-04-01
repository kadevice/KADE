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
# (joytest.py)
#
# Joystick Input Tester by Jon Wilson
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
import os
import wx
import gui

import pygame

class joyTest( gui.joytest ):
  def __init__( self, parent ):
    gui.joytest.__init__( self, parent )  

    try:
      pygame.init()
      self.stick = pygame.joystick.Joystick(0)
      self.stick.init()
      print "USB joystick detected"      
    except pygame.error:
      print "USB joystick was not detected"
        
    self.timer = wx.Timer(self)
    self.Bind(wx.EVT_TIMER, self.update, self.timer)       
    self.timer.Start(milliseconds=500, oneShot=True)

  def plot(self, pos):
    return int((pos+1)*72)
    
  def update(self, event):
    #load images
    dpad_none  = wx.Image("images\\dpad_none.gif", wx.BITMAP_TYPE_GIF)
    dpad_left  = wx.Image("images\\dpad_left.gif", wx.BITMAP_TYPE_GIF)
    dpad_right = wx.Image("images\\dpad_right.gif", wx.BITMAP_TYPE_GIF)
    dpad_up    = wx.Image("images\\dpad_up.gif", wx.BITMAP_TYPE_GIF)
    dpad_down  = wx.Image("images\\dpad_down.gif", wx.BITMAP_TYPE_GIF)
    dpad_ul    = wx.Image("images\\dpad_ul.gif", wx.BITMAP_TYPE_GIF)
    dpad_ur    = wx.Image("images\\dpad_ur.gif", wx.BITMAP_TYPE_GIF)
    dpad_dl    = wx.Image("images\\dpad_dl.gif", wx.BITMAP_TYPE_GIF)
    dpad_dr    = wx.Image("images\\dpad_dr.gif", wx.BITMAP_TYPE_GIF)
    
    #set default dpad direction
    direction  = dpad_none
    last_direction = dpad_none
    
    try:
      while True:      
        pygame.event.pump()
                
        #get Dpad -------------------------------------------------
        dpad = self.stick.get_hat(0)
        if dpad[0] != 0 or dpad[1] != 0:
          print 'Dpad %i: x=%i, y=%i' % (i, dpad[0], dpad[1])
          if dpad[1] == 1: 
            if dpad[0] == -1: 
              direction = dpad_ul
            elif dpad[0] == 1: 
              direction = dpad_ur
            else:
              direction = dpad_up
          elif dpad[1] == -1: 
            if dpad[0] == -1: 
              direction = dpad_dl
            elif dpad[0] == 1: 
              direction = dpad_dr
            else:
              direction = dpad_down
          elif dpad[0] == -1:
            direction = dpad_left
          elif dpad[0] == 1:
            direction = dpad_right
        else:
          direction = dpad_none
          
        if direction != last_direction:
          self.m_dpad.SetBitmap(wx.BitmapFromImage(direction))   
        last_direction = direction
            
        #get analog sticks ----------------------------------------
        a0, a1, a2, a3 = 0,0,0,0
        for i in range(0, self.stick.get_numaxes()):        
          axis = float("{0:.2f}".format(self.stick.get_axis(i)))
          if i == 0: a0 = axis
          if i == 1: a1 = axis
          if i == 2: a2 = axis
          if i == 3: a3 = axis
                    
          if axis != 0:
            print 'Axis %i = %s' % (i, axis)

        self.m_pointer1.SetPosition((self.plot(a0),self.plot(a1)))
        self.m_pointer2.SetPosition((self.plot(a2),self.plot(a3)))
            
        #get buttons -------------------------------------------------
        button_list = self.m_1, self.m_2, self.m_3, self.m_4, self.m_5, self.m_6, \
          self.m_7, self.m_8, self.m_9, self.m_10, self.m_11, self.m_12, self.m_13
        
        for i in range(0, self.stick.get_numbuttons()):
          button = self.stick.get_button(i)
          if abs(button) != 0:
            print 'Button %i = %i' % (i, button)

          
          if abs(button) != 0 and i < 13:
            button_list[i].SetBackgroundColour(wx.Colour(204,0,0))
            button_list[i].SetForegroundColour(wx.WHITE)
          else:
            button_list[i].SetBackgroundColour(wx.Colour(240,240,240))
            button_list[i].SetForegroundColour(wx.Colour(112,112,112))
            

    except:
      pass
    
    
    

#==========================================================================================
# Main

def main():
  app = wx.App(False)
  joyTest(None).Show()
  app.MainLoop()
  app.Destroy()

if __name__ == "__main__":
  main()