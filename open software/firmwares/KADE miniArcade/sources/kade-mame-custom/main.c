/*
     .k8GOGGNqkSFS5XkqXPSkSkkqXXFS5kSkSS15U22F2515U2uujuu1U1u2U1U2uUuFS.     
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
* Copyright (c) 2013 
* Jon Wilson    - degenatrons@gmail.com
* Bruno Freitas - bootsector@ig.com.br
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

#define F_USB 16000000

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard.h"

//LED flash
#include <avr/wdt.h>
#include <avr/power.h>

//eeprom
#include <avr/eeprom.h>
#define read_eeprom_byte(address) eeprom_read_byte ((const uint8_t*)address)
#define write_eeprom_byte(address,value) eeprom_write_byte ((uint8_t*)address,(uint8_t)value)

uint8_t map[21];
uint8_t key[77];
uint8_t keycount = 0;

//Main Program
int main(void)
{
	// set for 16 MHz clock
	CLKPR = 0x80, CLKPR = 0;

	//Initialise LED timings (added v1.1)
	clock_prescale_set(clock_div_1);

	//Set initial pin states.  These are adjusted based on eeprom settings.
    DDRB=0x00;
    DDRC=0x00;
    DDRD=0x00;
    PORTB=0xFF;
    PORTC=0xFF;
    PORTD=0xFF;

	//pin assignments and button states
	uint8_t	pos=0, cnt=0;
	uint8_t ass[40], state[20];
	
	//handle shift and shift lock
	uint8_t shift=0, shift_last=0, shift_count=0, shift_lock=0;
	
	//extended mode flags - use to detect if key combos are pressed
	uint8_t p1, p2, p3, p4;
	uint8_t ext_inputs, ext_func_block, ext_func;
	
    //Flash LEDs
	#include "..\shared\disco.c"

	//read first 40 eeprom into an array (pins + shifted pins)
	for(cnt=0;cnt<40;cnt++){	
		ass[cnt]=read_eeprom_byte(cnt);
		
		/*//set output pins
		if ((ass[cnt]==28)||(ass[cnt]==29)){
			#include "..\shared\outputs.c"		
		}*/		
	}
	

	// Initialize the USB
	usb_init();

	while(!usb_configured());

	while(1) {
		//read KADE pin states into an array
		#include "..\shared\state.c"		
		
		//set shifted status and detect shift lock (double click)
		#include "..\shared\shift.c"
	
		//loop through pins checking for inputs from those that are assigned a function
		keycount = 0;
		p1=0; p2=0; p3=0; p4=0;
		
		for(cnt=0;cnt<20;cnt++) {
			pos=cnt;					
			if (!(state[cnt])) {
				//there is input on this pin
				if (shift==1){pos=pos+20;}  //+20 if this is shifted input
				
				if (ass[pos]>0) {
					//there is an assignment to a function
					#include "keymaps.c"

					//check for extended mode inputs
					if (ass[pos]==3 ||ass[pos]==4 ){ p1 += 1; }
					if (ass[pos]==5 ||ass[pos]==6 ){ p1 += 3; }
					if (ass[pos]==17||ass[pos]==18){ p2 += 1; }
					if (ass[pos]==19||ass[pos]==20){ p2 += 3; }
					if (ass[pos]==25||ass[pos]==26){ p3 += 1; }
					if (ass[pos]==27||ass[pos]==28){ p3 += 3; }
					if (ass[pos]==43||ass[pos]==44){ p4 += 1; }
					if (ass[pos]==45||ass[pos]==46){ p4 += 3; }
				}				
			}
		}
   
		//Cycle players and process extended maps
		//ext_func_block: sets the start position of the extended functions read from eeprom
		//ext_inputs:     the calculated combo value between 0 and 8.
		//         0:     .
		//         1:     .
		//         2:     left+right
		//         3:     .
		//         4:     .
		//         5:     left+right
		//         6:     up+down
		//         7:     up+down
		//         8:     up+down+left+right
		for(cnt=0;cnt<4;cnt++) {
			if(cnt==0){ext_inputs = p1; ext_func_block = 69;} 
			if(cnt==1){ext_inputs = p2; ext_func_block = 72;} 
			if(cnt==2){ext_inputs = p3; ext_func_block = 75;} 
			if(cnt==3){ext_inputs = p4; ext_func_block = 78;} 
			if (ext_inputs==2||ext_inputs>=5){ 
				//extended combo is detected
				if (ext_inputs==8){ext_func=ext_func_block+2;}                     //(u+d+l+r)
				else if (ext_inputs==2||ext_inputs==5){ext_func=ext_func_block;}   //(u+d)
				else if (ext_inputs==6||ext_inputs==7){ext_func=ext_func_block+1;} //(l+r)
				
				//shifted function are higher in eeprom
				if (shift==1){ext_func=ext_func+12;}
				
				ass[pos] = read_eeprom_byte(ext_func);
				#include "keymaps.c"
			}
		}


   
		while(keycount < sizeof(keyboard_keys)) {
			keyboard_keys[keycount++] = KEY_NONE;
		}

		usb_keyboard_send();
		_delay_ms(2); // Debounce
	}
}
