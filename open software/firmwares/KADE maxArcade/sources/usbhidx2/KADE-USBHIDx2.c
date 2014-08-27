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
 
// initialize adc
void adc_init()
{
    // AVCC/AREF - maybe need 5V reference voltage connected to AREF otherwise may get noise.
    ADMUX = (1<<REFS0)|(0<<REFS1);
 
    // ADC Enable and prescaler 128
	// 3 least significant bits set the resolution
	// most significant bit is for enable ADC
    
	//ADC prescaler bit reference:
	// 0 0 1 = 2
	// 0 1 0 = 4
	// 0 1 1 = 8
	// 1 0 0 = 16
	// 1 0 1 = 32
	// 1 1 0 = 64
	// 1 1 1 = 128

	//prescaler
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);
}

// read adc value
uint16_t adc_read(uint8_t ch)
{
    // select the corresponding channel 0~7
    // ANDing with '7' will always keep the value of 'ch' between 0 and 7
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing
 
    // start single conversion
    // write '1' to ADSC
    ADCSRA |= (1<<ADSC);
 
    // wait for conversion to complete
    // ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1<<ADSC));
 
    return (ADC);
}

static uint8_t HIDReportInData[GENERIC_REPORT_SIZE];
static uint8_t HIDReportOutData[GENERIC_REPORT_SIZE];

//Working Variables
uint16_t adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7;
uint8_t up, down, left, right;
uint8_t buttons;

