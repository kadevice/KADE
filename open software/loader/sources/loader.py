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
# (loader.py)
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
import wx
import gui
import tempfile
import time
import subprocess
from trackball import *
from helpers import *
import usbevent

class kadeLoader( gui.loader ):
  def __init__( self, parent ):
    gui.loader.__init__( self, parent )
        
    self.beta = self.isBeta()              
    self.Title = get_title(self.beta)
    self.pins = get_pins()[2].split(",")
        
    self.m_list.InsertColumn(0, 'Description')
    self.m_list.InsertColumn(1, 'Key')
    self.m_list.SetColumnWidth(0, 240)
    self.m_list.SetColumnWidth(1, 0)    
    self.m_menu_testing.SetCheckable(True)
            
    #set application icon
    favicon = wx.Icon('images\\icons.ico', wx.BITMAP_TYPE_ICO, 16,16)
    self.SetIcon(favicon)
        
    #load icons for list
    self.image_lookup = ['console', 'joystick', 'keyboard', 'led', 'test', 'keypad', 'user']
    self.il = wx.ImageList(18, 16)
    for i in self.image_lookup:
      try:
        self.il.Add(wx.Bitmap("images\%s.bmp" % i))
        self.m_list.SetImageList(self.il, wx.IMAGE_LIST_SMALL)
      except: 
        pass   
        
    self.firmware = "" ; self.board = "" ;  self.family = ""
    self.addHTMLWindow()
    
    #get board selections and highlight last selected one
    default_board = self.getBoards()    
    if default_board: 
      self.m_choice.SetStringSelection(default_board)     
    
    #get firmware selections and highlight last selected one
    default_firmware = self.getFirmwares()    
    if default_firmware:
      i = 0
      while i < self.m_list.GetItemCount(): 
        if self.m_list.GetItem(i,1).GetText() == default_firmware: 
          self.m_list.Select(i)
        i += 1
      
    self.user_hex = None  #remember the last loaded user hex for the session
    self.m_load.SetLabel(program_label(self.family))
    self.checkForUpdates(initial=True)
    
    if self.beta:
      self.m_menu_trackball.Enable()
    
    #watch for USB events
    w = usbevent.Notification(self)
    
    #check for devices on start of loader
    w.detect(initial=True)
    self.board = self.m_choice.GetStringSelection()

  def isBeta(self):
    beta = os.path.exists(get_path("BETA"))
    if beta:
      self.m_menu_beta.SetItemLabel("Receive Public Updates Only (Not Beta)")
    else:
      self.m_menu_beta.SetItemLabel("Receive Beta Updates")    
    return beta    
    
  def addHTMLWindow(self):
    try:
      from wx.lib import iewin
      self.htmlWin = iewin.IEHtmlWindow(self.m_container, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize)
      self.previewPane.Add(self.htmlWin, proportion=1, flag=wx.EXPAND) 
      self.loadHTML()
      self.previewPane.Layout()
    except:
      self.popup("htmlerror")
      self.Destroy()
        
  def getBoards(self):
    self.m_choice.Clear()
    if self.beta:
      sql = 'SELECT name FROM boards ORDER BY sort'
    else:
      sql = 'SELECT name FROM boards WHERE public = "True" ORDER BY sort'
    data = sql_command(sql)    
    if data:
      for row in data: self.m_choice.Append(row[0])
      self.m_choice.SetSelection(0)
      self.board = self.m_choice.GetStringSelection()      
    return read_param("default_board")
    
  def getFirmwares(self):
    self.m_list.DeleteAllItems()
    family_data = sql_command('SELECT family FROM boards WHERE name = "%s"' % self.m_choice.GetStringSelection())
    if family_data:
      self.family = family_data[0][0]
      data = sql_command('SELECT desc, name, category, status, hex_test FROM firmwares WHERE family = "%s" AND status != "Admin" AND status != "Removed" ORDER BY category, sort' % self.family)
      for row in data:
        image = row[2]
        mode = ""
        if self.m_menu_testing.IsChecked() and row[4]: 
          mode = " (Test)"
          image = "test"
        elif row[3] == "WIP": 
          mode = " (WIP)"   
        item = self.m_list.Append((row[0] + mode, row[1]))
        
        if row[3] == "WIP": self.m_list.SetItemTextColour(item, wx.Colour(120,120,120))
        if image == "TEST": self.m_list.SetItemTextColour(item, wx.RED)
          
        try:
          self.m_list.SetItemImage(item, self.image_lookup.index(image))
        except ValueError:
          pass
    return read_param("default_firmware")                

  def getProduct(self):
    return sql_single('SELECT product FROM boards WHERE name = "%s"' % self.board)    
  
  def getCOMPort(self):
    #we need to work out the most likely port that arduino is connected
    #score a point for each significant word that appears in the description
    comport = ""
    if self.family == 'arduino':
      from serial.tools import list_ports
      wordlist = ("arduino", "prolific", "serial", "com", "port")
      score = 0
      results = []
      for port in list_ports.comports():
        for word in wordlist:
          if word in port[1].lower(): score += 1
        results.append((score, port[0]))
        score = 0 
      if results: 
        comport = sorted(results)[len(results)-1][1]
    else:
      comport = 'USB'
    return comport
 
  def updateBoards(self, notify=False):
    self.board = self.m_choice.GetStringSelection()
    self.getFirmwares()
    self.loadHTML("kade-instructions-%s" % self.family)    
    self.m_load.SetLabel(program_label(self.family))
    write_param("default_board", self.board)
    write_param("default_firmware", "") 
    if notify:
      self.popup("detect", self.board)
  
  def generateHTML(self, firmware):
    user_html_file = os.path.join(get_path("ROOT"), "%s.htm" % firmware)
    if not os.path.exists(user_html_file):
      mappings = sql_command('SELECT a.position, a.function, b.long_description FROM presets AS a, library AS b WHERE a. function = b.function and a.system = b.system and a.system = "%s" and a.preset = "0" ORDER BY a.position' % firmware)
      if mappings: generate_html(firmware, mappings)
    return user_html_file
  
  def loadHTML(self, firmware="kade-instructions-minimus"):
    doc = os.path.join(os.getcwd(),"documents\\%s\\index.htm" % firmware)
    if os.path.exists(doc): 
      self.htmlWin.LoadUrl(doc)
    else:
      doc = self.generateHTML(firmware)
      if os.path.exists(doc): self.htmlWin.LoadUrl(doc)     
   
  def verify(self):
    prg_settings = sql_command('SELECT loader, prog, port, baud FROM families WHERE family = "%s"' % self.family)  
    if prg_settings:  
      if prg_settings[0][0] == 'avrdude':
        com = self.getCOMPort()
        if com:
          msg = wx.MessageDialog(None, 'Arduino serial cable detected on COM Port: %s' % com, 'Arduino Detected', wx.OK | wx.ICON_EXCLAMATION)
          msg.ShowModal()
        return execute("verify",'"%s" -c %s -p %s -P %s -b 19200' % (get_path("AVR"), prg_settings[0][1], self.getProduct(), com) )      
      elif prg_settings[0][0] == 'dfu':
        return execute("verify",'"%s" %s get family' % (get_path("DFU"), self.getProduct()) )
    else:
      return False
       
  def erase(self):
    prg_settings = sql_command('SELECT loader, prog, port, baud FROM families WHERE family = "%s"' % self.family)  
    if prg_settings:  
      if prg_settings[0][0] == 'avrdude':
        return execute("erase",'"%s" -c %s -p %s -P %s -b 19200 -e' % (get_path("AVR"), prg_settings[0][1], self.getProduct(), self.getCOMPort()) )      
      elif prg_settings[0][0] == 'dfu':
        return execute("erase",'"%s" %s erase' % (get_path("DFU"), self.getProduct()) )
    else:
      return False

  def flashEeprom(self):
    do_flash = False
    if "custom" in self.firmware:
      from intelhex import IntelHex    
      eep_file = os.path.join(get_path("ROOT"), "eeprom.eep")
      map_file = os.path.join(get_path("ROOT"), "%s.map" % self.firmware)
      if not os.path.exists(map_file):
        map_file = os.path.join(get_path("ROOT"), "%s-default.map" % self.firmware)
      if os.path.exists(map_file):
        try:
          with open(map_file, 'r') as f: mappings = f.read().split("\n")
          f.closed
        except:
          pass
      
      if mappings:
        ih = IntelHex()
        i = 0
        for line in mappings:
          try: ih[i] = int(line)
          except: ih[i] = 0
          i +=1
        eep = open(eep_file, 'w')
        ih.write_hex_file(eep)
        eep.close()      
        do_flash = True
    return do_flash
  
  def burn(self, hex_file):
    success = False
    prg_settings = sql_command('SELECT loader, prog, port, baud FROM families WHERE family = "%s"' % self.family)  
    if prg_settings:  
      programmer = prg_settings[0][0]
      if programmer == 'avrdude':
        success = execute("burn",'"%s" -c %s -p %s -P %s -b 19200 -e -U flash:w:%s' % (get_path("AVR"), prg_settings[0][1], self.getProduct(), self.getCOMPort(), hex_file.split(":")[1]) )      
      elif programmer == 'bootloadhid':
        success = execute("burn",'"%s" -r %s' % (get_path("BLH"), hex_file.split(":")[1]) )      
      elif programmer == 'dfu':
        eep_file = os.path.join(get_path("ROOT"), "eeprom.eep")
        if self.flashEeprom() and os.path.exists(eep_file):
          execute("eeprom",'"%s" %s flash-eeprom "%s"' % (get_path("DFU"), self.getProduct(), eep_file))          
        success = execute("burn",'"%s" %s flash "%s"' % (get_path("DFU"), self.getProduct(), hex_file))
        if success:
          execute("start",'"%s" %s start' % (get_path("DFU"), self.getProduct()))
    return success

  def writeHex(self, hexdata):
    wx.BeginBusyCursor()
    if hexdata:      
      try:
        f = tempfile.TemporaryFile(delete=False)
        f.write(hexdata)
        f.close()
        if self.erase() and self.burn(f.name):
          delete_file(f.name)
          done = kadeProgrammed(None, self.firmware)
          done.ShowModal()
          done.Destroy()      
        else:
          delete_file(f.name)
          self.popup("problem")
      except: 
        self.popup("problem")    
    else: 
      self.popup("select")
    wx.EndBusyCursor()  
  
  def checkForUpdates(self, initial=False):    
    show=True
    if initial:
      if os.path.exists(get_path("NOCHECK")): 
        show = False
    if show:
      if get_latest_version(self.beta) > get_installed_version():
        update = kadeUpdate(self, get_latest_version(self.beta), initial)
        update.ShowModal()
        if update.getUpdate:
          update.Destroy()  
          self.Destroy()
        else:
          update.Destroy()
      else:
        if not initial: 
          self.popup("noupdate")
    
  def popup(self, messageID, subst=""):
    row = sql_command('SELECT msgtext, type FROM messages WHERE id = "%s"' % messageID)
    if row:
      if row[0][1] == "E":  
        msg = wx.MessageDialog(None, row[0][0].replace("%s",subst), 'KADE Alert', wx.OK | wx.ICON_EXCLAMATION)
      else: 
        msg = wx.MessageDialog(None, row[0][0].replace("%s",subst), 'KADE Information', wx.OK | wx.ICON_INFORMATION)      
      msg.ShowModal()  
          
