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
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard.h"

#include <avr/wdt.h>
#include <avr/power.h>

uint8_t keycount = 0;

//Main Program
int main(void)
{
	// set for 16 MHz clock
	CLKPR = 0x80, CLKPR = 0;

	//Switch off the ADC
	//power_adc_disable();

	//Switch off JTAG (to free up ports F pins 4,5,6,7)
    MCUCR = (1 << JTD) | (1 << IVCE) | (0 << PUD);
    MCUCR = (1 << JTD) | (0 << IVSEL) | (0 << IVCE) | (0 << PUD);	

	// Configure all ports as inputs with pullup resistors.
	DDRA = 0x00; DDRB = 0x00; DDRC = 0x00; DDRD = 0x00; DDRE = 0x00; DDRF = 0x00;
	PORTA = 0xFF; PORTB = 0xFF; PORTC = 0xFF; PORTD = 0xFF; PORTE = 0xFF; PORTF = 0xFF;

	// Variables to hold current pin state
	uint8_t a=0x00, b=0x00, c=0x00, d=0x00, e=0x00, f=0x00;

	// Variables to hold previous pin state
	uint8_t pa=0xFF, pb=0xFF, pc=0xFF, pd=0xFF, pe=0xFF, pf=0xFF;

	//Variables to handle shift and shift lock
	uint8_t shift=0, shift_last=0, shift_count=0, shift_lock=0;

	// Initialize the USB
	usb_init();

	while(!usb_configured());
	_delay_ms(500);

	while(1) {
		a = PINA; b = PINB; c = PINC; d = PIND; e = PINE; f = PINF;

		//set shifted status and detect shift lock (double click)
		#include "shift.c"

		if(a != pa || b != pb || c != pc || d != pd || e != pe || f != pf ) {
			keycount = 0;
			
			//note that HWB (e&0x04) is reserved for shift.
			
			//if (shift==0){
			
				//Bottom edge
				if(!(e & 0x01)) { keyboard_keys[keycount++] = KEY_UP; }			//D00 - P1 UP
				if(!(e & 0x02)) { keyboard_keys[keycount++] = KEY_DOWN; }			//D01 - P1 DOWN
				if(!(c & 0x01)) { keyboard_keys[keycount++] = KEY_LEFT; }			//D02 - P1 LEFT
				if(!(c & 0x02)) { keyboard_keys[keycount++] = KEY_RIGHT; }		//D03 - P1 RIGHT
				if(!(c & 0x04)) { keyboard_keys[keycount++] = KEY_LEFT_CTRL; }	//D04 - P1 BUTTON 1
				if(!(c & 0x08)) { keyboard_keys[keycount++] = KEY_LEFT_ALT; }		//D05 - P1 BUTTON 2
				if(!(c & 0x10)) { keyboard_keys[keycount++] = KEY_SPACE; }		//D06 - P1 BUTTON 3
				if(!(c & 0x20)) { keyboard_keys[keycount++] = KEY_LEFT_SHIFT; }	//D07 - P1 BUTTON 4
				if(!(c & 0x40)) { keyboard_keys[keycount++] = KEY_Z; } 			//D08 - P1 BUTTON 5
				if(!(c & 0x80)) { keyboard_keys[keycount++] = KEY_X; }			//D09 - P1 BUTTON 6
				//Note: Port A sequence is rearranged on PCB
				if(!(a & 0x80)) { keyboard_keys[keycount++] = KEY_Y; }			//D10 - P4 UP
				if(!(a & 0x20)) { keyboard_keys[keycount++] = KEY_N; }			//D11 - P4 DOWN
				if(!(a & 0x08)) { keyboard_keys[keycount++] = KEY_V; }			//D12 - P4 LEFT
				if(!(a & 0x02)) { keyboard_keys[keycount++] = KEY_U; }			//D13 - P4 RIGHT
				if(!(a & 0x01)) { keyboard_keys[keycount++] = KEYPAD_0; }			//D14 - P4 BUTTON 1
				if(!(a & 0x04)) { keyboard_keys[keycount++] = KEYPAD_MINUS; }		//D15 - P4 BUTTON 2
				if(!(a & 0x10)) { keyboard_keys[keycount++] = KEYPAD_ENTER; }		//D16 - P4 BUTTON 3
				if(!(a & 0x40)) { keyboard_keys[keycount++] = KEYPAD_PLUS; }		//D17 - P4 BUTTON 4
				if(!(e & 0x40)) { keyboard_keys[keycount++] = KEY_ESC; }			//D18 - EXIT/ESCAPE
 	
				//top edge
				if(!(b & 0x01)) { keyboard_keys[keycount++] = KEY_R; }			//D19 - P2 UP
				if(!(b & 0x02)) { keyboard_keys[keycount++] = KEY_F; }			//D20 - P2 DOWN
				if(!(b & 0x04)) { keyboard_keys[keycount++] = KEY_D; }			//D21 - P2 LEFT
				if(!(b & 0x08)) { keyboard_keys[keycount++] = KEY_G; }			//D22 - P2 RIGHT
				if(!(b & 0x10)) { keyboard_keys[keycount++] = KEY_A; }			//D23 - P2 BUTTON 1
				if(!(b & 0x20)) { keyboard_keys[keycount++] = KEY_S; }			//D24 - P2 BUTTON 2
				if(!(b & 0x40)) { keyboard_keys[keycount++] = KEY_Q; }			//D25 - P2 BUTTON 3
				if(!(b & 0x80)) { keyboard_keys[keycount++] = KEY_W; }			//D26 - P2 BUTTON 4
				if(!(e & 0x80)) { keyboard_keys[keycount++] = KEY_I; }			//D27 - P2 BUTTON 5
				if(!(e & 0x08)) { keyboard_keys[keycount++] = KEY_K; }			//D28 - P2 BUTTON 6
				if(!(d & 0x01)) { keyboard_keys[keycount++] = KEY_PAGE_UP; }		//D29 - P3 UP		-- ADJUSTED FROM DEFAULT TO PREVENT CONFLICT
				if(!(d & 0x02)) { keyboard_keys[keycount++] = KEY_PAGE_DOWN; }	//D30 - P3 DOWN		-- ADJUSTED FROM DEFAULT TO PREVENT CONFLICT
				if(!(d & 0x04)) { keyboard_keys[keycount++] = KEY_HOME; }			//D31 - P3 LEFT		-- ADJUSTED FROM DEFAULT TO PREVENT CONFLICT
				if(!(d & 0x08)) { keyboard_keys[keycount++] = KEY_END; }			//D32 - P3 RIGHT    -- ADJUSTED FROM DEFAULT TO PREVENT CONFLICT
				if(!(d & 0x10)) { keyboard_keys[keycount++] = KEY_RIGHT_CTRL; }	//D33 - P3 BUTTON 1
				if(!(d & 0x20)) { keyboard_keys[keycount++] = KEY_RIGHT_SHIFT; }	//D34 - P3 BUTTON 2
				if(!(d & 0x40)) { keyboard_keys[keycount++] = KEY_ENTER; }		//D35 - P3 BUTTON 3
				if(!(d & 0x80)) { keyboard_keys[keycount++] = KEY_BACKSLASH; }	//D36 - P3 BUTTON 4
				
				//Right Edge 
				if(!(f & 0x01)) { keyboard_keys[keycount++] = KEY_1; }			//A00 - P1 START
				if(!(f & 0x02)) { keyboard_keys[keycount++] = KEY_2; }			//A01 - P2 START
				if(!(f & 0x04)) { keyboard_keys[keycount++] = KEY_3; }			//A02 - P3 START
				if(!(f & 0x08)) { keyboard_keys[keycount++] = KEY_4; }			//A03 - P4 START
				if(!(f & 0x10)) { keyboard_keys[keycount++] = KEY_5; }			//A04 - P1 COIN
				if(!(f & 0x20)) { keyboard_keys[keycount++] = KEY_6; }			//A05 - P2 COIN
				if(!(f & 0x40)) { keyboard_keys[keycount++] = KEY_7; }			//A06 - P3 COIN
				if(!(f & 0x80)) { keyboard_keys[keycount++] = KEY_8; }			//A07 - P4 COIN
								
				
				//Crystal pins - after 32mhz crystal removed
				//if(!(e & 0x10)) { keyboard_keys[keycount++] = KEY_F9; }
				//if(!(e & 0x20)) { keyboard_keys[keycount++] = KEY_F10; }
			
			//}

			
				  			  
			while(keycount < sizeof(keyboard_keys)) {
				keyboard_keys[keycount++] = KEY_NONE;
			}

			usb_keyboard_send();

			pa = a; pb = b; pc = c; pd = d; pe = e; pf = f;
		  
		}
		_delay_ms(5); // Debounce
	}
}
