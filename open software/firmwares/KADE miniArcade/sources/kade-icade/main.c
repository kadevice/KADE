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

//LED flash
#include <avr/wdt.h>
#include <avr/power.h>
#define LED_A 6  //red  - unused
#define LED_B 5  //blue - mode change

uint8_t map[41];
uint8_t keycount = 0;

//Main Program
int main(void)
{
    #include "mappings.c"
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

		keycount = 0;

		//down
		if((!(c & 0x40))&&((c_prev & 0x40))) { keyboard_keys[keycount++] = map[17]; } //PIN B8
		if((!(c & 0x80))&&((c_prev & 0x80))) { keyboard_keys[keycount++] = map[16]; } //PIN B7
		if((!(b & 0x80))&&((b_prev & 0x80))) { keyboard_keys[keycount++] = map[15]; } //PIN B6
		if((!(b & 0x40))&&((b_prev & 0x40))) { keyboard_keys[keycount++] = map[14]; } //PIN B5
		if((!(b & 0x20))&&((b_prev & 0x20))) { keyboard_keys[keycount++] = map[13]; } //PIN B4
		if((!(b & 0x10))&&((b_prev & 0x10))) { keyboard_keys[keycount++] = map[12]; } //PIN B3
		if((!(b & 0x08))&&((b_prev & 0x08))) { keyboard_keys[keycount++] = map[11]; } //PIN B2
		if((!(b & 0x04))&&((b_prev & 0x04))) { keyboard_keys[keycount++] = map[10]; } //PIN B1
		if((!(d & 0x04))&&((d_prev & 0x04))) { keyboard_keys[keycount++] = map[3]; }  //PIN A4
		if((!(d & 0x02))&&((d_prev & 0x02))) { keyboard_keys[keycount++] = map[2]; }  //PIN A3
		if((!(d & 0x01))&&((d_prev & 0x01))) { keyboard_keys[keycount++] = map[1]; }  //PIN A2
		if((!(c & 0x04))&&((c_prev & 0x04))) { keyboard_keys[keycount++] = map[0]; }  //PIN A1

		//up
		if(((c & 0x40))&&(!(c_prev & 0x40))) { keyboard_keys[keycount++] = map[37]; } //PIN B8
		if(((c & 0x80))&&(!(c_prev & 0x80))) { keyboard_keys[keycount++] = map[36]; } //PIN B7
		if(((b & 0x80))&&(!(b_prev & 0x80))) { keyboard_keys[keycount++] = map[35]; } //PIN B6
		if(((b & 0x40))&&(!(b_prev & 0x40))) { keyboard_keys[keycount++] = map[34]; } //PIN B5
		if(((b & 0x20))&&(!(b_prev & 0x20))) { keyboard_keys[keycount++] = map[33]; } //PIN B4
		if(((b & 0x10))&&(!(b_prev & 0x10))) { keyboard_keys[keycount++] = map[32]; } //PIN B3
		if(((b & 0x08))&&(!(b_prev & 0x08))) { keyboard_keys[keycount++] = map[31]; } //PIN B2
		if(((b & 0x04))&&(!(b_prev & 0x04))) { keyboard_keys[keycount++] = map[30]; } //PIN B1
		if(((d & 0x04))&&(!(d_prev & 0x04))) { keyboard_keys[keycount++] = map[23]; }  //PIN A4
		if(((d & 0x02))&&(!(d_prev & 0x02))) { keyboard_keys[keycount++] = map[22]; }  //PIN A3
		if(((d & 0x01))&&(!(d_prev & 0x01))) { keyboard_keys[keycount++] = map[21]; }  //PIN A2
		if(((c & 0x04))&&(!(c_prev & 0x04))) { keyboard_keys[keycount++] = map[20]; }  //PIN A1
  			  
		while(keycount < sizeof(keyboard_keys)) {
			keyboard_keys[keycount++] = KEY_NONE;
		}

		usb_keyboard_send();


		b_prev = b;
		c_prev = c;
		d_prev = d;
		  
		_delay_ms(10); // Debounce
	}
}