#==========================================================================================
# Handlers for Loader events.  

  def onAbout(self, event):
    about = kadeAbout(None)
    about.ShowModal()
    about.Destroy()          
    
  def onBoards(self, event):
    self.updateBoards()
      
  def onSelect(self, event):
    selected = self.m_list.GetFirstSelected()    
    self.firmware = self.m_list.GetItem(selected, 1).GetText()
    if "custom" in self.firmware.lower():
      self.m_custom.Enable()
    else:
      self.m_custom.Disable()
    write_param("default_firmware", self.firmware)

    self.m_load.SetLabel(program_label(self.family))  #update button since it can change with load hex
    self.loadHTML(self.firmware)        
    time.sleep(0.2) #prevent rapid clicks which wxpython seems to struggle with    
    
  def onInstructions( self, event ):
    self.loadHTML("kade-instructions-%s" % self.family)       

  def onPrint( self, event ):
    self.htmlWin.Print()      

  def onPrintPreview( self, event ):
    self.htmlWin.PrintPreview()

  def onLoadHEX(self, event):
    dlg = wx.FileDialog(self, message="Load a HEX file", wildcard="*.hex", style=wx.OPEN)
    if dlg.ShowModal() == wx.ID_OK:
      self.user_hex = dlg.GetPath()
      self.loadHTML("user-hex") 
      self.m_load.SetLabel("Program HEX to Device")
      #unselect firmwares
      self.m_list.SetItemState(self.m_list.GetFirstSelected(), 0, wx.LIST_STATE_SELECTED)
    dlg.Destroy()
    
  def onVerify( self, event ):
    wx.BeginBusyCursor()
    if self.verify():
      self.popup("ready")
    else:
      self.popup("notfound")
    wx.EndBusyCursor()
  
  def onErase (self, event ):
    wx.BeginBusyCursor()
    if self.verify() and self.erase():
      self.popup("erased")      
    else:
      self.popup("notfound")
    wx.EndBusyCursor()
          
  def onBurn (self, event ):
    hexdata=""
    if self.user_hex and self.m_load.GetLabelText() == "Program HEX to Device":
      #read hex from user specified file
      with open(self.user_hex, 'r') as f:
        hexdata = f.read()
      f.closed      
    elif self.firmware:
      #read hex from database
      row = sql_command('SELECT hex, hex_test FROM firmwares WHERE name = "%s"' % self.firmware )
      if row:
        if self.m_menu_testing.IsChecked() and row[0][1]:
          hexdata=row[0][1]
        else:
          hexdata=row[0][0]
    self.writeHex(hexdata)
                
  def onNotes( self, event):
    open_file("release.txt")

  def onLicense(self, event):
    open_file("license.txt")

  def onConfig(self, event):
    config = kadeConfig(None, self.board, self.family, self.getCOMPort())
    config.ShowModal()
    config.Destroy()      

  def onCustom(self, event):
    custom = kadeCustom(None, self.firmware, self.board, self.beta)
    custom.ShowModal()
    custom.Destroy()      
    self.loadHTML(self.firmware)        
    
  def onTest(self, event):
    self.getFirmwares()

  def onBurnEZProgram(self, event):
    if self.family == "minimus":
      temp_firmware = self.firmware
      self.firmware = "kade-program"
      self.onBurn(event)
      self.firmware = temp_firmware
    else:
      self.popup("notcompatible")      
    
  def onBetaUpdates(self, event):  
    if self.beta:
      msg = "Please confirm that you no longer wish to receive Beta updates of this software.\n\n" + \
        "Reverting to public updates will remove board and firmware options that are currently flagged as Beta.\n\n" + \
        "Click OK to receive Public updates only."
    else:
      msg = "Please confirm that you wish to receive Beta updates of this software. " + \
        "Beta versions provide you with early access to new features, before the software is released to the general public.\n\n" + \
        "Please note that a Beta version is NOT the final version of the product and therefore we cannot guarantee it will be free from errors.\n\n" + \
        "Click OK to receive Beta."
    dlg = wx.MessageDialog(self, msg, "Beta Updates", wx.OK|wx.CANCEL|wx.ICON_QUESTION)
    if dlg.ShowModal() == wx.ID_OK:      
      if os.path.exists(get_path("BETA")):
        rmdir(get_path("BETA"))
      else:
        mkdir(get_path("BETA"))
        
      #Refresh everything - rather than forcing a restart
      self.beta = self.isBeta()
      self.Title = get_title(self.beta)
      self.getBoards()
      self.getFirmwares()
      self.m_choice.SetSelection(0)
      if self.beta:
        self.m_menu_trackball.Enable()
        self.popup("betaupdates")
      
  def onTrackballs(self, event):
    if self.family == "minimus":
      trackballs = kadeTrackballs(None, self.family)
      trackballs.ShowModal()
      trackballs.Destroy()      
    else:
      self.popup("noperipherals")
    
  def onCheckUpdates(self, event):
    self.checkForUpdates()
    
  def onAVRDrivers(self, event):
    open_file("drivers\minimus avr")
 
  def onKIT(self, event): 
    call_keyboard_test()
    
  def onKADEWebsite(self, event):
    browse("http://kadevice.com")
    
  def onKADEForum(self, event):
    browse("http://kadevice.com/forum")

  def onQuickStartGuide(self, event):
    browse("http://kadevice.com/?page_id=154")
    
  def onExit( self, event ):
    self.htmlWin.Destroy()
    self.Destroy()
 