int8_t main(void)
{
    SetupHardware();
    sei();	
		
	while(1) {
		//Analog
		//-------------------------------------------------------------
		//Set X/Y axis values
		adc0 = adc_read(0);
		adc1 = adc_read(1);
		adc2 = adc_read(2);
		adc3 = adc_read(3);
		adc4 = adc_read(4);
		adc5 = adc_read(5);
		adc6 = adc_read(6);
		adc7 = adc_read(7);
		
		//Joystick 1
		//=========================================================================================
		HIDReportOutData[0] = HID_REPORTID_JoystickReport;
		
		//hat switch		
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
		
		buttons = 0x00;
		if(!(PINA&0x08)) { buttons=buttons|(1<<0); }	//D12 - button 9
		if(!(PINA&0x02)) { buttons=buttons|(1<<1); }	//D13 - button 10
		if(!(PINA&0x01)) { buttons=buttons|(1<<2); }	//D14 - button 11
		if(!(PINA&0x04)) { buttons=buttons|(1<<3); }	//D15 - button 12
		if(!(PINA&0x10)) { buttons=buttons|(1<<4); }	//D16 - button 13
		if(!(PINA&0x40)) { buttons=buttons|(1<<5); }	//D17 - button 14
		if(!(PINE&0x40)) { buttons=buttons|(1<<6); }	//D18 - button 15
		HIDReportOutData[7] = buttons;
						
		//stick 1
		HIDReportOutData[1] = (adc0 / 4) - 128; // x axis
		HIDReportOutData[2] = (adc1 / 4) - 128; // y axis
		
		//stick 2
		HIDReportOutData[3] = (adc2 / 4) - 128; // x axis
		HIDReportOutData[4] = (adc3 / 4) - 128; // y axis
		
		//padding
		HIDReportOutData[8] = 0; // ] - unused
		HIDReportOutData[9] = 0; // ]
		
		HID_Task();
		USB_USBTask();
		_delay_ms(2);
		
		//Joystick 2
		//=========================================================================================
		HIDReportOutData[0] = HID_REPORTID_JoystickReport2;
			
		//hat switch		
		//digital direction
		up    = !(PINB&0x01); //D19 - digital up
		down  = !(PINB&0x02); //D20 - digital down
		left  = !(PINB&0x04); //D21 - digital left
		right = !(PINB&0x08); //D22 - digital right			
		
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
		if(!(PINB&0x10)) { buttons=buttons|(1<<0); }	//D23 - button 1
		if(!(PINB&0x20)) { buttons=buttons|(1<<1); }	//D24 - button 2
		if(!(PINB&0x40)) { buttons=buttons|(1<<2); }	//D25 - button 3
		if(!(PINB&0x80)) { buttons=buttons|(1<<3); }	//D26 - button 4
		if(!(PINE&0x80)) { buttons=buttons|(1<<4); }	//D27 - button 5
		if(!(PINE&0x08)) { buttons=buttons|(1<<5); }	//D28 - button 6
		if(!(PIND&0x01)) { buttons=buttons|(1<<6); }	//D29 - button 7
		if(!(PIND&0x02)) { buttons=buttons|(1<<7); }	//D30 - button 8
		HIDReportOutData[6] = buttons;

		buttons = 0x00;
		if(!(PIND&0x04)) { buttons=buttons|(1<<0); }	//D31 - button 9
		if(!(PIND&0x08)) { buttons=buttons|(1<<1); }	//D32 - button 10
		if(!(PIND&0x10)) { buttons=buttons|(1<<2); }	//D33 - button 11
		if(!(PIND&0x20)) { buttons=buttons|(1<<3); }	//D34 - button 12
		if(!(PIND&0x40)) { buttons=buttons|(1<<4); }	//D35 - button 13
		if(!(PIND&0x80)) { buttons=buttons|(1<<5); }	//D36 - button 14
		HIDReportOutData[7] = buttons;
	
		//stick 1
		HIDReportOutData[1] = (adc4 / 4) - 128; // x axis
		HIDReportOutData[2] = (adc5 / 4) - 128; // y axis
		
		//stick 2
		HIDReportOutData[3] = (adc6 / 4) - 128; // x axis
		HIDReportOutData[4] = (adc7 / 4) - 128; // y axis
		
		//padding
		HIDReportOutData[8] = 0; // ] - unused
		HIDReportOutData[9] = 0; // ]
		
		HID_Task();
		USB_USBTask();
		_delay_ms(2);
		
/*		//Can include keyboard and/or mouse input
		//Keyboard
		//=========================================================================================
		HIDReportOutData[0]  = HID_REPORTID_KeyboardReport;
		HIDReportOutData[1]  = 0; // modifiers
		HIDReportOutData[2]  = 0; // RESERVED
		
		//15 simultaneous key presses:
		//refer to scancodes.txt file
		HIDReportOutData[3]  = 0; 
		HIDReportOutData[4]  = 0;
		HIDReportOutData[5]  = 0;
		HIDReportOutData[6]  = 0;
		HIDReportOutData[7]  = 0;
		HIDReportOutData[8]  = 0;	
		HIDReportOutData[9]  = 0;
		HIDReportOutData[10] = 0;
		HIDReportOutData[11] = 0;
		HIDReportOutData[12] = 0;
		HIDReportOutData[13] = 0;
		HIDReportOutData[14] = 0;
		HIDReportOutData[15] = 0;
		HIDReportOutData[16] = 0;
		HIDReportOutData[17] = 0;
		
		if (!(PIND&0x80)) { HIDReportOutData[3]  = HID_KEYBOARD_SC_1_AND_EXCLAMATION; } 
		if (!(PIND&0x40)) { HIDReportOutData[4]  = HID_KEYBOARD_SC_2_AND_AT; }
		if (!(PIND&0x20)) { HIDReportOutData[5]  = HID_KEYBOARD_SC_A; }
		if (!(PIND&0x10)) { HIDReportOutData[6]  = HID_KEYBOARD_SC_S; }
		if (!(PIND&0x08)) { HIDReportOutData[7]  = HID_KEYBOARD_SC_Z; }
		if (!(PIND&0x04)) { HIDReportOutData[8]  = HID_KEYBOARD_SC_X; }
		if (!(PIND&0x02)) { HIDReportOutData[9]  = HID_KEYBOARD_SC_K; }
		if (!(PIND&0x01)) { HIDReportOutData[10] = HID_KEYBOARD_SC_L; }
		
		if (!(PINB&0x08)) { HIDReportOutData[11]  = HID_KEYBOARD_SC_UP_ARROW; }
		if (!(PINB&0x04)) { HIDReportOutData[12]  = HID_KEYBOARD_SC_DOWN_ARROW; }
		if (!(PINB&0x02)) { HIDReportOutData[13]  = HID_KEYBOARD_SC_LEFT_ARROW; }
		if (!(PINB&0x01)) { HIDReportOutData[14] = HID_KEYBOARD_SC_RIGHT_ARROW; }
	
		HID_Task();
		USB_USBTask();		
*/				
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
    /* Disable watchdog */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();
	
	//Switch off JTAG (to free up ports F pins 4,5,6,7)
	MCUCR = (1 << JTD) | (1 << IVCE) | (0 << PUD);
	MCUCR = (1 << JTD) | (0 << IVSEL) | (0 << IVCE) | (0 << PUD); 
	//#define DISABLE_JTAG_APPLICATION

	// Clock @ 16Mhz
	CPU_PRESCALE(0);
	
	adc_init();
	
	//Initialise AVR Pins
    DDRA=0x00;
    DDRB=0x00;
    DDRC=0x00;
    DDRD=0x00;
    DDRE=0x00;
    PORTA=0xFF;
    PORTB=0xFF;
    PORTC=0xFF;
    PORTD=0xFF;
    PORTE=0xFF;

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