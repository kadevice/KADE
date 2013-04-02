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
# (trackball.py)
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
# program must be marked as such and not identified as the original program.import os
import sys
import wx
import gui
from helpers import *

class kadeTrackballs( gui.trackball ):
  def __init__( self, parent, family=None ):
    gui.trackball.__init__( self, parent )
    self.family = family

    self.track_file = os.path.join(get_path("ROOT"),"track.dat")
    if os.path.exists(self.track_file):
      for record in read_data_keys(self.track_file):
        if record[0] == "trackball1-trackball": 
          self.m_trackball1.SetValue(record[1]=="True")
        if record[0] == "trackball1-spinner":   
          self.m_spinner1.SetValue(record[1]=="True")
        if record[0] == "trackball1-mouse":     
          self.m_mouse1.SetValue(record[1]=="True")
        if record[0] == "trackball1-counts":    
          self.m_counts1.SetSelection(int(record[1]))
        if record[0] == "trackball1-samples":   
          self.m_samples1.SetSelection(int(record[1]))
        if record[0] == "trackball2-trackball": 
          self.m_trackball2.SetValue(record[1]=="True")
        if record[0] == "trackball2-spinner":   
          self.m_spinner2.SetValue(record[1]=="True")
        if record[0] == "trackball2-mouse":     
          self.m_mouse2.SetValue(record[1]=="True")
        if record[0] == "trackball2-counts":    
          self.m_counts2.SetSelection(int(record[1]))
        if record[0] == "trackball2-samples":   
          self.m_samples2.SetSelection(int(record[1]))
    else:
      #use default values
      self.m_trackball1.SetValue(True)
      self.m_spinner1.SetValue(False)
      self.m_mouse1.SetValue(False)
      self.m_counts1.SetSelection(3)
      self.m_samples1.SetSelection(6)
      self.m_trackball2.SetValue(True)
      self.m_spinner2.SetValue(False)
      self.m_mouse2.SetValue(False)
      self.m_counts2.SetSelection(3)
      self.m_samples2.SetSelection(6)        
        
  def onTrackball1(self, event):
    self.m_samples1.SetSelection(6)
    self.m_counts1.SetSelection(3)
                
  def onTrackball2(self, event):
    self.m_samples2.SetSelection(6)
    self.m_counts2.SetSelection(3)

  def onSpinner1(self, event):
    self.m_samples1.SetSelection(5)
    self.m_counts1.SetSelection(2)
                
  def onSpinner2(self, event):
    self.m_samples2.SetSelection(5)
    self.m_counts2.SetSelection(2)

  def onMouse1(self, event):
    self.m_samples1.SetSelection(6)
    self.m_counts1.SetSelection(0)
                
  def onMouse2(self, event):
    self.m_samples2.SetSelection(6)
    self.m_counts2.SetSelection(0)
    
  def onOK(self, event):
    records = []
    records.append(("trackball1-counts",    self.m_counts1.GetSelection()))
    records.append(("trackball1-samples",   self.m_samples1.GetSelection()))
    records.append(("trackball1-trackball", self.m_trackball1.GetValue()))
    records.append(("trackball1-spinner",   self.m_spinner1.GetValue()))
    records.append(("trackball1-mouse",     self.m_mouse1.GetValue()))
    records.append(("trackball2-counts",    self.m_counts2.GetSelection()))
    records.append(("trackball2-samples",   self.m_samples2.GetSelection()))
    records.append(("trackball2-trackball", self.m_trackball2.GetValue()))
    records.append(("trackball2-spinner",   self.m_spinner2.GetValue()))
    records.append(("trackball2-mouse",     self.m_mouse2.GetValue()))
    write_data_keys(self.track_file, records)
    self.Destroy()
    
  def onCancel(self, event):
    self.Destroy()    


class kadeTrackballInputs( gui.trackball_inputs ):
  def __init__( self, parent, name, trackball_choices, keys, maps ):
    gui.trackball_inputs.__init__( self, parent )
    self.Title = "Assign Device Inputs for %s" % name
    self.normal = self.BUT1, self.BUT2, self.BUT3
    self.shifted = self.BUT1s, self.BUT2s, self.BUT3s           
    
    #load values
    self.m_left.SetValue(maps[0]==0)
    self.m_right.SetValue(maps[0]==1)
    i = 1
    for control in self.normal: 
      control.SetItems(trackball_choices)
      control.SetSelection(keys.index(maps[i]))
      i += 1            
    for control in self.shifted: 
      control.SetItems(trackball_choices)  
      control.SetSelection(keys.index(maps[i]))
      i += 1

  def onChoice(self, event):
    #restricted functions for trackball buttons
    for control in self.normal + self.shifted:
      if "dpad"      in control.GetStringSelection().lower() or \
         "auto fire" in control.GetStringSelection().lower():
        control.SetSelection(0)
        msg = wx.MessageDialog(None, 'Some functions are not available as trackball buttons.\nDpad and Auto-Fire are not implemented', \
          'Function not available on trackball/mouse', wx.OK | wx.ICON_INFORMATION)      
        msg.ShowModal()

  def onClear(self, event):
    for control in self.normal + self.shifted:
      control.SetSelection(0)

  def onConfigure(self, event):
    trackballs = kadeTrackballs(None)
    trackballs.ShowModal()
    trackballs.Destroy()            
      
  def onOK(self, event):
    self.Destroy()
    
  def onCancel(self, event):
    self.Destroy()      
