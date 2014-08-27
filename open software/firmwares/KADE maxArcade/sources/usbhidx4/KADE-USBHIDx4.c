/*   .k8GOGGNqkSFS5XkqXPSkSkkqXXFS5kSkSS15U22F2515U2uujuu1U1u2U1U2uUuFS.     
   :0qE     JS5uuJuuFFX51jU2SSk12jU2SSXF5uuu15SFS5k12ujj21S5kFS5S12jJYu11    
  5XS:        1UYYLu.   vUUX    U22r     SUF         SUF           ;YYLuU5   
 1F5i  NNSkS7  2uLJui   51u     S5.      .PX         .XX           LJvLLu1.  
 kUk  0iLk5FFu vuYY2:   5F    Xkk7        78    E0    i0    GEXPXk2uLLvLLuk  
X25, 8O   2kX0  5YJUi   M    555    PkXk   i    q1FU   7    ONNkP12YLvLvLYS  
S25  8888  888  5uY5         FuS    PS50   .    FuUU   7          uJvLvLLJ2i 
kUF             SJjU.      P02UF    P25k   .    Su2Y   v          2LLvLvLL17 
S21  XJj88  0u  1uY2.        X2k           .    k11E   v    7;ii:JuJvLvLvJ2: 
2257 jqv   Pqq  1LJur         PP.          7    EX:    q    OqqXP51JYvLvYYS.  
 X2F  kXkXSXk  kJYLU:   O     ,Z    0PXZ   i    ii    q0    i:::,,.jLLvLLuF'  
 ik1k  ;qkPj  .uJvYu:   UN      :   XU2F   :         S5S           iJLLvjUF8   
  :PSq       72uLLLui   uSi    .;   2uY1   r.       72j1           LYYLYJSU88
    XqE2   rP12juJuu1FX55U5FqXXSXkXF1juUkkPSXSPXPXPF1Jju5FkFSFXFSF5uujUu5j28V 
      .uGOZESS5S5SFkkPkPkXkPXqXPXqXXFkSkkPXPXPkqSkSS1521252121U2u2u12Suv7   
*
* KADE - Kick Ass Dynamic Encoder
*
* Copyright (c) 2014
* Jon Wilson    - degenatrons@gmail.com
* Bruno Freitas - bruno@brunofreitas.com
* Kevin Mackett - kevin@sharpfork.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* ADDITIONAL TERMS per GNU GPL Section 7
* No trademark or publicity rights are granted. This license does NOT give you 
* any right, title or interest in the KADE brand. You may not distribute any 
* modification of this program using the KADE name or KADE logo or claim any 
* affiliation or association with KADE or the KADE development team.
*
* Any propagation or conveyance of this program must include this copyright 
* notice and these terms.
*
* You may not misrepresent the origins of this program; modified versions of the 
* program must be marked as such and not identified as the original program.
*/ 

#include "KADEmultiHID.h"
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
 
static uint8_t HIDReportInData[GENERIC_REPORT_SIZE];
static uint8_t HIDReportOutData[GENERIC_REPORT_SIZE];

//Working Variables
uint8_t up, down, left, right;
uint8_t buttons;

