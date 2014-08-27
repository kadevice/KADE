/* 
 * KADE - Kick Ass Dynamic Encoder
 * Copyright (c) 2012 Bruno Freitas - bruno@brunofreitas.com
 *                    Jon Wilson    - degenatrons@gmail.com
 *                    Kevin Mackett - kevin@sharpfork.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

#include "USBVirtuaStick.h"
#include "../shared/jump.c"

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
#define bit_set(p,m) ((p) |= (m)) 
#define bit_clear(p,m) ((p) &= ~(m)) 
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m)) 

//eeprom
#include <avr/eeprom.h>
#define read_eeprom_byte(address) eeprom_read_byte ((const uint8_t*)address)
#define write_eeprom_byte(address,value) eeprom_write_byte ((uint8_t*)address,(uint8_t)value)

int main(void) {
	// Set clock @ 16Mhz
	CPU_PRESCALE(0);		

	//Set initial pin states.  These are adjusted based on eeprom settings.
    DDRB=0x00;
    DDRC=0x00;
    DDRD=0x00;
    PORTB=0xFF;
    PORTC=0xFF;
    PORTD=0xFF;
	
	//dpad and pad restrictions
	uint8_t	u=0, d=0, l=0, r=0, pu=0, pd=0, pl=0, pr=0;
	
	//pin assignments and button states
	uint8_t	pos=0, cnt=0;
	uint8_t ass[40], state[20];
	
	//handle shift and shift lock
	uint8_t shift=0, shift_last=0, shift_count=0, shift_lock=0;
	
	//handle settings
	uint8_t invert, restrict4;
	uint8_t setting_delay;
	uint8_t autofire, auto_toggle=1;
	uint8_t active=0, delay_power=0;
	
    //Flash LEDs
	#include "../shared/disco.c"

	//read first 40 eeprom into an array (pins + shifted pins)
	for(cnt=0;cnt<40;cnt++){	
		ass[cnt]=read_eeprom_byte(cnt);
		
		//set output pins
		if ((ass[cnt]==28)||(ass[cnt]==29)){
			#include "../shared/outputs.c"		
		}
		if (ass[cnt]==29){delay_power=1;}
		
	}
	//Read other settings (40+ in Eeprom) 
	setting_delay=read_eeprom_byte(41);

	//wait for specified delay time (allow 2 secs for led flash)
	if ((delay_power==1)&&(setting_delay>0)){
		for(cnt=0;cnt<=setting_delay-3;cnt++){
			_delay_ms(1000);
		}
		active=1;
		for(cnt=0;cnt<40;cnt++){	
			if (ass[cnt]==29){
				#include "../shared/showleds.c"
			}
		}
	}

	// Init USB pad emulation
	vs_init(true);

	// Pins polling and gamepad status updates
	for (;;) {
		vs_reset_watchdog();
		
		//read KADE pin states into an array
		#include "../shared/state.c"		
		
		//set shifted status and detect shift lock (double click)
		#include "../shared/shift.c"		

		//set default button states
		//reset direction to centre
		gamepad_state.direction=8;
		gamepad_state.l_y_axis=0x80;
		gamepad_state.l_x_axis=0x80;

		gamepad_state.square_btn=0x00;
		gamepad_state.cross_btn=0x00;
		gamepad_state.circle_btn=0x00;
		gamepad_state.triangle_btn=0x00;
		gamepad_state.l1_btn=0x00;
		gamepad_state.r1_btn=0x00;					
		gamepad_state.l2_btn=0x00;
		gamepad_state.r2_btn=0x00;
		gamepad_state.l3_btn=0x00;
		gamepad_state.r3_btn=0x00;
		gamepad_state.select_btn=0x00;
		gamepad_state.start_btn=0x00;
		gamepad_state.ps_btn=0x00;
		invert=0;
		restrict4=0;
		autofire=0;		
		
		//pre-loop to deal with any switches/toggles		
		pu=u; pd=d; pl=l; pr=r;
		u=0; d=0; l=0; r=0;
		for(cnt=0;cnt<20;cnt++) {
			if (!(state[cnt])) {
				//there is input on this pin, also account for shifted input
				pos = cnt;
				if (shift==1){pos=pos+20;}
				
				if ((ass[cnt]==23)||(ass[pos]==23)){invert=1;}     //invert Y axis
				if ((ass[cnt]==22)||(ass[pos]==22)){restrict4=1;}  //restrict dPad 4-way
				if ((ass[pos]>=24)&&(ass[pos]<=27)){autofire=1;}   //autofire mode
				if ((ass[pos]>=30)&&(ass[pos]<=38)){autofire=1;}   //extra autofire mode
				if (ass[pos]==1){u=1;}
				if (ass[pos]==2){d=1;}				
				if (ass[pos]==3){l=1;}
				if (ass[pos]==4){r=1;}
			}
			
			//Show the shift status LED(s) and power up externals with delay
			if (ass[cnt]==28){
				active = shift;
				#include "../shared/showleds.c"								
			}
		}			

		//invert Y axis on DPAD (if we want to do this)
		//if (invert==1){
		//	if (u==1){d=1; u=0;} 
		//	else if (d==1){d=0; u=1;}
		//}

		//autofire toggle
		if(autofire==1){
			auto_toggle = auto_toggle * -1;
		}

		//Handle dpad and restricted movement
		if(restrict4==1){
			if (u==1){gamepad_state.direction=0;}
			if (d==1){gamepad_state.direction=4;}
			if (l==1){gamepad_state.direction=6;}
			if (r==1){gamepad_state.direction=2;}
		} else {				
			//left and right directions
			if (l==1){gamepad_state.direction=6;}  //Left
			if (r==1){gamepad_state.direction=2;}	//Right						
			
			//up, down and diagonal directions
			if (u==1){								//Up
				if (l==1){							//left
					gamepad_state.direction=7;		//up-left
				}
				else if (r==1){    					//right
					gamepad_state.direction=1;		//up-right
				} else {
					gamepad_state.direction=0;		//up
				}		
			}
			if (d==1){								//down
				if (l==1){							//left
					gamepad_state.direction=5;		//down-left
				}
				else if (r==1){   	 				//right
					gamepad_state.direction=3;		//down-right
				} else {
					gamepad_state.direction=4;		//down
				}
			}		
		}

		//loop through pins checking for inputs from those that are assigned a function
		for(cnt=0;cnt<20;cnt++) {
			pos=cnt;					
			if (!(state[cnt])) {
				//there is input on this pin
				if (shift==1){pos=pos+20;}  //+20 if this is shifted input
				
				if (ass[pos]>0) {
					//there is an assignment to a function

					//A, B, X, Y
					if (ass[pos]==5){gamepad_state.square_btn=0xFF;}
					if (ass[pos]==6){gamepad_state.cross_btn=0xFF;}
					if (ass[pos]==7){gamepad_state.circle_btn=0xFF;}
					if (ass[pos]==8){gamepad_state.triangle_btn=0xFF;}
					
					//Autofire
					if (autofire==1){
						if(auto_toggle==1){
							if (ass[pos]==24){gamepad_state.square_btn=0xFF;}
							if (ass[pos]==25){gamepad_state.cross_btn=0xFF;}
							if (ass[pos]==26){gamepad_state.circle_btn=0xFF;}
							if (ass[pos]==27){gamepad_state.triangle_btn=0xFF;}
						}
						_delay_ms(15);
					}
					
					//PS3 Triggers
					if (ass[pos]==9){gamepad_state.l1_btn=0xFF;}   		    //L1
					if (ass[pos]==10){gamepad_state.r1_btn=0xFF;}  		    //R1					
					if (ass[pos]==11){gamepad_state.l2_btn=0xFF;}  		    //L2
					if (ass[pos]==12){gamepad_state.r2_btn=0xFF;}   			//R2
					if (ass[pos]==15){gamepad_state.l3_btn=0xFF;}  		    //L3
					if (ass[pos]==16){gamepad_state.r3_btn=0xFF;}				//R3
					
					//PS3 Special
					if (ass[pos]==13){gamepad_state.select_btn=0xFF;}			//L3
					if (ass[pos]==14){gamepad_state.start_btn=0xFF;}			//R3
					if (ass[pos]==17){gamepad_state.ps_btn=0xFF;}				//PS Button
					
					//Analog Stick
					if (ass[pos]==18+invert){gamepad_state.l_y_axis = 0x00;} 	//Analog Up
					if (ass[pos]==19-invert){gamepad_state.l_y_axis = 0xff;} 	//Analog Down
					if (ass[pos]==20){gamepad_state.l_x_axis = 0x00;} 			//Analog Left
					if (ass[pos]==21){gamepad_state.l_x_axis = 0xff;} 			//Analog Right
					
					//Enter programming mode
					if (ass[pos]==39){Jump_To_Bootloader();}					//Program mode					
										
				}
			}
		}

		_delay_ms(10);  //debounce
		vs_send_pad_state();
		
	}
}
