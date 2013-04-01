# -*- coding: utf-8 -*- 

###########################################################################
## Python code generated with wxFormBuilder (version Jun 30 2011)
## http://www.wxformbuilder.org/
##
## PLEASE DO "NOT" EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc

###########################################################################
## Class loader
###########################################################################

class loader ( wx.Frame ):
	
	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = u"KADE Loader", pos = wx.DefaultPosition, size = wx.Size( 1001,640 ), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL )
		
		self.SetSizeHintsSz( wx.Size( 800,640 ), wx.DefaultSize )
		
		bSizer1 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_panel1 = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer2 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer3 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_panel3 = wx.Panel( self.m_panel1, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer4 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_bitmap1 = wx.StaticBitmap( self.m_panel3, wx.ID_ANY, wx.Bitmap( u"images/KADE.png", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer4.Add( self.m_bitmap1, 0, wx.ALL|wx.EXPAND, 5 )
		
		sbSizer3 = wx.StaticBoxSizer( wx.StaticBox( self.m_panel3, wx.ID_ANY, u"Board Options" ), wx.VERTICAL )
		
		m_choiceChoices = []
		self.m_choice = wx.Choice( self.m_panel3, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, m_choiceChoices, 0 )
		self.m_choice.SetSelection( -1 )
		self.m_choice.SetFont( wx.Font( 10, 70, 90, 90, False, wx.EmptyString ) )
		
		sbSizer3.Add( self.m_choice, 0, wx.ALL|wx.EXPAND, 5 )
		
		bSizer4.Add( sbSizer3, 0, wx.ALL|wx.EXPAND, 5 )
		
		sbSizer21 = wx.StaticBoxSizer( wx.StaticBox( self.m_panel3, wx.ID_ANY, u"Firmware Options" ), wx.VERTICAL )
		
		self.m_list = wx.ListCtrl( self.m_panel3, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.LC_HRULES|wx.LC_NO_HEADER|wx.LC_REPORT|wx.LC_SINGLE_SEL|wx.LC_VRULES )
		sbSizer21.Add( self.m_list, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer4.Add( sbSizer21, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer13 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_load = wx.Button( self.m_panel3, wx.ID_ANY, u"Program KADE with Selected Firmware", wx.DefaultPosition, wx.Size( 220,-1 ), 0 )
		bSizer13.Add( self.m_load, 0, wx.ALL, 5 )
		
		bSizer4.Add( bSizer13, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_panel3.SetSizer( bSizer4 )
		self.m_panel3.Layout()
		bSizer4.Fit( self.m_panel3 )
		bSizer3.Add( self.m_panel3, 0, wx.EXPAND, 5 )
		
		self.m_container = wx.Panel( self.m_panel1, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer5 = wx.BoxSizer( wx.VERTICAL )
		
		sbSizer1 = wx.StaticBoxSizer( wx.StaticBox( self.m_container, wx.ID_ANY, u"Documentation" ), wx.VERTICAL )
		
		self.previewPane = wx.BoxSizer( wx.VERTICAL )
		
		sbSizer1.Add( self.previewPane, 1, wx.EXPAND, 5 )
		
		bSizer5.Add( sbSizer1, 1, wx.ALL|wx.EXPAND, 5 )
		
		self.m_buttons = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_instructions = wx.Button( self.m_container, wx.ID_ANY, u"Print Preview", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_buttons.Add( self.m_instructions, 0, wx.ALL, 5 )
		
		self.m_custom = wx.Button( self.m_container, wx.ID_ANY, u"Customise", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_custom.Enable( False )
		
		self.m_buttons.Add( self.m_custom, 0, wx.ALL, 5 )
		
		
		self.m_buttons.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_usb = wx.StaticText( self.m_container, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( 300,-1 ), wx.ALIGN_RIGHT|wx.ST_NO_AUTORESIZE )
		self.m_usb.Wrap( -1 )
		self.m_usb.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 90, False, wx.EmptyString ) )
		
		self.m_buttons.Add( self.m_usb, 0, wx.ALL, 10 )
		
		self.m_usb_icon = wx.StaticBitmap( self.m_container, wx.ID_ANY, wx.Bitmap( u"images/usb_off.png", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.Size( 30,16 ), 0 )
		self.m_buttons.Add( self.m_usb_icon, 0, wx.ALIGN_CENTER_VERTICAL|wx.ALL, 5 )
		
		bSizer5.Add( self.m_buttons, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_container.SetSizer( bSizer5 )
		self.m_container.Layout()
		bSizer5.Fit( self.m_container )
		bSizer3.Add( self.m_container, 1, wx.EXPAND, 5 )
		
		bSizer2.Add( bSizer3, 1, wx.EXPAND, 5 )
		
		self.m_panel1.SetSizer( bSizer2 )
		self.m_panel1.Layout()
		bSizer2.Fit( self.m_panel1 )
		bSizer1.Add( self.m_panel1, 1, wx.EXPAND, 5 )
		
		self.SetSizer( bSizer1 )
		self.Layout()
		self.m_menubar1 = wx.MenuBar( 0 )
		self.m_menu1 = wx.Menu()
		self.m_menuItem12 = wx.MenuItem( self.m_menu1, wx.ID_ANY, u"Print", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu1.AppendItem( self.m_menuItem12 )
		
		self.m_menuItem13 = wx.MenuItem( self.m_menu1, wx.ID_ANY, u"Print Preview", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu1.AppendItem( self.m_menuItem13 )
		
		self.m_menu1.AppendSeparator()
		
		self.m_menuItem16 = wx.MenuItem( self.m_menu1, wx.ID_ANY, u"Load HEX File...", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu1.AppendItem( self.m_menuItem16 )
		
		self.m_menu1.AppendSeparator()
		
		self.m_menuItem2 = wx.MenuItem( self.m_menu1, wx.ID_ANY, u"Exit", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu1.AppendItem( self.m_menuItem2 )
		
		self.m_menubar1.Append( self.m_menu1, u"File" ) 
		
		self.m_menu4 = wx.Menu()
		self.m_menuItem32 = wx.MenuItem( self.m_menu4, wx.ID_ANY, u"Verify Device", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu4.AppendItem( self.m_menuItem32 )
		
		self.m_menuItem31 = wx.MenuItem( self.m_menu4, wx.ID_ANY, u"Erase Device", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu4.AppendItem( self.m_menuItem31 )
		
		self.m_menuItem3 = wx.MenuItem( self.m_menu4, wx.ID_ANY, u"Program Selected Firmware", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu4.AppendItem( self.m_menuItem3 )
		
		self.m_menubar1.Append( self.m_menu4, u"Actions" ) 
		
		self.m_menu41 = wx.Menu()
		self.m_menuItem10 = wx.MenuItem( self.m_menu41, wx.ID_ANY, u"Board Configuration", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu41.AppendItem( self.m_menuItem10 )
		
		self.m_menu11 = wx.Menu()
		self.m_menu_trackball = wx.MenuItem( self.m_menu11, wx.ID_ANY, u"Configure Trackball, Spinner and Mouse (Beta)", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu11.AppendItem( self.m_menu_trackball )
		self.m_menu_trackball.Enable( False )
		
		self.m_menu41.AppendSubMenu( self.m_menu11, u"Peripherals" )
		
		self.m_menubar1.Append( self.m_menu41, u"Settings" ) 
		
		self.m_menu61 = wx.Menu()
		self.m_menuItem18 = wx.MenuItem( self.m_menu61, wx.ID_ANY, u"Keyboard Input Tester", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu61.AppendItem( self.m_menuItem18 )
		
		self.m_menubar1.Append( self.m_menu61, u"Utilities" ) 
		
		self.m_menu5 = wx.Menu()
		self.m_menu_testing = wx.MenuItem( self.m_menu5, wx.ID_ANY, u"Enable PC Testing of Firmwares", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu5.AppendItem( self.m_menu_testing )
		
		self.m_menu5.AppendSeparator()
		
		self.m_menu_ezprogram = wx.MenuItem( self.m_menu5, wx.ID_ANY, u"Burn EZ-Program Firmware", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu5.AppendItem( self.m_menu_ezprogram )
		
		self.m_menu5.AppendSeparator()
		
		self.m_menu3 = wx.Menu()
		self.m_menu_beta = wx.MenuItem( self.m_menu3, wx.ID_ANY, u"Receive Beta Updates", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu3.AppendItem( self.m_menu_beta )
		
		self.m_menu5.AppendSubMenu( self.m_menu3, u"Beta Version" )
		
		self.m_menubar1.Append( self.m_menu5, u"Advanced" ) 
		
		self.m_menu6 = wx.Menu()
		self.m_menuItem61 = wx.MenuItem( self.m_menu6, wx.ID_ANY, u"Instructions", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu6.AppendItem( self.m_menuItem61 )
		
		self.m_menuItem611 = wx.MenuItem( self.m_menu6, wx.ID_ANY, u"Release Notes", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu6.AppendItem( self.m_menuItem611 )
		
		self.m_menuItem17 = wx.MenuItem( self.m_menu6, wx.ID_ANY, u"License Agreement", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu6.AppendItem( self.m_menuItem17 )
		
		self.m_menu2 = wx.Menu()
		self.m_menuItem15 = wx.MenuItem( self.m_menu2, wx.ID_ANY, u"AVR Drivers", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu2.AppendItem( self.m_menuItem15 )
		
		self.m_menu6.AppendSubMenu( self.m_menu2, u"Drivers" )
		
		self.m_menu6.AppendSeparator()
		
		self.m_menuItem20 = wx.MenuItem( self.m_menu6, wx.ID_ANY, u"KADE Website", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu6.AppendItem( self.m_menuItem20 )
		
		self.m_menuItem21 = wx.MenuItem( self.m_menu6, wx.ID_ANY, u"KADE Forum", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu6.AppendItem( self.m_menuItem21 )
		
		self.m_menu6.AppendSeparator()
		
		self.m_menuItem11 = wx.MenuItem( self.m_menu6, wx.ID_ANY, u"Check for Updates", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu6.AppendItem( self.m_menuItem11 )
		
		self.m_menu6.AppendSeparator()
		
		self.m_menuItem6 = wx.MenuItem( self.m_menu6, wx.ID_ANY, u"About...", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu6.AppendItem( self.m_menuItem6 )
		
		self.m_menubar1.Append( self.m_menu6, u"Help" ) 
		
		self.SetMenuBar( self.m_menubar1 )
		
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.m_choice.Bind( wx.EVT_CHOICE, self.onBoards )
		self.m_list.Bind( wx.EVT_LIST_ITEM_SELECTED, self.onSelect )
		self.m_load.Bind( wx.EVT_BUTTON, self.onBurn )
		self.m_instructions.Bind( wx.EVT_BUTTON, self.onPrintPreview )
		self.m_custom.Bind( wx.EVT_BUTTON, self.onCustom )
		self.Bind( wx.EVT_MENU, self.onPrint, id = self.m_menuItem12.GetId() )
		self.Bind( wx.EVT_MENU, self.onPrintPreview, id = self.m_menuItem13.GetId() )
		self.Bind( wx.EVT_MENU, self.onLoadHEX, id = self.m_menuItem16.GetId() )
		self.Bind( wx.EVT_MENU, self.onExit, id = self.m_menuItem2.GetId() )
		self.Bind( wx.EVT_MENU, self.onVerify, id = self.m_menuItem32.GetId() )
		self.Bind( wx.EVT_MENU, self.onErase, id = self.m_menuItem31.GetId() )
		self.Bind( wx.EVT_MENU, self.onBurn, id = self.m_menuItem3.GetId() )
		self.Bind( wx.EVT_MENU, self.onConfig, id = self.m_menuItem10.GetId() )
		self.Bind( wx.EVT_MENU, self.onTrackballs, id = self.m_menu_trackball.GetId() )
		self.Bind( wx.EVT_MENU, self.onKIT, id = self.m_menuItem18.GetId() )
		self.Bind( wx.EVT_MENU, self.onTest, id = self.m_menu_testing.GetId() )
		self.Bind( wx.EVT_MENU, self.onBurnEZProgram, id = self.m_menu_ezprogram.GetId() )
		self.Bind( wx.EVT_MENU, self.onBetaUpdates, id = self.m_menu_beta.GetId() )
		self.Bind( wx.EVT_MENU, self.onInstructions, id = self.m_menuItem61.GetId() )
		self.Bind( wx.EVT_MENU, self.onNotes, id = self.m_menuItem611.GetId() )
		self.Bind( wx.EVT_MENU, self.onLicense, id = self.m_menuItem17.GetId() )
		self.Bind( wx.EVT_MENU, self.onAVRDrivers, id = self.m_menuItem15.GetId() )
		self.Bind( wx.EVT_MENU, self.onKADEWebsite, id = self.m_menuItem20.GetId() )
		self.Bind( wx.EVT_MENU, self.onKADEForum, id = self.m_menuItem21.GetId() )
		self.Bind( wx.EVT_MENU, self.onCheckUpdates, id = self.m_menuItem11.GetId() )
		self.Bind( wx.EVT_MENU, self.onAbout, id = self.m_menuItem6.GetId() )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onBoards( self, event ):
		event.Skip()
	
	def onSelect( self, event ):
		event.Skip()
	
	def onBurn( self, event ):
		event.Skip()
	
	def onPrintPreview( self, event ):
		event.Skip()
	
	def onCustom( self, event ):
		event.Skip()
	
	def onPrint( self, event ):
		event.Skip()
	
	
	def onLoadHEX( self, event ):
		event.Skip()
	
	def onExit( self, event ):
		event.Skip()
	
	def onVerify( self, event ):
		event.Skip()
	
	def onErase( self, event ):
		event.Skip()
	
	
	def onConfig( self, event ):
		event.Skip()
	
	def onTrackballs( self, event ):
		event.Skip()
	
	def onKIT( self, event ):
		event.Skip()
	
	def onTest( self, event ):
		event.Skip()
	
	def onBurnEZProgram( self, event ):
		event.Skip()
	
	def onBetaUpdates( self, event ):
		event.Skip()
	
	def onInstructions( self, event ):
		event.Skip()
	
	def onNotes( self, event ):
		event.Skip()
	
	def onLicense( self, event ):
		event.Skip()
	
	def onAVRDrivers( self, event ):
		event.Skip()
	
	def onKADEWebsite( self, event ):
		event.Skip()
	
	def onKADEForum( self, event ):
		event.Skip()
	
	def onCheckUpdates( self, event ):
		event.Skip()
	
	def onAbout( self, event ):
		event.Skip()
	

###########################################################################
## Class config
###########################################################################

class config ( wx.Dialog ):
	
	def __init__( self, parent ):
		wx.Dialog.__init__ ( self, parent, id = wx.ID_ANY, title = u"Board Configuation", pos = wx.DefaultPosition, size = wx.Size( 300,350 ), style = wx.DEFAULT_DIALOG_STYLE )
		
		self.SetSizeHintsSz( wx.Size( 300,350 ), wx.DefaultSize )
		
		bSizer9 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer10 = wx.BoxSizer( wx.VERTICAL )
		
		sbSizer4 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"Board Name" ), wx.VERTICAL )
		
		self.m_board = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_board.Enable( False )
		
		sbSizer4.Add( self.m_board, 0, wx.ALL|wx.EXPAND, 5 )
		
		bSizer10.Add( sbSizer4, 0, wx.ALL|wx.EXPAND, 5 )
		
		sbSizer5 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"Settings" ), wx.VERTICAL )
		
		bSizer21 = wx.BoxSizer( wx.VERTICAL )
		
		gSizer1 = wx.GridSizer( 4, 2, 0, 0 )
		
		bSizer11 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_staticText1 = wx.StaticText( self, wx.ID_ANY, u"Family:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText1.Wrap( -1 )
		bSizer11.Add( self.m_staticText1, 0, wx.ALL, 5 )
		
		gSizer1.Add( bSizer11, 1, wx.EXPAND, 5 )
		
		bSizer12 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_family = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_family.Enable( False )
		
		bSizer12.Add( self.m_family, 0, wx.ALL|wx.EXPAND, 5 )
		
		gSizer1.Add( bSizer12, 1, wx.EXPAND, 5 )
		
		bSizer17 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_staticText4 = wx.StaticText( self, wx.ID_ANY, u"Port:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText4.Wrap( -1 )
		bSizer17.Add( self.m_staticText4, 0, wx.ALL, 5 )
		
		gSizer1.Add( bSizer17, 1, wx.EXPAND, 5 )
		
		bSizer18 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_com = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_com.Enable( False )
		
		bSizer18.Add( self.m_com, 0, wx.ALL|wx.EXPAND, 5 )
		
		gSizer1.Add( bSizer18, 1, wx.EXPAND, 5 )
		
		bSizer13 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_staticText2 = wx.StaticText( self, wx.ID_ANY, u"Loader:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText2.Wrap( -1 )
		bSizer13.Add( self.m_staticText2, 0, wx.ALL, 5 )
		
		gSizer1.Add( bSizer13, 1, wx.EXPAND, 5 )
		
		bSizer14 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_loader = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_loader.Enable( False )
		
		bSizer14.Add( self.m_loader, 0, wx.ALL|wx.EXPAND, 5 )
		
		gSizer1.Add( bSizer14, 1, wx.EXPAND, 5 )
		
		bSizer15 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_staticText3 = wx.StaticText( self, wx.ID_ANY, u"Programmer:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText3.Wrap( -1 )
		bSizer15.Add( self.m_staticText3, 0, wx.ALL, 5 )
		
		gSizer1.Add( bSizer15, 1, wx.EXPAND, 5 )
		
		bSizer16 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_prog = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer16.Add( self.m_prog, 0, wx.ALL|wx.EXPAND, 5 )
		
		gSizer1.Add( bSizer16, 1, wx.EXPAND, 5 )
		
		bSizer19 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_staticText5 = wx.StaticText( self, wx.ID_ANY, u"Baud Rate:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText5.Wrap( -1 )
		bSizer19.Add( self.m_staticText5, 0, wx.ALL, 5 )
		
		gSizer1.Add( bSizer19, 1, wx.EXPAND, 5 )
		
		bSizer20 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_baud = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer20.Add( self.m_baud, 0, wx.ALL|wx.EXPAND, 5 )
		
		gSizer1.Add( bSizer20, 1, wx.EXPAND, 5 )
		
		bSizer22 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_staticText6 = wx.StaticText( self, wx.ID_ANY, u"Product:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText6.Wrap( -1 )
		bSizer22.Add( self.m_staticText6, 0, wx.ALL, 5 )
		
		gSizer1.Add( bSizer22, 1, wx.EXPAND, 5 )
		
		bSizer23 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_product = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer23.Add( self.m_product, 0, wx.ALL|wx.EXPAND, 5 )
		
		gSizer1.Add( bSizer23, 1, wx.EXPAND, 5 )
		
		bSizer21.Add( gSizer1, 1, wx.EXPAND, 5 )
		
		sbSizer5.Add( bSizer21, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer10.Add( sbSizer5, 0, wx.ALL|wx.EXPAND, 5 )
		
		m_sdbSizer1 = wx.StdDialogButtonSizer()
		self.m_sdbSizer1OK = wx.Button( self, wx.ID_OK )
		m_sdbSizer1.AddButton( self.m_sdbSizer1OK )
		self.m_sdbSizer1Cancel = wx.Button( self, wx.ID_CANCEL )
		m_sdbSizer1.AddButton( self.m_sdbSizer1Cancel )
		m_sdbSizer1.Realize();
		bSizer10.Add( m_sdbSizer1, 1, wx.EXPAND, 5 )
		
		bSizer9.Add( bSizer10, 1, wx.EXPAND, 5 )
		
		self.SetSizer( bSizer9 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.m_sdbSizer1Cancel.Bind( wx.EVT_BUTTON, self.onCancel )
		self.m_sdbSizer1OK.Bind( wx.EVT_BUTTON, self.onOK )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onCancel( self, event ):
		event.Skip()
	
	def onOK( self, event ):
		event.Skip()
	

###########################################################################
## Class custom
###########################################################################

class custom ( wx.Dialog ):
	
	def __init__( self, parent ):
		wx.Dialog.__init__ ( self, parent, id = wx.ID_ANY, title = u"Custom Mapping Builder", pos = wx.DefaultPosition, size = wx.Size( 850,600 ), style = wx.DEFAULT_DIALOG_STYLE )
		
		self.SetSizeHintsSz( wx.Size( 800,600 ), wx.DefaultSize )
		
		bSizer28 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer30 = wx.BoxSizer( wx.VERTICAL )
		
		sbSizer6 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"Pin Assignments" ), wx.VERTICAL )
		
		bSizer301 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer3011 = wx.BoxSizer( wx.HORIZONTAL )
		
		fgSizer1 = wx.FlexGridSizer( 11, 3, 0, 0 )
		fgSizer1.AddGrowableCol( 1 )
		fgSizer1.AddGrowableCol( 2 )
		fgSizer1.SetFlexibleDirection( wx.BOTH )
		fgSizer1.SetNonFlexibleGrowMode( wx.FLEX_GROWMODE_SPECIFIED )
		
		self.m_staticText24 = wx.StaticText( self, wx.ID_ANY, u"Pin", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText24.Wrap( -1 )
		self.m_staticText24.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer1.Add( self.m_staticText24, 0, wx.ALL, 5 )
		
		self.m_staticText25 = wx.StaticText( self, wx.ID_ANY, u"Function", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText25.Wrap( -1 )
		self.m_staticText25.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer1.Add( self.m_staticText25, 0, wx.ALL, 5 )
		
		self.m_staticText26 = wx.StaticText( self, wx.ID_ANY, u"Shifted Function", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText26.Wrap( -1 )
		self.m_staticText26.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer1.Add( self.m_staticText26, 0, wx.ALL, 5 )
		
		self.m_staticTextA1 = wx.StaticText( self, wx.ID_ANY, u"A1", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA1.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA1, 0, wx.ALL, 5 )
		
		A1Choices = []
		self.A1 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A1Choices, 0 )
		self.A1.SetSelection( -1 )
		fgSizer1.Add( self.A1, 0, wx.ALL, 5 )
		
		A1sChoices = []
		self.A1s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A1sChoices, 0 )
		self.A1s.SetSelection( 0 )
		fgSizer1.Add( self.A1s, 0, wx.ALL, 5 )
		
		self.m_staticTextA2 = wx.StaticText( self, wx.ID_ANY, u"A2", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA2.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA2, 0, wx.ALL, 5 )
		
		A2Choices = []
		self.A2 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A2Choices, 0 )
		self.A2.SetSelection( -1 )
		fgSizer1.Add( self.A2, 0, wx.ALL, 5 )
		
		A2sChoices = []
		self.A2s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A2sChoices, 0 )
		self.A2s.SetSelection( 0 )
		fgSizer1.Add( self.A2s, 0, wx.ALL, 5 )
		
		self.m_staticTextA3 = wx.StaticText( self, wx.ID_ANY, u"A3", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA3.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA3, 0, wx.ALL, 5 )
		
		A3Choices = []
		self.A3 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A3Choices, 0 )
		self.A3.SetSelection( -1 )
		fgSizer1.Add( self.A3, 0, wx.ALL, 5 )
		
		A3sChoices = []
		self.A3s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A3sChoices, 0 )
		self.A3s.SetSelection( 0 )
		fgSizer1.Add( self.A3s, 0, wx.ALL, 5 )
		
		self.m_staticTextA4 = wx.StaticText( self, wx.ID_ANY, u"A4", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA4.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA4, 0, wx.ALL, 5 )
		
		A4Choices = []
		self.A4 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A4Choices, 0 )
		self.A4.SetSelection( 0 )
		fgSizer1.Add( self.A4, 0, wx.ALL, 5 )
		
		A4sChoices = []
		self.A4s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A4sChoices, 0 )
		self.A4s.SetSelection( 0 )
		fgSizer1.Add( self.A4s, 0, wx.ALL, 5 )
		
		self.m_staticTextA5 = wx.StaticText( self, wx.ID_ANY, u"A5", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA5.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA5, 0, wx.ALL, 5 )
		
		A5Choices = []
		self.A5 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A5Choices, 0 )
		self.A5.SetSelection( -1 )
		fgSizer1.Add( self.A5, 0, wx.ALL, 5 )
		
		A5sChoices = []
		self.A5s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A5sChoices, 0 )
		self.A5s.SetSelection( 0 )
		fgSizer1.Add( self.A5s, 0, wx.ALL, 5 )
		
		self.m_staticTextA6 = wx.StaticText( self, wx.ID_ANY, u"A6", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA6.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA6, 0, wx.ALL, 5 )
		
		A6Choices = []
		self.A6 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A6Choices, 0 )
		self.A6.SetSelection( 0 )
		fgSizer1.Add( self.A6, 0, wx.ALL, 5 )
		
		A6sChoices = []
		self.A6s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A6sChoices, 0 )
		self.A6s.SetSelection( 0 )
		fgSizer1.Add( self.A6s, 0, wx.ALL, 5 )
		
		self.m_staticTextA7 = wx.StaticText( self, wx.ID_ANY, u"A7", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA7.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA7, 0, wx.ALL, 5 )
		
		A7Choices = []
		self.A7 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A7Choices, 0 )
		self.A7.SetSelection( 0 )
		fgSizer1.Add( self.A7, 0, wx.ALL, 5 )
		
		A7sChoices = []
		self.A7s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A7sChoices, 0 )
		self.A7s.SetSelection( 0 )
		fgSizer1.Add( self.A7s, 0, wx.ALL, 5 )
		
		self.m_staticTextA8 = wx.StaticText( self, wx.ID_ANY, u"A8", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA8.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA8, 0, wx.ALL, 5 )
		
		A8Choices = []
		self.A8 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A8Choices, 0 )
		self.A8.SetSelection( 0 )
		fgSizer1.Add( self.A8, 0, wx.ALL, 5 )
		
		A8sChoices = []
		self.A8s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A8sChoices, 0 )
		self.A8s.SetSelection( 0 )
		fgSizer1.Add( self.A8s, 0, wx.ALL, 5 )
		
		self.m_staticTextA9 = wx.StaticText( self, wx.ID_ANY, u"A9", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA9.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA9, 0, wx.ALL, 5 )
		
		A9Choices = []
		self.A9 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A9Choices, 0 )
		self.A9.SetSelection( 0 )
		fgSizer1.Add( self.A9, 0, wx.ALL, 5 )
		
		A9sChoices = []
		self.A9s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A9sChoices, 0 )
		self.A9s.SetSelection( 0 )
		fgSizer1.Add( self.A9s, 0, wx.ALL, 5 )
		
		self.m_staticTextA10 = wx.StaticText( self, wx.ID_ANY, u"A10", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextA10.Wrap( -1 )
		fgSizer1.Add( self.m_staticTextA10, 0, wx.ALL, 5 )
		
		A10Choices = []
		self.A10 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A10Choices, 0 )
		self.A10.SetSelection( 0 )
		fgSizer1.Add( self.A10, 0, wx.ALL, 5 )
		
		A10sChoices = []
		self.A10s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), A10sChoices, 0 )
		self.A10s.SetSelection( 0 )
		fgSizer1.Add( self.A10s, 0, wx.ALL, 5 )
		
		bSizer3011.Add( fgSizer1, 1, wx.EXPAND, 5 )
		
		self.m_staticline2 = wx.StaticLine( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.LI_VERTICAL )
		bSizer3011.Add( self.m_staticline2, 0, wx.ALL|wx.EXPAND, 20 )
		
		fgSizer2 = wx.FlexGridSizer( 11, 3, 0, 0 )
		fgSizer2.AddGrowableCol( 1 )
		fgSizer2.AddGrowableCol( 2 )
		fgSizer2.SetFlexibleDirection( wx.BOTH )
		fgSizer2.SetNonFlexibleGrowMode( wx.FLEX_GROWMODE_SPECIFIED )
		
		self.m_staticText241 = wx.StaticText( self, wx.ID_ANY, u"Pin", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText241.Wrap( -1 )
		self.m_staticText241.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer2.Add( self.m_staticText241, 0, wx.ALL, 5 )
		
		self.m_staticText251 = wx.StaticText( self, wx.ID_ANY, u"Function", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText251.Wrap( -1 )
		self.m_staticText251.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer2.Add( self.m_staticText251, 0, wx.ALL, 5 )
		
		self.m_staticText261 = wx.StaticText( self, wx.ID_ANY, u"Shifted Function", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText261.Wrap( -1 )
		self.m_staticText261.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer2.Add( self.m_staticText261, 0, wx.ALL, 5 )
		
		self.m_staticTextB1 = wx.StaticText( self, wx.ID_ANY, u"B1", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB1.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB1, 0, wx.ALL, 5 )
		
		B1Choices = []
		self.B1 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B1Choices, 0 )
		self.B1.SetSelection( -1 )
		fgSizer2.Add( self.B1, 0, wx.ALL, 5 )
		
		B1sChoices = []
		self.B1s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B1sChoices, 0 )
		self.B1s.SetSelection( 0 )
		fgSizer2.Add( self.B1s, 0, wx.ALL, 5 )
		
		self.m_staticTextB2 = wx.StaticText( self, wx.ID_ANY, u"B2", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB2.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB2, 0, wx.ALL, 5 )
		
		B2Choices = []
		self.B2 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B2Choices, 0 )
		self.B2.SetSelection( 0 )
		fgSizer2.Add( self.B2, 0, wx.ALL, 5 )
		
		B2sChoices = []
		self.B2s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B2sChoices, 0 )
		self.B2s.SetSelection( -1 )
		fgSizer2.Add( self.B2s, 0, wx.ALL, 5 )
		
		self.m_staticTextB3 = wx.StaticText( self, wx.ID_ANY, u"B3", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB3.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB3, 0, wx.ALL, 5 )
		
		B3Choices = []
		self.B3 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B3Choices, 0 )
		self.B3.SetSelection( 0 )
		fgSizer2.Add( self.B3, 0, wx.ALL, 5 )
		
		B3sChoices = []
		self.B3s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B3sChoices, 0 )
		self.B3s.SetSelection( 0 )
		fgSizer2.Add( self.B3s, 0, wx.ALL, 5 )
		
		self.m_staticTextB4 = wx.StaticText( self, wx.ID_ANY, u"B4", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB4.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB4, 0, wx.ALL, 5 )
		
		B4Choices = []
		self.B4 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B4Choices, 0 )
		self.B4.SetSelection( 0 )
		fgSizer2.Add( self.B4, 0, wx.ALL, 5 )
		
		B4sChoices = []
		self.B4s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B4sChoices, 0 )
		self.B4s.SetSelection( 0 )
		fgSizer2.Add( self.B4s, 0, wx.ALL, 5 )
		
		self.m_staticTextB5 = wx.StaticText( self, wx.ID_ANY, u"B5", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB5.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB5, 0, wx.ALL, 5 )
		
		B5Choices = []
		self.B5 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B5Choices, 0 )
		self.B5.SetSelection( 0 )
		fgSizer2.Add( self.B5, 0, wx.ALL, 5 )
		
		B5sChoices = []
		self.B5s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B5sChoices, 0 )
		self.B5s.SetSelection( 0 )
		fgSizer2.Add( self.B5s, 0, wx.ALL, 5 )
		
		self.m_staticTextB6 = wx.StaticText( self, wx.ID_ANY, u"B6", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB6.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB6, 0, wx.ALL, 5 )
		
		B6Choices = []
		self.B6 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B6Choices, 0 )
		self.B6.SetSelection( 0 )
		fgSizer2.Add( self.B6, 0, wx.ALL, 5 )
		
		B6sChoices = []
		self.B6s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B6sChoices, 0 )
		self.B6s.SetSelection( 0 )
		fgSizer2.Add( self.B6s, 0, wx.ALL, 5 )
		
		self.m_staticTextB7 = wx.StaticText( self, wx.ID_ANY, u"B7", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB7.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB7, 0, wx.ALL, 5 )
		
		B7Choices = []
		self.B7 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B7Choices, 0 )
		self.B7.SetSelection( 0 )
		fgSizer2.Add( self.B7, 0, wx.ALL, 5 )
		
		B7sChoices = []
		self.B7s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B7sChoices, 0 )
		self.B7s.SetSelection( 0 )
		fgSizer2.Add( self.B7s, 0, wx.ALL, 5 )
		
		self.m_staticTextB8 = wx.StaticText( self, wx.ID_ANY, u"B8", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB8.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB8, 0, wx.ALL, 5 )
		
		B8Choices = []
		self.B8 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B8Choices, 0 )
		self.B8.SetSelection( 0 )
		fgSizer2.Add( self.B8, 0, wx.ALL, 5 )
		
		B8sChoices = []
		self.B8s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B8sChoices, 0 )
		self.B8s.SetSelection( 0 )
		fgSizer2.Add( self.B8s, 0, wx.ALL, 5 )
		
		self.m_staticTextB9 = wx.StaticText( self, wx.ID_ANY, u"B9", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB9.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB9, 0, wx.ALL, 5 )
		
		B9Choices = []
		self.B9 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B9Choices, 0 )
		self.B9.SetSelection( 0 )
		fgSizer2.Add( self.B9, 0, wx.ALL, 5 )
		
		B9sChoices = []
		self.B9s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B9sChoices, 0 )
		self.B9s.SetSelection( 0 )
		fgSizer2.Add( self.B9s, 0, wx.ALL, 5 )
		
		self.m_staticTextB10 = wx.StaticText( self, wx.ID_ANY, u"B10", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextB10.Wrap( -1 )
		fgSizer2.Add( self.m_staticTextB10, 0, wx.ALL, 5 )
		
		B10Choices = []
		self.B10 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B10Choices, 0 )
		self.B10.SetSelection( 0 )
		fgSizer2.Add( self.B10, 0, wx.ALL, 5 )
		
		B10sChoices = []
		self.B10s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), B10sChoices, 0 )
		self.B10s.SetSelection( 0 )
		fgSizer2.Add( self.B10s, 0, wx.ALL, 5 )
		
		bSizer3011.Add( fgSizer2, 1, wx.EXPAND, 5 )
		
		bSizer301.Add( bSizer3011, 1, wx.ALL|wx.EXPAND, 10 )
		
		bSizer52 = wx.BoxSizer( wx.HORIZONTAL )
		
		
		bSizer52.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_xbox_combos = wx.HyperlinkCtrl( self, wx.ID_ANY, u"Help with advanced xbox combos", wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, wx.HL_DEFAULT_STYLE )
		bSizer52.Add( self.m_xbox_combos, 0, wx.ALL, 5 )
		
		bSizer301.Add( bSizer52, 0, wx.EXPAND, 5 )
		
		sbSizer6.Add( bSizer301, 1, wx.EXPAND, 5 )
		
		bSizer30.Add( sbSizer6, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer46 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_settings0 = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		sbSizer11 = wx.StaticBoxSizer( wx.StaticBox( self.m_settings0, wx.ID_ANY, u"Peripherals (Beta)" ), wx.VERTICAL )
		
		bSizer511 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_trackball1 = wx.CheckBox( self.m_settings0, wx.ID_ANY, u"Connect trackball* to pins A3/A7", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer511.Add( self.m_trackball1, 0, wx.ALL, 5 )
		
		self.m_trackball1_map = wx.Button( self.m_settings0, wx.ID_ANY, u"Assign Inputs", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_trackball1_map.Enable( False )
		
		bSizer511.Add( self.m_trackball1_map, 0, 0, 5 )
		
		
		bSizer511.AddSpacer( ( 20, 0), 0, wx.EXPAND, 5 )
		
		self.m_trackball2 = wx.CheckBox( self.m_settings0, wx.ID_ANY, u"Connect trackball* to pins A4/A8", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_trackball2.Enable( False )
		
		bSizer511.Add( self.m_trackball2, 0, wx.ALL, 5 )
		
		self.m_trackball2_map = wx.Button( self.m_settings0, wx.ID_ANY, u"Assign Inputs", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_trackball2_map.Enable( False )
		
		bSizer511.Add( self.m_trackball2_map, 0, 0, 5 )
		
		
		bSizer511.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_compatible_list = wx.HyperlinkCtrl( self.m_settings0, wx.ID_ANY, u"* Trackball and mouse compatibility information", wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, wx.HL_DEFAULT_STYLE )
		bSizer511.Add( self.m_compatible_list, 0, wx.ALL, 5 )
		
		sbSizer11.Add( bSizer511, 1, wx.ALL|wx.EXPAND, 5 )
		
		self.m_settings0.SetSizer( sbSizer11 )
		self.m_settings0.Layout()
		sbSizer11.Fit( self.m_settings0 )
		bSizer46.Add( self.m_settings0, 1, wx.EXPAND |wx.ALL, 5 )
		
		self.m_settings1 = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		sbSizer8 = wx.StaticBoxSizer( wx.StaticBox( self.m_settings1, wx.ID_ANY, u"Settings" ), wx.VERTICAL )
		
		bSettings = wx.BoxSizer( wx.HORIZONTAL )
		
		bSizer44 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_xbox_disable = wx.CheckBox( self.m_settings1, wx.ID_ANY, u"Disable start+back combination", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer44.Add( self.m_xbox_disable, 0, wx.ALL, 5 )
		
		bSettings.Add( bSizer44, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer461 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_xbox_autofire_delay_text1 = wx.StaticText( self.m_settings1, wx.ID_ANY, u"Autofire delay:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_xbox_autofire_delay_text1.Wrap( -1 )
		bSizer461.Add( self.m_xbox_autofire_delay_text1, 0, wx.ALL, 5 )
		
		m_xbox_autofire_delayChoices = [ u"5", u"10", u"15", u"20", u"25", u"50", u"100", u"250" ]
		self.m_xbox_autofire_delay = wx.ComboBox( self.m_settings1, wx.ID_ANY, u"15", wx.DefaultPosition, wx.Size( 40,-1 ), m_xbox_autofire_delayChoices, 0 )
		bSizer461.Add( self.m_xbox_autofire_delay, 0, 0, 5 )
		
		self.m_xbox_autofire_delay_text2 = wx.StaticText( self.m_settings1, wx.ID_ANY, u"ms", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_xbox_autofire_delay_text2.Wrap( -1 )
		bSizer461.Add( self.m_xbox_autofire_delay_text2, 0, wx.ALL, 5 )
		
		bSettings.Add( bSizer461, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer45 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_xbox_delay_text1 = wx.StaticText( self.m_settings1, wx.ID_ANY, u"Delay power to external peripherals by:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_xbox_delay_text1.Wrap( -1 )
		bSizer45.Add( self.m_xbox_delay_text1, 0, wx.ALL, 5 )
		
		m_xbox_delayChoices = [ u"0", u"3", u"5", u"10", u"15", u"20", u"25", u"30", u"45", u"60" ]
		self.m_xbox_delay = wx.ComboBox( self.m_settings1, wx.ID_ANY, u"15", wx.DefaultPosition, wx.Size( 40,-1 ), m_xbox_delayChoices, 0 )
		bSizer45.Add( self.m_xbox_delay, 0, 0, 5 )
		
		self.m_xbox_delay_text2 = wx.StaticText( self.m_settings1, wx.ID_ANY, u"seconds", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_xbox_delay_text2.Wrap( -1 )
		bSizer45.Add( self.m_xbox_delay_text2, 0, wx.ALL, 5 )
		
		bSettings.Add( bSizer45, 0, wx.ALL|wx.EXPAND, 5 )
		
		sbSizer8.Add( bSettings, 0, wx.EXPAND, 5 )
		
		self.m_settings1.SetSizer( sbSizer8 )
		self.m_settings1.Layout()
		sbSizer8.Fit( self.m_settings1 )
		bSizer46.Add( self.m_settings1, 1, wx.ALL|wx.EXPAND, 5 )
		
		self.m_settings2 = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer51 = wx.BoxSizer( wx.VERTICAL )
		
		sbSizer10 = wx.StaticBoxSizer( wx.StaticBox( self.m_settings2, wx.ID_ANY, u"MAME Presets" ), wx.HORIZONTAL )
		
		
		sbSizer10.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_MAME0 = wx.Button( self.m_settings2, wx.ID_ANY, u"MAME Player 1", wx.DefaultPosition, wx.Size( -1,20 ), 0 )
		sbSizer10.Add( self.m_MAME0, 0, wx.ALL, 5 )
		
		self.m_MAME1 = wx.Button( self.m_settings2, wx.ID_ANY, u"MAME Player 2", wx.DefaultPosition, wx.Size( -1,20 ), 0 )
		sbSizer10.Add( self.m_MAME1, 0, wx.ALL, 5 )
		
		self.m_MAME2 = wx.Button( self.m_settings2, wx.ID_ANY, u"MAME Player 3", wx.DefaultPosition, wx.Size( -1,20 ), 0 )
		sbSizer10.Add( self.m_MAME2, 0, wx.ALL, 5 )
		
		self.m_MAME3 = wx.Button( self.m_settings2, wx.ID_ANY, u"MAME Player 4", wx.DefaultPosition, wx.Size( -1,20 ), 0 )
		sbSizer10.Add( self.m_MAME3, 0, wx.ALL, 5 )
		
		self.m_MAME4 = wx.Button( self.m_settings2, wx.ID_ANY, u"MAME Players 1 && 2 Combined", wx.DefaultPosition, wx.Size( -1,20 ), 0 )
		sbSizer10.Add( self.m_MAME4, 0, wx.ALL, 5 )
		
		self.m_MAME5 = wx.Button( self.m_settings2, wx.ID_ANY, u"MAME Players 3 && 4 Combined", wx.DefaultPosition, wx.Size( -1,20 ), 0 )
		sbSizer10.Add( self.m_MAME5, 0, wx.ALL, 5 )
		
		
		sbSizer10.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		bSizer51.Add( sbSizer10, 1, wx.EXPAND, 5 )
		
		self.m_settings2.SetSizer( bSizer51 )
		self.m_settings2.Layout()
		bSizer51.Fit( self.m_settings2 )
		bSizer46.Add( self.m_settings2, 0, wx.ALL|wx.EXPAND, 5 )
		
		bSizer30.Add( bSizer46, 0, wx.EXPAND, 5 )
		
		
		bSizer30.AddSpacer( ( 0, 10), 0, wx.EXPAND, 5 )
		
		bSizer28.Add( bSizer30, 1, wx.EXPAND, 5 )
		
		bSizer37 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_default = wx.Button( self, wx.ID_ANY, u"Default", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		bSizer37.Add( self.m_default, 0, wx.RIGHT, 5 )
		
		self.m_preset1 = wx.Button( self, wx.ID_ANY, u"Preset 1", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		bSizer37.Add( self.m_preset1, 0, wx.RIGHT, 5 )
		
		self.m_preset2 = wx.Button( self, wx.ID_ANY, u" Preset 2", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		self.m_preset2.Hide()
		
		bSizer37.Add( self.m_preset2, 0, wx.RIGHT, 5 )
		
		self.m_staticline4 = wx.StaticLine( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.LI_VERTICAL )
		bSizer37.Add( self.m_staticline4, 0, wx.EXPAND |wx.ALL, 5 )
		
		self.m_clear = wx.Button( self, wx.ID_ANY, u"Clear", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		bSizer37.Add( self.m_clear, 0, wx.RIGHT, 5 )
		
		self.m_import = wx.Button( self, wx.ID_ANY, u"Import", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		bSizer37.Add( self.m_import, 0, wx.RIGHT, 5 )
		
		self.m_export = wx.Button( self, wx.ID_ANY, u"Export", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		bSizer37.Add( self.m_export, 0, 0, 5 )
		
		
		bSizer37.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_save = wx.Button( self, wx.ID_ANY, u"Save", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		bSizer37.Add( self.m_save, 0, wx.RIGHT, 5 )
		
		self.m_cancel = wx.Button( self, wx.ID_ANY, u"Cancel", wx.DefaultPosition, wx.Size( 60,-1 ), 0 )
		bSizer37.Add( self.m_cancel, 0, 0, 5 )
		
		bSizer28.Add( bSizer37, 0, wx.ALL|wx.EXPAND, 7 )
		
		self.SetSizer( bSizer28 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.A1.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A2.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A3.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A4.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A5.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A6.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A7.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A8.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A9.Bind( wx.EVT_CHOICE, self.onChoice )
		self.A10.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B1.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B2.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B3.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B4.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B5.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B6.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B7.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B8.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B9.Bind( wx.EVT_CHOICE, self.onChoice )
		self.B10.Bind( wx.EVT_CHOICE, self.onChoice )
		self.m_trackball1.Bind( wx.EVT_CHECKBOX, self.onTrackball1 )
		self.m_trackball1_map.Bind( wx.EVT_BUTTON, self.onAssign1 )
		self.m_trackball2.Bind( wx.EVT_CHECKBOX, self.onTrackball2 )
		self.m_trackball2_map.Bind( wx.EVT_BUTTON, self.onAssign2 )
		self.m_MAME0.Bind( wx.EVT_BUTTON, self.onPreset0 )
		self.m_MAME1.Bind( wx.EVT_BUTTON, self.onPreset1 )
		self.m_MAME2.Bind( wx.EVT_BUTTON, self.onPreset2 )
		self.m_MAME3.Bind( wx.EVT_BUTTON, self.onPreset3 )
		self.m_MAME4.Bind( wx.EVT_BUTTON, self.onPreset4 )
		self.m_MAME5.Bind( wx.EVT_BUTTON, self.onPreset5 )
		self.m_default.Bind( wx.EVT_BUTTON, self.onPreset0 )
		self.m_preset1.Bind( wx.EVT_BUTTON, self.onPreset1 )
		self.m_preset2.Bind( wx.EVT_BUTTON, self.onPreset2 )
		self.m_clear.Bind( wx.EVT_BUTTON, self.onClear )
		self.m_import.Bind( wx.EVT_BUTTON, self.onImport )
		self.m_export.Bind( wx.EVT_BUTTON, self.onExport )
		self.m_save.Bind( wx.EVT_BUTTON, self.onSave )
		self.m_cancel.Bind( wx.EVT_BUTTON, self.onCancel )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onChoice( self, event ):
		event.Skip()
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	def onTrackball1( self, event ):
		event.Skip()
	
	def onAssign1( self, event ):
		event.Skip()
	
	def onTrackball2( self, event ):
		event.Skip()
	
	def onAssign2( self, event ):
		event.Skip()
	
	def onPreset0( self, event ):
		event.Skip()
	
	def onPreset1( self, event ):
		event.Skip()
	
	def onPreset2( self, event ):
		event.Skip()
	
	def onPreset3( self, event ):
		event.Skip()
	
	def onPreset4( self, event ):
		event.Skip()
	
	def onPreset5( self, event ):
		event.Skip()
	
	
	
	
	def onClear( self, event ):
		event.Skip()
	
	def onImport( self, event ):
		event.Skip()
	
	def onExport( self, event ):
		event.Skip()
	
	def onSave( self, event ):
		event.Skip()
	
	def onCancel( self, event ):
		event.Skip()
	

###########################################################################
## Class update
###########################################################################

class update ( wx.Dialog ):
	
	def __init__( self, parent ):
		wx.Dialog.__init__ ( self, parent, id = wx.ID_ANY, title = u"KADE Loader Update", pos = wx.DefaultPosition, size = wx.Size( 425,150 ), style = wx.DEFAULT_DIALOG_STYLE )
		
		self.SetSizeHintsSz( wx.Size( 425,150 ), wx.DefaultSize )
		
		bSizer24 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer25 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer27 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_text1 = wx.StaticText( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_text1.Wrap( -1 )
		bSizer27.Add( self.m_text1, 0, wx.ALL, 5 )
		
		self.m_text2 = wx.StaticText( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_text2.Wrap( -1 )
		bSizer27.Add( self.m_text2, 0, wx.ALL, 5 )
		
		self.m_text3 = wx.StaticText( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_text3.Wrap( -1 )
		self.m_text3.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 90, False, wx.EmptyString ) )
		
		bSizer27.Add( self.m_text3, 0, wx.ALL, 5 )
		
		bSizer25.Add( bSizer27, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer26 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_check = wx.CheckBox( self, wx.ID_ANY, u"I want to switch off these update checks", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_check.SetFont( wx.Font( 7, 70, 90, 90, False, wx.EmptyString ) )
		
		bSizer26.Add( self.m_check, 0, wx.ALL, 5 )
		
		
		bSizer26.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_update = wx.Button( self, wx.ID_ANY, u"Get the Update", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer26.Add( self.m_update, 0, wx.RIGHT, 5 )
		
		self.m_cancel = wx.Button( self, wx.ID_ANY, u"Ignore", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer26.Add( self.m_cancel, 0, 0, 5 )
		
		bSizer25.Add( bSizer26, 0, wx.ALL|wx.EXPAND, 5 )
		
		bSizer24.Add( bSizer25, 1, wx.EXPAND, 5 )
		
		self.SetSizer( bSizer24 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.m_update.Bind( wx.EVT_BUTTON, self.onUpdate )
		self.m_cancel.Bind( wx.EVT_BUTTON, self.onCancel )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onUpdate( self, event ):
		event.Skip()
	
	def onCancel( self, event ):
		event.Skip()
	

###########################################################################
## Class about
###########################################################################

class about ( wx.Dialog ):
	
	def __init__( self, parent ):
		wx.Dialog.__init__ ( self, parent, id = wx.ID_ANY, title = u"About KADE Loader <version>", pos = wx.DefaultPosition, size = wx.Size( 375,585 ), style = wx.DEFAULT_DIALOG_STYLE )
		
		self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		
		bSizer37 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer39 = wx.BoxSizer( wx.HORIZONTAL )
		
		bSizer41 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_bitmap2 = wx.StaticBitmap( self, wx.ID_ANY, wx.Bitmap( u"images/KADE.png", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer41.Add( self.m_bitmap2, 0, wx.ALIGN_CENTER_HORIZONTAL, 5 )
		
		
		bSizer41.AddSpacer( ( 0, 10), 0, wx.EXPAND, 5 )
		
		self.m_staticText39 = wx.StaticText( self, wx.ID_ANY, u"A firmware programming utility for KADE devices \nby Jon Wilson\n\nKADE Development Team:\n• Jon Wilson (degenatrons@gmail.com)\n• Bruno Freitas (bootsector@ig.com.br)\n• Kevin Mackett (kevin@sharpfork.com)\n\nTesters and Contributors:\n• Rodney Black\n• Scott Hutchinson\n• John McNaught\n\nIf you like our open source software and hardware\nthen please consider making a small donation to help \nus improve KADE.\n", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText39.Wrap( -1 )
		self.m_staticText39.SetFont( wx.Font( 10, 70, 90, 90, False, wx.EmptyString ) )
		
		bSizer41.Add( self.m_staticText39, 0, wx.LEFT, 10 )
		
		sbSizer14 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"License Info" ), wx.VERTICAL )
		
		self.m_staticText391 = wx.StaticText( self, wx.ID_ANY, u"KADE software licensed under GNU/GPL V3", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText391.Wrap( -1 )
		self.m_staticText391.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 90, False, wx.EmptyString ) )
		
		sbSizer14.Add( self.m_staticText391, 0, wx.LEFT|wx.RIGHT|wx.TOP, 5 )
		
		self.m_hyperlink3 = wx.HyperlinkCtrl( self, wx.ID_ANY, u"http://www.gnu.org/licenses/gpl.html", u"http://www.gnu.org/licenses/gpl.html", wx.DefaultPosition, wx.DefaultSize, wx.HL_DEFAULT_STYLE )
		sbSizer14.Add( self.m_hyperlink3, 0, wx.BOTTOM|wx.LEFT|wx.RIGHT, 5 )
		
		self.m_staticText3911 = wx.StaticText( self, wx.ID_ANY, u"KADE hardware licensed under Creative Commons (CC BY-SA 3.0)", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText3911.Wrap( -1 )
		self.m_staticText3911.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 90, False, wx.EmptyString ) )
		
		sbSizer14.Add( self.m_staticText3911, 0, wx.LEFT|wx.RIGHT|wx.TOP, 5 )
		
		self.m_hyperlink4 = wx.HyperlinkCtrl( self, wx.ID_ANY, u"http://creativecommons.org/licenses/by-sa/3.0/", u"http://creativecommons.org/licenses/by-sa/3.0/", wx.DefaultPosition, wx.DefaultSize, wx.HL_DEFAULT_STYLE )
		sbSizer14.Add( self.m_hyperlink4, 0, wx.BOTTOM|wx.LEFT|wx.RIGHT, 5 )
		
		bSizer41.Add( sbSizer14, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer39.Add( bSizer41, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer37.Add( bSizer39, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer38 = wx.BoxSizer( wx.HORIZONTAL )
		
		
		bSizer38.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_donate = wx.Button( self, wx.ID_ANY, u"Donate", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer38.Add( self.m_donate, 0, wx.ALL, 5 )
		
		self.m_ok = wx.Button( self, wx.ID_ANY, u"OK", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_ok.SetDefault() 
		bSizer38.Add( self.m_ok, 0, wx.ALL, 5 )
		
		bSizer37.Add( bSizer38, 0, wx.EXPAND, 5 )
		
		self.SetSizer( bSizer37 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.m_donate.Bind( wx.EVT_BUTTON, self.onDonate )
		self.m_ok.Bind( wx.EVT_BUTTON, self.onOK )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onDonate( self, event ):
		event.Skip()
	
	def onOK( self, event ):
		event.Skip()
	

###########################################################################
## Class trackball
###########################################################################

class trackball ( wx.Dialog ):
	
	def __init__( self, parent ):
		wx.Dialog.__init__ ( self, parent, id = wx.ID_ANY, title = u"Configure Trackball and Mouse (BETA)", pos = wx.DefaultPosition, size = wx.Size( 290,400 ), style = wx.DEFAULT_DIALOG_STYLE )
		
		self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		
		bSizer47 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer53 = wx.BoxSizer( wx.VERTICAL )
		
		sbSizer10 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"Device 1" ), wx.VERTICAL )
		
		self.m_panel8 = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		gSizer2 = wx.GridSizer( 2, 2, 0, 0 )
		
		bSizer491 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_trackball1 = wx.RadioButton( self.m_panel8, wx.ID_ANY, u"Trackball", wx.DefaultPosition, wx.DefaultSize, wx.RB_GROUP )
		bSizer491.Add( self.m_trackball1, 0, wx.ALL, 5 )
		
		self.m_spinner1 = wx.RadioButton( self.m_panel8, wx.ID_ANY, u"Spinner", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer491.Add( self.m_spinner1, 0, wx.ALL, 5 )
		
		self.m_mouse1 = wx.RadioButton( self.m_panel8, wx.ID_ANY, u"Mouse", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer491.Add( self.m_mouse1, 0, wx.ALL, 5 )
		
		gSizer2.Add( bSizer491, 1, wx.EXPAND, 5 )
		
		
		gSizer2.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_staticText56 = wx.StaticText( self.m_panel8, wx.ID_ANY, u"KADE Pins:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText56.Wrap( -1 )
		gSizer2.Add( self.m_staticText56, 0, wx.ALL, 5 )
		
		self.m_pins1 = wx.TextCtrl( self.m_panel8, wx.ID_ANY, u"A3 Data & A7 Clock", wx.DefaultPosition, wx.Size( 140,-1 ), 0 )
		self.m_pins1.Enable( False )
		
		gSizer2.Add( self.m_pins1, 0, wx.ALIGN_RIGHT|wx.ALL, 5 )
		
		self.m_staticText42 = wx.StaticText( self.m_panel8, wx.ID_ANY, u"Resolution:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText42.Wrap( -1 )
		gSizer2.Add( self.m_staticText42, 0, wx.ALL, 5 )
		
		m_counts1Choices = [ u"1 count/mm", u"2 counts/ mm", u"4 counts/ mm", u"8 counts/ mm" ]
		self.m_counts1 = wx.Choice( self.m_panel8, wx.ID_ANY, wx.DefaultPosition, wx.Size( 140,-1 ), m_counts1Choices, 0 )
		self.m_counts1.SetSelection( 0 )
		gSizer2.Add( self.m_counts1, 0, wx.ALIGN_RIGHT|wx.ALL, 5 )
		
		self.m_staticText421 = wx.StaticText( self.m_panel8, wx.ID_ANY, u"Sample Rate:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText421.Wrap( -1 )
		gSizer2.Add( self.m_staticText421, 0, wx.ALL, 5 )
		
		m_samples1Choices = [ u"10 samples/second", u"20 samples/second", u"40 samples/second", u"60 samples/second", u"80 samples/second", u"100 samples/second", u"200 samples/second" ]
		self.m_samples1 = wx.Choice( self.m_panel8, wx.ID_ANY, wx.DefaultPosition, wx.Size( 140,-1 ), m_samples1Choices, 0 )
		self.m_samples1.SetSelection( 0 )
		gSizer2.Add( self.m_samples1, 0, wx.ALIGN_RIGHT|wx.ALL, 5 )
		
		self.m_panel8.SetSizer( gSizer2 )
		self.m_panel8.Layout()
		gSizer2.Fit( self.m_panel8 )
		sbSizer10.Add( self.m_panel8, 1, wx.EXPAND |wx.ALL, 5 )
		
		bSizer53.Add( sbSizer10, 1, wx.ALL|wx.EXPAND, 5 )
		
		
		bSizer53.AddSpacer( ( 0, 3), 0, wx.EXPAND, 5 )
		
		sbSizer101 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"Device 2" ), wx.VERTICAL )
		
		self.m_panel7 = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.m_panel7.Enable( False )
		
		gSizer21 = wx.GridSizer( 2, 2, 0, 0 )
		
		bSizer4911 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_trackball2 = wx.RadioButton( self.m_panel7, wx.ID_ANY, u"Trackball", wx.DefaultPosition, wx.DefaultSize, wx.RB_GROUP )
		self.m_trackball2.Enable( False )
		
		bSizer4911.Add( self.m_trackball2, 0, wx.ALL, 5 )
		
		self.m_spinner2 = wx.RadioButton( self.m_panel7, wx.ID_ANY, u"Spinner", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_spinner2.Enable( False )
		
		bSizer4911.Add( self.m_spinner2, 0, wx.ALL, 5 )
		
		self.m_mouse2 = wx.RadioButton( self.m_panel7, wx.ID_ANY, u"Mouse", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_mouse2.Enable( False )
		
		bSizer4911.Add( self.m_mouse2, 0, wx.ALL, 5 )
		
		gSizer21.Add( bSizer4911, 1, wx.EXPAND, 5 )
		
		
		gSizer21.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_staticText561 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"KADE Pins:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText561.Wrap( -1 )
		self.m_staticText561.Enable( False )
		
		gSizer21.Add( self.m_staticText561, 0, wx.ALL, 5 )
		
		self.m_pins2 = wx.TextCtrl( self.m_panel7, wx.ID_ANY, u"A4 Data & A8 Clock", wx.DefaultPosition, wx.Size( 140,-1 ), 0 )
		self.m_pins2.Enable( False )
		
		gSizer21.Add( self.m_pins2, 0, wx.ALIGN_RIGHT|wx.ALL, 5 )
		
		self.m_staticText422 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"Resolution:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText422.Wrap( -1 )
		self.m_staticText422.Enable( False )
		
		gSizer21.Add( self.m_staticText422, 0, wx.ALL, 5 )
		
		m_counts2Choices = [ u"1 count/mm", u"2 counts/ mm", u"4 counts/ mm", u"8 counts/ mm" ]
		self.m_counts2 = wx.Choice( self.m_panel7, wx.ID_ANY, wx.DefaultPosition, wx.Size( 140,-1 ), m_counts2Choices, 0 )
		self.m_counts2.SetSelection( 0 )
		self.m_counts2.Enable( False )
		
		gSizer21.Add( self.m_counts2, 0, wx.ALIGN_RIGHT|wx.ALL, 5 )
		
		self.m_staticText4211 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"Sample Rate:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText4211.Wrap( -1 )
		self.m_staticText4211.Enable( False )
		
		gSizer21.Add( self.m_staticText4211, 0, wx.ALL, 5 )
		
		m_samples2Choices = [ u"10 samples/second", u"20 samples/second", u"40 samples/second", u"60 samples/second", u"80 samples/second", u"100 samples/second", u"200 samples/second" ]
		self.m_samples2 = wx.Choice( self.m_panel7, wx.ID_ANY, wx.DefaultPosition, wx.Size( 140,-1 ), m_samples2Choices, 0 )
		self.m_samples2.SetSelection( 0 )
		self.m_samples2.Enable( False )
		
		gSizer21.Add( self.m_samples2, 0, wx.ALIGN_RIGHT|wx.ALL, 5 )
		
		self.m_panel7.SetSizer( gSizer21 )
		self.m_panel7.Layout()
		gSizer21.Fit( self.m_panel7 )
		sbSizer101.Add( self.m_panel7, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer53.Add( sbSizer101, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer49 = wx.BoxSizer( wx.HORIZONTAL )
		
		
		bSizer49.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_button25 = wx.Button( self, wx.ID_ANY, u"OK", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer49.Add( self.m_button25, 0, wx.TOP, 5 )
		
		self.m_button26 = wx.Button( self, wx.ID_ANY, u"Cancel", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer49.Add( self.m_button26, 0, wx.ALL, 5 )
		
		bSizer53.Add( bSizer49, 0, wx.EXPAND, 5 )
		
		bSizer47.Add( bSizer53, 1, wx.ALL|wx.EXPAND, 5 )
		
		self.SetSizer( bSizer47 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.m_trackball1.Bind( wx.EVT_RADIOBUTTON, self.onTrackball1 )
		self.m_spinner1.Bind( wx.EVT_RADIOBUTTON, self.onSpinner1 )
		self.m_mouse1.Bind( wx.EVT_RADIOBUTTON, self.onMouse1 )
		self.m_trackball2.Bind( wx.EVT_RADIOBUTTON, self.onTrackball2 )
		self.m_spinner2.Bind( wx.EVT_RADIOBUTTON, self.onSpinner2 )
		self.m_mouse2.Bind( wx.EVT_RADIOBUTTON, self.onMouse2 )
		self.m_button25.Bind( wx.EVT_BUTTON, self.onOK )
		self.m_button26.Bind( wx.EVT_BUTTON, self.onCancel )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onTrackball1( self, event ):
		event.Skip()
	
	def onSpinner1( self, event ):
		event.Skip()
	
	def onMouse1( self, event ):
		event.Skip()
	
	def onTrackball2( self, event ):
		event.Skip()
	
	def onSpinner2( self, event ):
		event.Skip()
	
	def onMouse2( self, event ):
		event.Skip()
	
	def onOK( self, event ):
		event.Skip()
	
	def onCancel( self, event ):
		event.Skip()
	

###########################################################################
## Class trackball_inputs
###########################################################################

class trackball_inputs ( wx.Dialog ):
	
	def __init__( self, parent ):
		wx.Dialog.__init__ ( self, parent, id = wx.ID_ANY, title = u"Assign Device Inputs", pos = wx.DefaultPosition, size = wx.Size( 425,300 ), style = wx.DEFAULT_DIALOG_STYLE )
		
		self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		
		bSizer54 = wx.BoxSizer( wx.VERTICAL )
		
		sbSizer12 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"Axis Assignment" ), wx.HORIZONTAL )
		
		self.m_left = wx.RadioButton( self, wx.ID_ANY, u"Left Analog Stick", wx.DefaultPosition, wx.DefaultSize, wx.RB_GROUP )
		sbSizer12.Add( self.m_left, 0, wx.ALL, 10 )
		
		self.m_right = wx.RadioButton( self, wx.ID_ANY, u"Right Analog Stick", wx.DefaultPosition, wx.DefaultSize, 0 )
		sbSizer12.Add( self.m_right, 0, wx.ALL, 10 )
		
		bSizer54.Add( sbSizer12, 0, wx.ALL|wx.EXPAND, 5 )
		
		sbSizer13 = wx.StaticBoxSizer( wx.StaticBox( self, wx.ID_ANY, u"Button Assignments" ), wx.VERTICAL )
		
		fgSizer3 = wx.FlexGridSizer( 4, 3, 0, 0 )
		fgSizer3.SetFlexibleDirection( wx.BOTH )
		fgSizer3.SetNonFlexibleGrowMode( wx.FLEX_GROWMODE_SPECIFIED )
		
		self.m_staticText24 = wx.StaticText( self, wx.ID_ANY, u"Button", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText24.Wrap( -1 )
		self.m_staticText24.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer3.Add( self.m_staticText24, 0, wx.ALL, 5 )
		
		self.m_staticText251 = wx.StaticText( self, wx.ID_ANY, u"Function", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText251.Wrap( -1 )
		self.m_staticText251.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer3.Add( self.m_staticText251, 0, wx.ALL, 5 )
		
		self.m_staticText261 = wx.StaticText( self, wx.ID_ANY, u"Shifted Function", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText261.Wrap( -1 )
		self.m_staticText261.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 92, True, wx.EmptyString ) )
		
		fgSizer3.Add( self.m_staticText261, 0, wx.ALL, 5 )
		
		self.m_staticTextBUT1 = wx.StaticText( self, wx.ID_ANY, u"1", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextBUT1.Wrap( -1 )
		self.m_staticTextBUT1.SetFont( wx.Font( 9, 70, 90, 90, False, wx.EmptyString ) )
		
		fgSizer3.Add( self.m_staticTextBUT1, 0, wx.ALIGN_CENTER_HORIZONTAL|wx.ALL, 5 )
		
		BUT1Choices = []
		self.BUT1 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), BUT1Choices, 0 )
		self.BUT1.SetSelection( -1 )
		fgSizer3.Add( self.BUT1, 0, wx.ALL, 5 )
		
		BUT1sChoices = []
		self.BUT1s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), BUT1sChoices, 0 )
		self.BUT1s.SetSelection( 0 )
		fgSizer3.Add( self.BUT1s, 0, wx.ALL, 5 )
		
		self.m_staticTextBUT2 = wx.StaticText( self, wx.ID_ANY, u"2", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextBUT2.Wrap( -1 )
		self.m_staticTextBUT2.SetFont( wx.Font( 9, 70, 90, 90, False, wx.EmptyString ) )
		
		fgSizer3.Add( self.m_staticTextBUT2, 0, wx.ALIGN_CENTER_HORIZONTAL|wx.ALL, 5 )
		
		BUT2Choices = []
		self.BUT2 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), BUT2Choices, 0 )
		self.BUT2.SetSelection( -1 )
		fgSizer3.Add( self.BUT2, 0, wx.ALL, 5 )
		
		BUT2sChoices = []
		self.BUT2s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), BUT2sChoices, 0 )
		self.BUT2s.SetSelection( 0 )
		fgSizer3.Add( self.BUT2s, 0, wx.ALL, 5 )
		
		self.m_staticTextBUT3 = wx.StaticText( self, wx.ID_ANY, u"3", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticTextBUT3.Wrap( -1 )
		self.m_staticTextBUT3.SetFont( wx.Font( 9, 70, 90, 90, False, wx.EmptyString ) )
		
		fgSizer3.Add( self.m_staticTextBUT3, 0, wx.ALIGN_CENTER_HORIZONTAL|wx.ALL, 5 )
		
		BUT3Choices = []
		self.BUT3 = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), BUT3Choices, 0 )
		self.BUT3.SetSelection( -1 )
		fgSizer3.Add( self.BUT3, 0, wx.ALL, 5 )
		
		BUT3sChoices = []
		self.BUT3s = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 160,-1 ), BUT3sChoices, 0 )
		self.BUT3s.SetSelection( 0 )
		fgSizer3.Add( self.BUT3s, 0, wx.ALL, 5 )
		
		
		fgSizer3.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		
		fgSizer3.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		
		fgSizer3.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		sbSizer13.Add( fgSizer3, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer54.Add( sbSizer13, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer55 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_button28 = wx.Button( self, wx.ID_ANY, u"Clear", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer55.Add( self.m_button28, 0, wx.ALL, 5 )
		
		self.m_button281 = wx.Button( self, wx.ID_ANY, u"Configure Device...", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_button281.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 90, False, wx.EmptyString ) )
		
		bSizer55.Add( self.m_button281, 0, wx.ALL, 5 )
		
		
		bSizer55.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_button29 = wx.Button( self, wx.ID_ANY, u"OK", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer55.Add( self.m_button29, 0, wx.ALL, 5 )
		
		self.m_button30 = wx.Button( self, wx.ID_ANY, u"Cancel", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer55.Add( self.m_button30, 0, wx.ALL, 5 )
		
		bSizer54.Add( bSizer55, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.SetSizer( bSizer54 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.BUT1.Bind( wx.EVT_CHOICE, self.onChoice )
		self.BUT1s.Bind( wx.EVT_CHOICE, self.onChoice )
		self.BUT2.Bind( wx.EVT_CHOICE, self.onChoice )
		self.BUT2s.Bind( wx.EVT_CHOICE, self.onChoice )
		self.BUT3.Bind( wx.EVT_CHOICE, self.onChoice )
		self.BUT3s.Bind( wx.EVT_CHOICE, self.onChoice )
		self.m_button28.Bind( wx.EVT_BUTTON, self.onClear )
		self.m_button281.Bind( wx.EVT_BUTTON, self.onConfigure )
		self.m_button29.Bind( wx.EVT_BUTTON, self.onOK )
		self.m_button30.Bind( wx.EVT_BUTTON, self.onCancel )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onChoice( self, event ):
		event.Skip()
	
	
	
	
	
	
	def onClear( self, event ):
		event.Skip()
	
	def onConfigure( self, event ):
		event.Skip()
	
	def onOK( self, event ):
		event.Skip()
	
	def onCancel( self, event ):
		event.Skip()
	

###########################################################################
## Class programmed
###########################################################################

class programmed ( wx.Dialog ):
	
	def __init__( self, parent ):
		wx.Dialog.__init__ ( self, parent, id = wx.ID_ANY, title = u"Congratulations", pos = wx.DefaultPosition, size = wx.Size( 395,270 ), style = wx.CAPTION )
		
		self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		self.SetBackgroundColour( wx.Colour( 209, 255, 164 ) )
		
		bSizer37 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer39 = wx.BoxSizer( wx.HORIZONTAL )
		
		bSizer41 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_bitmap2 = wx.StaticBitmap( self, wx.ID_ANY, wx.Bitmap( u"images/KADE.png", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer41.Add( self.m_bitmap2, 0, wx.ALIGN_CENTER_HORIZONTAL, 5 )
		
		
		bSizer41.AddSpacer( ( 0, 15), 0, wx.EXPAND, 5 )
		
		self.m_staticText39 = wx.StaticText( self, wx.ID_ANY, u"Your device is programmed and ready for use.\n\nEnjoy.", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTRE )
		self.m_staticText39.Wrap( -1 )
		self.m_staticText39.SetFont( wx.Font( 10, 70, 90, 92, False, wx.EmptyString ) )
		
		bSizer41.Add( self.m_staticText39, 0, wx.ALL|wx.EXPAND, 5 )
		
		
		bSizer41.AddSpacer( ( 0, 25), 0, wx.EXPAND, 5 )
		
		bSizer39.Add( bSizer41, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer37.Add( bSizer39, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer38 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_kit = wx.CheckBox( self, wx.ID_ANY, u"Click here to use the Keyboard Input Tester utility", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_kit.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 90, False, wx.EmptyString ) )
		
		bSizer38.Add( self.m_kit, 0, wx.ALIGN_BOTTOM|wx.ALL, 10 )
		
		
		bSizer38.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_ok = wx.Button( self, wx.ID_ANY, u"OK", wx.DefaultPosition, wx.DefaultSize, wx.NO_BORDER )
		self.m_ok.SetFont( wx.Font( wx.NORMAL_FONT.GetPointSize(), 70, 90, 90, False, wx.EmptyString ) )
		
		bSizer38.Add( self.m_ok, 0, wx.ALL, 5 )
		
		bSizer37.Add( bSizer38, 0, wx.EXPAND, 5 )
		
		self.SetSizer( bSizer37 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.m_ok.Bind( wx.EVT_BUTTON, self.onOK )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onOK( self, event ):
		event.Skip()
	

