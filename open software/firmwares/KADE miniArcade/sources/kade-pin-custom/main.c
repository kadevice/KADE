/* 
 * KADE - Kick Ass Device Encoder
 * Copyright (c) 2012 Jon Wilson    - degenatrons@gmail.com
 *                    Bruno Freitas - bruno@brunofreitas.com
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
------------------------------------------------------------------------------
 * Designed for the Minimus AVR Development Board http://minimususb.com
 * Compatible with all USB keyboard input systems (Windows, Linux, Mac)
 *
 * All modern operating systems support USB keyboards. 
 * No special drivers need to be loaded.
 * Full keyboard emulation. No ghosting and no blocking.
 *
 * This code also supports the keyboard "boot protocol" for compatability with 
 * the BIOS before an operating system has loaded. 
------------------------------------------------------------------------------
 * HWB button (and pin) used to toggle the keymapping mapping modes.
 * Active mapping is stored in EEPROM and is remembered when powered off.
------------------------------------------------------------------------------
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
uint8_t key[61];
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
	
    //Flash LEDs
	#include "../shared/disco.c"

	//read first 40 eeprom into an array (pins + shifted pins)
	for(cnt=0;cnt<40;cnt++){	
		ass[cnt]=read_eeprom_byte(cnt);
		
		/*//set output pins
		if ((ass[cnt]==28)||(ass[cnt]==29)){
			#include "../shared/outputs.c"		
		}*/		
	}

	// Initialize the USB
	usb_init();

	while(!usb_configured());

	while(1) {
	
		
		//read KADE pin states into an array
		#include "../shared/state.c"		
		
		//set shifted status and detect shift lock (double click)
		#include "../shared/shift.c"	
	
	
		//loop through pins checking for inputs from those that are assigned a function
		keycount = 0;
		for(cnt=0;cnt<20;cnt++) {
			pos=cnt;					
			if (!(state[cnt])) {
				//there is input on this pin
				if (shift==1){pos=pos+20;}  //+20 if this is shifted input
				
				if (ass[pos]>0) {
					//there is an assignment to a function
					#include "keymaps.c"					
				}
			}
		  
		}
   
		while(keycount < sizeof(keyboard_keys)) {
			keyboard_keys[keycount++] = KEY_NONE;
			//keyboard_modifier_keys = KEY_NONE;
		}

		usb_keyboard_send();

		_delay_ms(10); // Debounce
	}
}
