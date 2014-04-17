/* 
 * KADE - Kick Ass Device Encoder
 * Copyright (c) 2012 Jon Wilson    - degenatrons@gmail.com
 *                    Bruno Freitas - bootsector@ig.com.br
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
#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard.h"

//LED flash
#include <avr/wdt.h>
#include <avr/power.h>
#define LED_A 6  //red  - unused
#define LED_B 5  //blue - mode change

//eeprom
#define read_eeprom_byte(address) eeprom_read_byte ((const uint8_t*)address)
#define write_eeprom_byte(address,value) eeprom_write_byte ((uint8_t*)address,(uint8_t)value)

uint8_t	ee_byte;
uint8_t map[21];
uint8_t flashes = 1;
uint8_t keycount = 0;
uint8_t modecount = 0;  //HWB to toggle active mode

#include "mappings.c"
#include "routines.c"

//Main Program
int main(void)
{
	uint8_t b_prev=0xFF, c_prev=0xFF, d_prev=0xFF;

	// set for 16 MHz clock
	CLKPR = 0x80, CLKPR = 0;

	// Configure all ports as inputs with pullup resistors.
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x60; // D5,D6 - OUTPUT (LED)
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;

	//Initialise LED timings (added v1.1)
	clock_prescale_set(clock_div_1);
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	//Read eeprom to get active group and mode
	ee_byte=read_eeprom_byte(1);
	set_active_mode();

	// Initialize the USB
	usb_init();

    //flash them leds
	#include "../shared/disco.c"

	while(!usb_configured());

//	// Wait for host to load drivers
//	_delay_ms(500);

	while(1) {
		uint8_t b = PINB;
		uint8_t c = PINC;
		uint8_t d = PIND;

		if(b != b_prev || c != c_prev || d != d_prev ) {
		  keycount = 0;
		  modecount = 0;  //HWB to toggle active mode

		  if(!(c & 0x10)) { keyboard_keys[keycount++] = map[19]; } //PIN B10
		  if(!(c & 0x20)) { keyboard_keys[keycount++] = map[18]; } //PIN B9
		  if(!(c & 0x40)) { keyboard_keys[keycount++] = map[17]; } //PIN B8
		  if(!(c & 0x80)) { keyboard_keys[keycount++] = map[16]; } //PIN B7
		  if(!(b & 0x80)) { keyboard_keys[keycount++] = map[15]; } //PIN B6
		  if(!(b & 0x40)) { keyboard_keys[keycount++] = map[14]; } //PIN B5
		  if(!(b & 0x20)) { keyboard_keys[keycount++] = map[13]; } //PIN B4
		  if(!(b & 0x10)) { keyboard_keys[keycount++] = map[12]; } //PIN B3
		  if(!(b & 0x08)) { keyboard_keys[keycount++] = map[11]; } //PIN B2
		  if(!(b & 0x04)) { keyboard_keys[keycount++] = map[10]; } //PIN B1
		  if(!(b & 0x02)) { keyboard_keys[keycount++] = map[9]; }  //PIN A10
		  if(!(b & 0x01)) { keyboard_keys[keycount++] = map[8]; }  //PIN A9
		  if(!(d & 0x40)) { keyboard_keys[keycount++] = map[7]; }  //PIN A8
		  if(!(d & 0x20)) { keyboard_keys[keycount++] = map[6]; }  //PIN A7
		  if(!(d & 0x10)) { keyboard_keys[keycount++] = map[5]; }  //PIN A6
		  if(!(d & 0x08)) { keyboard_keys[keycount++] = map[4]; }  //PIN A5
		  if(!(d & 0x04)) { keyboard_keys[keycount++] = map[3]; }  //PIN A4
		  if(!(d & 0x02)) { keyboard_keys[keycount++] = map[2]; }  //PIN A3
		  if(!(d & 0x01)) { keyboard_keys[keycount++] = map[1]; }  //PIN A2
		  if(!(c & 0x04)) { keyboard_keys[keycount++] = map[0]; }  //PIN A1
		  
		  if(!(d & 0x80)) {                                         //HWB PIN 
			  modecount++;
		  }                        			  
			  
		  while(keycount < sizeof(keyboard_keys)) {
			keyboard_keys[keycount++] = KEY_NONE;
		  }

		  usb_keyboard_send();

		  b_prev = b;
		  c_prev = c;
		  d_prev = d;
		  
		  if (modecount>0){
			switch_mode();
		  }	  

		}
		_delay_ms(2); // Debounce
	}
}
