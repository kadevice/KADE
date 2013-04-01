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
## Class joytest
###########################################################################

class joytest ( wx.Frame ):
	
	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = u"Joystick Input Tester (Work in Progress)", pos = wx.DefaultPosition, size = wx.Size( 750,375 ), style = wx.CAPTION|wx.DEFAULT_FRAME_STYLE|wx.STAY_ON_TOP|wx.TAB_TRAVERSAL )
		
		self.SetSizeHintsSz( wx.Size( 750,305 ), wx.Size( 800,-1 ) )
		
		bSizer19 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_panel7 = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer29 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer30 = wx.BoxSizer( wx.HORIZONTAL )
		
		bSizer30.SetMinSize( wx.Size( -1,250 ) ) 
		sbSizer6 = wx.StaticBoxSizer( wx.StaticBox( self.m_panel7, wx.ID_ANY, u"Directional Pad" ), wx.VERTICAL )
		
		bSizer32 = wx.BoxSizer( wx.HORIZONTAL )
		
		
		bSizer32.AddSpacer( ( 12, 0), 0, wx.EXPAND, 5 )
		
		self.m_dpad = wx.StaticBitmap( self.m_panel7, wx.ID_ANY, wx.Bitmap( u"images/dpad_none.gif", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer32.Add( self.m_dpad, 0, wx.ALL, 5 )
		
		
		bSizer32.AddSpacer( ( 11, 0), 1, wx.EXPAND, 5 )
		
		sbSizer6.Add( bSizer32, 0, wx.ALL|wx.EXPAND, 5 )
		
		bSizer30.Add( sbSizer6, 1, wx.ALL|wx.EXPAND, 5 )
		
		sbSizer4 = wx.StaticBoxSizer( wx.StaticBox( self.m_panel7, wx.ID_ANY, u"Left Analog Stick " ), wx.VERTICAL )
		
		bSizer28 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_stick1 = wx.Panel( self.m_panel7, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.WANTS_CHARS )
		bSizer16 = wx.BoxSizer( wx.VERTICAL )
		
		fgSizer1 = wx.FlexGridSizer( 2, 2, 0, 0 )
		fgSizer1.SetFlexibleDirection( wx.BOTH )
		fgSizer1.SetNonFlexibleGrowMode( wx.FLEX_GROWMODE_SPECIFIED )
		
		
		fgSizer1.AddSpacer( ( 10, 10), 0, 0, 5 )
		
		self.m_bitmap2 = wx.StaticBitmap( self.m_stick1, wx.ID_ANY, wx.Bitmap( u"images/x_axis.gif", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer1.Add( self.m_bitmap2, 0, wx.LEFT, 13 )
		
		self.m_bitmap3 = wx.StaticBitmap( self.m_stick1, wx.ID_ANY, wx.Bitmap( u"images/y_axis.gif", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer1.Add( self.m_bitmap3, 0, wx.TOP, 13 )
		
		bSizer14 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer14.SetMinSize( wx.Size( 182,182 ) ) 
		self.m_panel2 = wx.Panel( self.m_stick1, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.m_panel2.SetBackgroundColour( wx.Colour( 231, 231, 231 ) )
		
		bSizer18 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_pointer1 = wx.StaticBitmap( self.m_panel2, wx.ID_ANY, wx.Bitmap( u"images/sight.gif", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer18.Add( self.m_pointer1, 0, 0, 0 )
		
		self.m_panel2.SetSizer( bSizer18 )
		self.m_panel2.Layout()
		bSizer18.Fit( self.m_panel2 )
		bSizer14.Add( self.m_panel2, 1, wx.ALL|wx.EXPAND, 5 )
		
		fgSizer1.Add( bSizer14, 0, 0, 0 )
		
		bSizer16.Add( fgSizer1, 1, wx.ALL|wx.EXPAND, 5 )
		
		self.m_stick1.SetSizer( bSizer16 )
		self.m_stick1.Layout()
		bSizer16.Fit( self.m_stick1 )
		bSizer28.Add( self.m_stick1, 1, wx.EXPAND |wx.ALL, 0 )
		
		sbSizer4.Add( bSizer28, 0, wx.EXPAND, 5 )
		
		bSizer30.Add( sbSizer4, 1, wx.ALL|wx.EXPAND, 5 )
		
		sbSizer5 = wx.StaticBoxSizer( wx.StaticBox( self.m_panel7, wx.ID_ANY, u"Right Analog Stick" ), wx.VERTICAL )
		
		bSizer191 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_stick2 = wx.Panel( self.m_panel7, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.WANTS_CHARS )
		bSizer161 = wx.BoxSizer( wx.VERTICAL )
		
		fgSizer11 = wx.FlexGridSizer( 2, 2, 0, 0 )
		fgSizer11.SetFlexibleDirection( wx.BOTH )
		fgSizer11.SetNonFlexibleGrowMode( wx.FLEX_GROWMODE_SPECIFIED )
		
		
		fgSizer11.AddSpacer( ( 10, 10), 0, 0, 5 )
		
		self.m_bitmap21 = wx.StaticBitmap( self.m_stick2, wx.ID_ANY, wx.Bitmap( u"images/x_axis.gif", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer11.Add( self.m_bitmap21, 0, wx.LEFT, 13 )
		
		self.m_bitmap31 = wx.StaticBitmap( self.m_stick2, wx.ID_ANY, wx.Bitmap( u"images/y_axis.gif", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		fgSizer11.Add( self.m_bitmap31, 0, wx.TOP, 13 )
		
		bSizer141 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer141.SetMinSize( wx.Size( 182,182 ) ) 
		self.m_panel21 = wx.Panel( self.m_stick2, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.m_panel21.SetBackgroundColour( wx.Colour( 231, 231, 231 ) )
		
		bSizer181 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_pointer2 = wx.StaticBitmap( self.m_panel21, wx.ID_ANY, wx.Bitmap( u"images/sight.gif", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer181.Add( self.m_pointer2, 0, 0, 0 )
		
		self.m_panel21.SetSizer( bSizer181 )
		self.m_panel21.Layout()
		bSizer181.Fit( self.m_panel21 )
		bSizer141.Add( self.m_panel21, 1, wx.ALL|wx.EXPAND, 5 )
		
		fgSizer11.Add( bSizer141, 0, 0, 0 )
		
		bSizer161.Add( fgSizer11, 1, wx.ALL|wx.EXPAND, 5 )
		
		self.m_stick2.SetSizer( bSizer161 )
		self.m_stick2.Layout()
		bSizer161.Fit( self.m_stick2 )
		bSizer191.Add( self.m_stick2, 1, wx.EXPAND |wx.ALL, 0 )
		
		sbSizer5.Add( bSizer191, 0, 0, 5 )
		
		bSizer30.Add( sbSizer5, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer29.Add( bSizer30, 0, wx.EXPAND, 5 )
		
		bSizer33 = wx.BoxSizer( wx.VERTICAL )
		
		sbSizer7 = wx.StaticBoxSizer( wx.StaticBox( self.m_panel7, wx.ID_ANY, u"Buttons" ), wx.VERTICAL )
		
		fgSizer6 = wx.FlexGridSizer( 2, 7, 0, 0 )
		fgSizer6.AddGrowableCol( 0 )
		fgSizer6.AddGrowableCol( 1 )
		fgSizer6.AddGrowableCol( 2 )
		fgSizer6.AddGrowableCol( 3 )
		fgSizer6.AddGrowableCol( 4 )
		fgSizer6.AddGrowableCol( 5 )
		fgSizer6.AddGrowableCol( 6 )
		fgSizer6.AddGrowableRow( 0 )
		fgSizer6.AddGrowableRow( 1 )
		fgSizer6.SetFlexibleDirection( wx.BOTH )
		fgSizer6.SetNonFlexibleGrowMode( wx.FLEX_GROWMODE_SPECIFIED )
		
		self.m_1 = wx.Button( self.m_panel7, wx.ID_ANY, u"1", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_1.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_1.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_1, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_2 = wx.Button( self.m_panel7, wx.ID_ANY, u"2", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_2.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_2.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_2, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_3 = wx.Button( self.m_panel7, wx.ID_ANY, u"3", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_3.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_3.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_3, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_4 = wx.Button( self.m_panel7, wx.ID_ANY, u"4", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_4.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_4.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_4, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_5 = wx.Button( self.m_panel7, wx.ID_ANY, u"5", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_5.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_5.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_5, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_6 = wx.Button( self.m_panel7, wx.ID_ANY, u"6", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_6.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_6.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_6, 0, wx.ALL|wx.EXPAND, 5 )
		
		
		fgSizer6.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_7 = wx.Button( self.m_panel7, wx.ID_ANY, u"7", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_7.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_7.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_7, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_8 = wx.Button( self.m_panel7, wx.ID_ANY, u"8", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_8.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_8.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_8, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_9 = wx.Button( self.m_panel7, wx.ID_ANY, u"9", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_9.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_9.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_9, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_10 = wx.Button( self.m_panel7, wx.ID_ANY, u"10", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_10.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_10.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_10, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_11 = wx.Button( self.m_panel7, wx.ID_ANY, u"11", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_11.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_11.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_11, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_12 = wx.Button( self.m_panel7, wx.ID_ANY, u"12", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_12.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_12.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_12, 0, wx.ALL|wx.EXPAND, 5 )
		
		self.m_13 = wx.Button( self.m_panel7, wx.ID_ANY, u"13", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_13.SetForegroundColour( wx.Colour( 112, 112, 112 ) )
		self.m_13.SetBackgroundColour( wx.Colour( 240, 240, 240 ) )
		
		fgSizer6.Add( self.m_13, 1, wx.ALL|wx.EXPAND, 5 )
		
		sbSizer7.Add( fgSizer6, 1, wx.EXPAND, 5 )
		
		bSizer33.Add( sbSizer7, 1, wx.ALL|wx.EXPAND, 5 )
		
		bSizer29.Add( bSizer33, 1, wx.EXPAND, 5 )
		
		self.m_panel7.SetSizer( bSizer29 )
		self.m_panel7.Layout()
		bSizer29.Fit( self.m_panel7 )
		bSizer19.Add( self.m_panel7, 1, wx.EXPAND, 5 )
		
		self.SetSizer( bSizer19 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.Bind( wx.EVT_UPDATE_UI, self.onUI )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onUI( self, event ):
		event.Skip()
	