#==========================================================================================
# Config

class kadeConfig( gui.config ):
  def __init__( self, parent, board, family, comport ):
    gui.config.__init__( self, parent )
    self.family = family
    self.board = board
    
    if family == "minimus": 
      self.m_baud.Disable()
      self.m_product.Disable()
      self.m_prog.Disable()
    
    settings = sql_command('SELECT loader, prog, baud FROM families WHERE family = "%s"' % (family))
    if settings:
      self.m_board.SetValue(board)
      self.m_family.SetValue(family)
      self.m_loader.SetValue(settings[0][0])
      self.m_prog.SetValue(settings[0][1])
      self.m_baud.SetValue(settings[0][2])
      
      if family == 'arduino' and not comport: 
        comport = "Not connected!"
      self.m_com.SetValue(comport)
      
      product = sql_command('SELECT product FROM boards WHERE name = "%s"' % (board))
      if product: 
        self.m_product.SetValue(product[0][0])
            
  def onOK(self, event):
    if self.family != "minimus":
      sql_command('UPDATE families SET prog = "%s", baud = "%s" WHERE family = "%s"' % (self.m_prog.GetValue(), self.m_baud.GetValue(), self.family), True)
      sql_command('UPDATE boards SET product = "%s" WHERE name = "%s"' % (self.m_product.GetValue(), self.board), True)
    self.Destroy()
    
  def onCancel(self, event):
    self.Destroy()    