int8_t main(void)
{
    SetupHardware();
    sei();	
		  	
	while(1) {		
		//Joystick 1
		//=========================================================================================
		HIDReportOutData[0] = HID_REPORTID_JoystickReport;
		
		//digital direction
		up    = !(PINE&0x01); //D00 - digital up
		down  = !(PINE&0x02); //D01 - digital down
		left  = !(PINC&0x01); //D02 - digital left
		right = !(PINC&0x02); //D03 - digital right			
		
		HIDReportOutData[5] = 0X08;  //NULL		
		if (left)  { HIDReportOutData[5]=0x06; }
		if (right) { HIDReportOutData[5]=0x02; }
		if (up) {
			if (left)		{ HIDReportOutData[5]=0x07; }
			else if (right)	{ HIDReportOutData[5]=0x01; } 
			else			{ HIDReportOutData[5]=0x00; }		
		}
		if (down) {
			if (left)		{ HIDReportOutData[5]=0x05; }
			else if (right)	{ HIDReportOutData[5]=0x03; } 
			else			{ HIDReportOutData[5]=0x04; }
		}		
		
		//buttons
		buttons = 0x00;
		if(!(PINC&0x04)) { buttons=buttons|(1<<0); }	//D04 - button 1
		if(!(PINC&0x08)) { buttons=buttons|(1<<1); }	//D05 - button 2
		if(!(PINC&0x10)) { buttons=buttons|(1<<2); }	//D06 - button 3
		if(!(PINC&0x20)) { buttons=buttons|(1<<3); }	//D07 - button 4
		if(!(PINC&0x40)) { buttons=buttons|(1<<4); }	//D08 - button 5
		if(!(PINC&0x80)) { buttons=buttons|(1<<5); }	//D09 - button 6
		if(!(PINA&0x80)) { buttons=buttons|(1<<6); }	//D10 - button 7
		if(!(PINA&0x20)) { buttons=buttons|(1<<7); }	//D11 - button 8
		HIDReportOutData[6] = buttons;						
		
		//padding
		HIDReportOutData[7] = 0; // ] - unused
		HIDReportOutData[8] = 0; // ]
		
		HID_Task();
		USB_USBTask();
		_delay_ms(2);

		//Joystick 2
		//=========================================================================================
		HIDReportOutData[0] = HID_REPORTID_JoystickReport2;
		
		//digital direction
		up    = !(PINA&0x02); //D13 - digital up
		down  = !(PINA&0x01); //D14 - digital down
		left  = !(PINA&0x04); //D15 - digital left
		right = !(PINA&0x10); //D16 - digital right			
		
		HIDReportOutData[5] = 0X08;  //NULL		
		if (left)  { HIDReportOutData[5]=0x06; }
		if (right) { HIDReportOutData[5]=0x02; }
		if (up) {
			if (left)		{ HIDReportOutData[5]=0x07; }
			else if (right)	{ HIDReportOutData[5]=0x01; } 
			else			{ HIDReportOutData[5]=0x00; }		
		}
		if (down) {
			if (left)		{ HIDReportOutData[5]=0x05; }
			else if (right)	{ HIDReportOutData[5]=0x03; } 
			else			{ HIDReportOutData[5]=0x04; }
		}		
		
		//buttons
		buttons = 0x00;
		if(!(PINA&0x40)) { buttons=buttons|(1<<0); }	//D17 - button 1
		if(!(PINE&0x40)) { buttons=buttons|(1<<1); }	//D18 - button 2
		if(!(PINB&0x01)) { buttons=buttons|(1<<2); }	//D19 - button 3
		if(!(PINB&0x02)) { buttons=buttons|(1<<3); }	//D20 - button 4
		if(!(PINB&0x04)) { buttons=buttons|(1<<4); }	//D21 - button 5
		if(!(PINB&0x08)) { buttons=buttons|(1<<5); }	//D22 - button 6
		if(!(PINB&0x10)) { buttons=buttons|(1<<6); }	//D23 - button 7
		if(!(PINB&0x20)) { buttons=buttons|(1<<7); }	//D24 - button 8
		HIDReportOutData[6] = buttons;						
		
		//padding
		HIDReportOutData[7] = 0; // ] - unused
		HIDReportOutData[8] = 0; // ]
		
		HID_Task();
		USB_USBTask();
		_delay_ms(2);

		//Joystick 3
		//=========================================================================================
		HIDReportOutData[0] = HID_REPORTID_JoystickReport3;
		
		//digital direction
		up    = !(PINB&0x40); //D25 - digital up
		down  = !(PINB&0x80); //D26 - digital down
		left  = !(PINE&0x80); //D27 - digital left
		right = !(PINE&0x08); //D28 - digital right			
		
		HIDReportOutData[5] = 0X08;  //NULL		
		if (left)  { HIDReportOutData[5]=0x06; }
		if (right) { HIDReportOutData[5]=0x02; }
		if (up) {
			if (left)		{ HIDReportOutData[5]=0x07; }
			else if (right)	{ HIDReportOutData[5]=0x01; } 
			else			{ HIDReportOutData[5]=0x00; }		
		}
		if (down) {
			if (left)		{ HIDReportOutData[5]=0x05; }
			else if (right)	{ HIDReportOutData[5]=0x03; } 
			else			{ HIDReportOutData[5]=0x04; }
		}		
		
		//buttons
		buttons = 0x00;
		if(!(PIND&0x01)) { buttons=buttons|(1<<0); }	//D29 - button 1
		if(!(PIND&0x02)) { buttons=buttons|(1<<1); }	//D30 - button 2
		if(!(PIND&0x04)) { buttons=buttons|(1<<2); }	//D31 - button 3
		if(!(PIND&0x08)) { buttons=buttons|(1<<3); }	//D32 - button 4
		if(!(PIND&0x10)) { buttons=buttons|(1<<4); }	//D33 - button 5
		if(!(PIND&0x20)) { buttons=buttons|(1<<5); }	//D34 - button 6
		HIDReportOutData[6] = buttons;						
		
		//padding
		HIDReportOutData[7] = 0; // ] - unused
		HIDReportOutData[8] = 0; // ]
		
		HID_Task();
		USB_USBTask();
		_delay_ms(2);

		//Joystick 4
		//=========================================================================================
		HIDReportOutData[0] = HID_REPORTID_JoystickReport4;
		
		//digital direction
		up    = !(PIND&0x40); //D35 - digital up
		down  = !(PIND&0x80); //D36 - digital down
		left  = !(PINF&0x01); //A00 - digital left
		right = !(PINF&0x02); //A01 - digital right			
		
		HIDReportOutData[5] = 0X08;  //NULL		
		if (left)  { HIDReportOutData[5]=0x06; }
		if (right) { HIDReportOutData[5]=0x02; }
		if (up) {
			if (left)		{ HIDReportOutData[5]=0x07; }
			else if (right)	{ HIDReportOutData[5]=0x01; } 
			else			{ HIDReportOutData[5]=0x00; }		
		}
		if (down) {
			if (left)		{ HIDReportOutData[5]=0x05; }
			else if (right)	{ HIDReportOutData[5]=0x03; } 
			else			{ HIDReportOutData[5]=0x04; }
		}		
		
		//buttons
		buttons = 0x00;
		if(!(PINF&0x04)) { buttons=buttons|(1<<0); }	//A02 - button 1
		if(!(PINF&0x08)) { buttons=buttons|(1<<1); }	//A03 - button 2
		if(!(PINF&0x10)) { buttons=buttons|(1<<2); }	//A04 - button 3
		if(!(PINF&0x20)) { buttons=buttons|(1<<3); }	//A05 - button 4
		if(!(PINF&0x40)) { buttons=buttons|(1<<4); }	//A06 - button 5
		if(!(PINF&0x80)) { buttons=buttons|(1<<5); }	//A07 - button 6
		HIDReportOutData[6] = buttons;						
		
		//padding
		HIDReportOutData[7] = 0; // ] - unused
		HIDReportOutData[8] = 0; // ]
		
		HID_Task();
		USB_USBTask();
		_delay_ms(2);
		
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
    /* Disable watchdog */
    //MCUSR &= ~(1 << WDRF);
    //wdt_disable();
	
	//Switch off JTAG (to free up ports F pins 4,5,6,7)
	MCUCR = (1 << JTD) | (1 << IVCE) | (0 << PUD);
	MCUCR = (1 << JTD) | (0 << IVSEL) | (0 << IVCE) | (0 << PUD); 
	//#define DISABLE_JTAG_APPLICATION

	// Clock @ 16Mhz
	CPU_PRESCALE(0);
	
	//adc_init();
	
	//Initialise AVR Pins
    DDRA=0x00;
    DDRB=0x00;
    DDRC=0x00;
    DDRD=0x00;
    DDRE=0x00;
    DDRF=0x00;
    PORTA=0xFF;
    PORTB=0xFF;
    PORTC=0xFF;
    PORTD=0xFF;
    PORTE=0xFF;
    PORTF=0xFF;

    /* Hardware Initialization */
    USB_Init();
}


void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    ConfigSuccess &= Endpoint_ConfigureEndpoint(GENERIC_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
                                                GENERIC_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(GENERIC_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT,
                                                GENERIC_EPSIZE, ENDPOINT_BANK_SINGLE);
}

void EVENT_USB_Device_ControlRequest(void)
{
    switch (USB_ControlRequest.bRequest)
    {
        case HID_REQ_GetReport:
            if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();
                Endpoint_Write_Control_Stream_LE(&HIDReportOutData, sizeof(HIDReportOutData));
                memset(&HIDReportOutData, 0, GENERIC_REPORT_SIZE + 1);
                Endpoint_ClearOUT();
            }

            break;
        case HID_REQ_SetReport:
            if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
            {
                Endpoint_ClearSETUP();
                Endpoint_Read_Control_Stream_LE(&HIDReportInData, sizeof(HIDReportInData));
                Endpoint_ClearIN();
            }

            break;
    }
}


void HID_Task(void)
{
    if (USB_DeviceState != DEVICE_STATE_Configured)
      return;

    Endpoint_SelectEndpoint(GENERIC_OUT_EPNUM);

    if (Endpoint_IsOUTReceived())
    {
        if (Endpoint_IsReadWriteAllowed())
        {
            Endpoint_Read_Stream_LE(&HIDReportInData, sizeof(HIDReportInData), NULL);
        }
        Endpoint_ClearOUT();
    }

    Endpoint_SelectEndpoint(GENERIC_IN_EPNUM);

    if (Endpoint_IsINReady())
    {
        Endpoint_Write_Stream_LE(&HIDReportOutData, sizeof(HIDReportOutData), NULL);
        memset(&HIDReportOutData, 0, GENERIC_REPORT_SIZE + 1);
        Endpoint_ClearIN();
    }
}