#==========================================================================================
# Update

class kadeUpdate( gui.update ):
  def __init__( self, parent, version, initial ):
    gui.update.__init__( self, parent )    
    self.m_text1.SetLabel('Version  %s  is now available.' % version)
    self.m_text2.SetLabel('KADE Loader will exit automatically if you get this update.')
    self.getUpdate = False
    self.m_check.SetValue(os.path.exists(get_path("NOCHECK")))        
    
  def onUpdate(self, event):
    from webbrowser import open as openbrowser
    self.getUpdate = True    
    if self.m_check.GetValue():
      mkdir(get_path("NOCHECK"))
    else:
      rmdir(get_path("NOCHECK"))
    openbrowser("http://kadevice.com/loader/update.zip")
    self.Close()
    
  def onCancel(self, event):
    if self.m_check.GetValue():
      mkdir(get_path("NOCHECK"))
    else:
      rmdir(get_path("NOCHECK"))
    self.Close()    
        

#==========================================================================================
# About

class kadeAbout( gui.about ):
  def __init__( self, parent ):
    gui.about.__init__( self, parent )
    self.Title = "About KADE Loader"
    
  def onDonate(self, event):
    donate_link()
    self.Close()
    
  def onOK(self, event):
    self.Close()    
    
#==========================================================================================
# Programmed

class kadeProgrammed( gui.programmed ):
  def __init__( self, parent, firmware ):
    gui.programmed.__init__( self, parent )
    category = sql_single('SELECT category FROM firmwares WHERE name = "%s"' % firmware)    
    if category <> 'keyboard':
      self.m_kit.Hide()              
      
  def onOK(self, event):
    if self.m_kit.GetValue():
      call_keyboard_test()
    self.Close()        
    
#==========================================================================================
# Custom

class kadeCustom( gui.custom ):
  def __init__( self, parent, firmware, board, beta ):
    gui.custom.__init__( self, parent )        
    self.firmware = firmware
    self.beta = beta
    self.Title = "Custom Mapping Builder for %s" % get_firmware_title(self.firmware).split("(")[0]
    self.map_file = os.path.join(get_path("ROOT"), "%s.map" % self.firmware)
    self.default_map_file = os.path.join(get_path("ROOT"), "%s-default.map" % self.firmware)
    self.pins = get_pins()[0].split(",")
    self.normal = self.A1,self.A2,self.A3,self.A4,self.A5,self.A6,self.A7,self.A8,self.A9,self.A10,self.B1,self.B2,self.B3,self.B4,self.B5,self.B6,self.B7,self.B8,self.B9,self.B10        
    self.shifted = self.A1s,self.A2s,self.A3s,self.A4s,self.A5s,self.A6s,self.A7s,self.A8s,self.A9s,self.A10s,self.B1s,self.B2s,self.B3s,self.B4s,self.B5s,self.B6s,self.B7s,self.B8s,self.B9s,self.B10s   
    self.inputs = self.normal + self.shifted
    self.keys = []
    self.filtered = ""
    
    self.getFunctions()
    self.loadCustom()
      
    #system specific features
    if self.firmware == 'kade-xbox-custom': 
      self.m_xbox_disable.Show()
      self.m_xbox_combos.Show()
      self.m_xbox_combos.SetURL(os.path.join(os.getcwd(), "documents\\supplementary\\xbox_advanced_combos.htm"))
    else: 
      self.m_xbox_disable.Hide()
      self.m_xbox_combos.Hide()
    
    if self.firmware == 'kade-mame-custom' or self.firmware == 'kade-key-custom' or self.firmware == 'kade-pin-custom':
      self.m_settings0.Hide()
      self.m_settings1.Hide()
      
    if self.firmware == 'kade-mame-custom':
      self.m_preset1.Hide()
      self.m_settings2.Show()
      self.m_settings2.Layout()
    else:
      self.m_settings2.Hide()
  
    #do we show a 2nd preset?
    if sql_command('SELECT position FROM presets WHERE system = "%s" AND preset = "2"' % (self.firmware)):
      self.m_preset2.Show()
    
    #Update any reserved pins
    for rsv in get_reserved(self.firmware):
      try:
        index = self.pins.index(rsv[0])
      except ValueError:
        index = -1
      if index >= 0:
        #update normal pins
        self.normal[index].SetItems((rsv[2],))
        self.normal[index].SetSelection(0)
        self.normal[index].Disable()
        #update shifted pins
        self.shifted[index].SetItems(('',))
        self.shifted[index].SetSelection(0)
        self.shifted[index].Disable()
    
    #Trackball settings?
    trackball = sql_command('SELECT trackball FROM firmwares WHERE name = "%s" AND trackball = "True"' % self.firmware)
    if trackball:      
      if not self.beta:
        #disable trackball functionality outside of beta
        self.m_trackball1.Disable()
        
      self.m_compatible_list.SetURL(os.path.join(os.getcwd(), "documents\\supplementary\\peripheral_compatibility_list.htm"))      

      if self.m_trackball1.GetValue(): self.m_trackball1_map.Enable()
      if self.m_trackball2.GetValue(): self.m_trackball2_map.Enable()
      self.reserveTrackball(self.A3, self.A3s, self.m_trackball1.GetValue(), "Trackball 1: DATA Line",  initial=True)
      self.reserveTrackball(self.A7, self.A7s, self.m_trackball1.GetValue(), "Trackball 1: CLOCK Line", initial=True)
      self.reserveTrackball(self.A4, self.A4s, self.m_trackball2.GetValue(), "Trackball 2: DATA Line",  initial=True)
      self.reserveTrackball(self.A8, self.A8s, self.m_trackball2.GetValue(), "Trackball 2: CLOCK Line", initial=True)      
    else:
      self.m_settings0.Hide()
      
  def getFunctions(self):
    self.choices = []
    self.shifted_choices = []
    self.functions = sql_command('SELECT function, description FROM library WHERE system = "%s" ORDER BY sort' % (self.firmware))
      
    for row in self.functions:
      self.keys.append(row[0])
      self.choices.append(row[1])
      if not "*" in row[1]: 
        self.shifted_choices.append(row[1])
    for control in self.normal: 
      control.SetItems(self.choices)
    for control in self.shifted: 
      control.SetItems(self.shifted_choices)    
      
  def clearAll(self):
    for control in self.inputs:
      control.SetSelection(0)
      
  def updateInputFields(self):      
    #disable shift when it is not relevant
    for x in range(0, 20):
      if "*" in self.normal[x].GetStringSelection():
        self.shifted[x].SetSelection(0)
        self.shifted[x].Disable()
      else:
        self.shifted[x].Enable()
                  
  def populatePresets(self, preset):
    self.clearAll()
    presets = sql_command('SELECT position, function FROM presets WHERE system = "%s" AND preset = "%s" ORDER BY position' % (self.firmware, preset))
    if presets:
      for row in presets:
        try:
          pos = int(row[0])-1
          fun = int(row[1])
          self.inputs[pos].SetSelection(self.keys.index(int(fun)))
        except:
          pass        
    self.updateInputFields()
            
  def loadCustom(self):
    if os.path.exists(self.map_file):
      with open(self.map_file, 'r') as f: 
        mappings = f.read().split("\n")
      f.closed
      
      #read first 40 lines as pin assignments
      i = 0
      for control in self.inputs: 
        try: control.SetSelection(self.keys.index(int(mappings[i])))    
        except: control.SetSelection(0)              
        i += 1
      self.updateInputFields()
        
      #additional lines are for system specific settings
      #we can load them all and only display those that are relevant
      try:
        self.m_xbox_disable.SetValue(mappings[40] == '1')        
        self.m_xbox_delay.SetValue(mappings[41])
        self.m_xbox_autofire_delay.SetValue(mappings[42])        
      except IndexError:
        pass

      #Trackballs enabled
      try:
        self.m_trackball1.SetValue(mappings[43]=='1')
        self.m_trackball2.SetValue(mappings[44]=='1')
      except:
        pass        
      
      #Trackball 1 mappings
      self.trackball1_map = []
      try:
        for i in range(55, 62):
          self.trackball1_map.append(int(mappings[i]))
      except:
        self.trackball1_map = list((0,0,0,0,0,0,0))
      
      #Trackball 2 mappings
      self.trackball2_map = []
      try:
        for i in range(62, 69):
          self.trackball2_map.append(int(mappings[i]))
      except:
        self.trackball2_map = list((0,0,0,0,0,0,0))
      
    else:
      self.trackball1_map = list((0,0,0,0,0,0,0))
      self.trackball2_map = list((0,0,0,0,0,0,0))
      self.populatePresets(0)

  def save(self, filename):
    try:
      #build mapping list for HTML generation
      desc = sql_command('SELECT long_description FROM library WHERE system = "%s"' % self.firmware)
      mappings = []
      
      #write out the pin mappings (first 40 lines)
      f = open(filename, 'w')       
      cnt = 1
      for control in self.inputs:
        function = self.functions[control.GetSelection()][0]
        f.write(str(function) + "\n")
        
        try: mappings.append((cnt, function, desc[function][0]))
        except: mappings.append((cnt, function, ""))
        cnt += 1

      #write out extra settings             
      extra=[]
      #40: disable start/back      
      disable = str(b2i(self.m_xbox_disable.GetValue()))
      extra.append(disable)
      f.write(disable + "\n")  
        
      #41: Seconds to delay power
      try:
        delay = int(self.m_xbox_delay.GetValue())
        if delay > 60: delay = 60
        if delay < 0: delay = 0
      except:
        delay = 0
      extra.append(str(delay))
      f.write(str(delay)+ "\n")        
      
      #42: Autofire Delay
      try:
        delay = int(self.m_xbox_autofire_delay.GetValue())
        if delay > 25: delay = 250
        if delay < 5: delay = 5
      except:
        delay = 15
      extra.append(str(delay))
      f.write(str(delay)+"\n")        
      
      #43: PS/2 (Trackball and Mouse) connection 1
      try:
        connected = b2i(self.m_trackball1.GetValue())
      except:
        connected = 0
      extra.append(str(connected))
      f.write(str(connected)+"\n")

      #44: PS/2 (Trackball and Mouse) connection 2
      try:
        connected = b2i(self.m_trackball2.GetValue())
      except:
        connected = 0
      extra.append(str(connected))
      f.write(str(connected)+"\n")        
      
      #45 to 54: Trackball Configuration
      track_file = os.path.join(get_path("ROOT"),"track.dat")      
      if os.path.exists(track_file):
        records = read_data_keys(track_file)
        #trackball 1
        f.write(records[0][1]+"\n") # counts
        f.write(records[1][1]+"\n") # samples
        f.write(str(b2i(records[2][1]=="True")) +"\n") # trackball 1
        f.write(str(b2i(records[3][1]=="True")) +"\n") # spinner 1
        f.write(str(b2i(records[4][1]=="True")) +"\n") # mouse 1              
        #trackball 2
        f.write(records[5][1]+"\n") # counts
        f.write(records[6][1]+"\n") # samples
        f.write(str(b2i(records[7][1]=="True")) +"\n") # trackball 1
        f.write(str(b2i(records[8][1]=="True")) +"\n") # spinner 1
        f.write(str(b2i(records[9][1]=="True")) +"\n") # mouse 1              
      else:
        for i in range(0,10): 
          f.write("0\n")          
      
      #55 to 61: Trackball Device 1 Assignments
      for mapping in self.trackball1_map:
        f.write(str(mapping)+"\n")
      
      #62 to 68: Trackball Device 2 Assignments
      for mapping in self.trackball2_map:
        f.write(str(mapping)+"\n")

      #End of settings
      f.close()
      if mappings:
        generate_html(self.firmware, mappings, extra)
        
    except:
      pass

  def reserveTrackball(self, pin, pin_s, reserve=True, description="Reserved", initial=False):
    if reserve:
      pin.SetItems((description,))
      pin.SetSelection(0)
      pin.Disable()
      pin_s.SetItems(("",))
      pin_s.SetSelection(0)
      pin_s.Disable()
    else:
      if not initial:  #don't erase content when first loading
        pin.SetItems(self.choices)
        pin.SetSelection(0)
        pin.Enable()
        pin_s.SetItems(self.shifted_choices)
        pin_s.SetSelection(0)    
        pin_s.Enable()
        
  def onSave(self, event):
    self.save(self.map_file)
    self.Destroy()
          
  def onChoice(self, event):
    self.updateInputFields()
    
  def onClear(self, event):
    self.clearAll()
      
  def onPreset0(self, event):    
    self.populatePresets(0)  
    #Generate a default map for fallback (and for inclusion in the installer)
    if not os.path.exists(self.default_map_file):
      self.save(self.default_map_file)
      
  def onPreset1(self, event):
    self.populatePresets(1)        

  def onPreset2(self, event):
    self.populatePresets(2)        

  def onPreset3(self, event):    
    self.populatePresets(3)
    
  def onPreset4(self, event):
    self.populatePresets(4)
    
  def onPreset5(self, event):    
    self.populatePresets(5)    
    
  def onImport(self, event):
    dlg=wx.FileDialog(None,'Choose a KADE mapping file',get_path(name="USERDOCS"), \
      style=wx.OPEN | wx.FD_MULTIPLE | wx.FD_FILE_MUST_EXIST,wildcard="XML File (*.xml)|*.xml")
    if dlg.ShowModal() == wx.ID_OK:
      with open(dlg.GetPath(), 'r') as f: 
        xml = f.read()
      f.closed
      if xml.find('firmware="%s"' % self.firmware) > 0:
        self.clearAll()
        for x in range(0,20):
          self.inputs[x].SetSelection(self.keys.index(read_xml(xml, self.pins[x])))
          self.inputs[x+20].SetSelection(self.keys.index(read_xml(xml, self.pins[x], True)))
        self.updateInputFields()
        
        #import system specific fields (if they're in the XML)
        self.m_xbox_disable.SetValue(read_xml(xml, 'DISABLE-STARTBACK') == 1)
        self.m_xbox_delay.SetValue(str(read_xml(xml, 'DELAY-SECONDS')))
        self.m_xbox_autofire_delay.SetValue(str(read_xml(xml, 'AUTOFIRE-TIMING')))
      else:
        msg = wx.MessageDialog(None, 'Mappings were not imported. The selected XML file is not valid for this system.', 'Invalid XML', wx.OK | wx.ICON_WARNING)      
        msg.ShowModal()
      
  def onExport(self, event):
    dlg=wx.FileDialog(None,'Choose a KADE mapping file',get_path(name="USERDOCS"), \
      style=wx.SAVE | wx.OVERWRITE_PROMPT,defaultFile="%s-user" % self.firmware, wildcard="XML File (*.xml)|*.xml")
    if dlg.ShowModal() == wx.ID_OK:
      xml = get_template(self.firmware, "xml")
      if xml:
        for x in range(0,20):
          xml = xml.replace('{%s}' % self.pins[x], str(self.functions[self.inputs[x].GetSelection()][0]))
          xml = xml.replace('{%sS}' % self.pins[x], str(self.functions[self.inputs[x+20].GetSelection()][0]))
          
        #export system specific fields (if they're in the XML template)
        xml = xml.replace('{DISABLE-STARTBACK}', str(b2i(self.m_xbox_disable.GetValue())))
        xml = xml.replace('{DELAY-SECONDS}', str(self.m_xbox_delay.GetValue()))
        xml = xml.replace('{AUTOFIRE-TIMING}', str(self.m_xbox_autofire_delay.GetValue()))
        
        f = open(dlg.GetPath(), 'w') 
        f.write(xml)
        f.close()
    
  def onCancel(self, event):
    self.Destroy()    
                    
  def onTrackball1(self, event):
    self.reserveTrackball(self.A3, self.A3s, self.m_trackball1.GetValue(), "Trackball 1: DATA Line")
    self.reserveTrackball(self.A7, self.A7s, self.m_trackball1.GetValue(), "Trackball 1: CLOCK Line")
    if self.m_trackball1.GetValue(): 
      self.m_trackball1_map.Enable()    
    else:
      self.m_trackball1_map.Disable()    

  def onTrackball2(self, event):
    self.reserveTrackball(self.A4, self.A4s, self.m_trackball2.GetValue(), "Trackball 2: DATA Line")
    self.reserveTrackball(self.A8, self.A8s, self.m_trackball2.GetValue(), "Trackball 2: CLOCK Line")
    if self.m_trackball2.GetValue(): 
      self.m_trackball2_map.Enable()    
    else:
      self.m_trackball2_map.Disable()    

  def assign_trackball_inputs(self, name, maps):
    array = []
    trackballs = kadeTrackballInputs(None, name, self.choices, self.keys, maps)
    trackballs.ShowModal()    
    trackball_controls = trackballs.BUT1, trackballs.BUT2, trackballs.BUT3, trackballs.BUT1s, trackballs.BUT2s, trackballs.BUT3s       
    array.append(b2i(trackballs.m_left.GetValue()==False))
    for control in trackball_controls:
      array.append(self.functions[control.GetSelection()][0])
    trackballs.Destroy()      
    return array    
      
  def onAssign1(self, event):
    self.trackball1_map = self.assign_trackball_inputs("Trackball 1", self.trackball1_map)
        
  def onAssign2(self, event):
    self.trackball2_map = self.assign_trackball_inputs("Trackball 2", self.trackball2_map)
    

#==========================================================================================
# Main
    
def main():
  app = wx.App(False)
  kadeLoader(None).Show()
  app.MainLoop()
  app.Destroy()

if __name__ == "__main__":
  main()  