/* 
 * PS3
 * KADE - Kick Ass Dynamic Encoder
 * Copyright (c) 2012 Bruno Freitas - bootsector@ig.com.br
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
 
  
   Mappings
   --------

   A1  up        (+shift for analog)
   A2  down      (+shift for analog)
   A3  left      (+shift for analog)
   A4  right     (+shift for analog)
   A5  square    (and button 1)
   A6  cross     (and button 2)
   A7  *shift status LED
   A8  *connectivity status LED
   A9  circle    (and button 3)
   A10 triangle  (and button 4)
   B1  L1        (and button 5)
   B2  R1        (and button 6)
   B3  L2        (and button 7)
   B4  R2        (and button 8)
   B5  Select    (and button 9)
   B6  Start     (and button 10)
   B7  L3        (and button 11)
   B8  R3        (and button 12)
   B9  PS Button (and button 13)
   B10 (unused)
   HWB shift (double click for shift lock)
*/

#include "USBVirtuaStick.h"

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
#define bit_set(p,m) ((p) |= (m)) 
#define bit_clear(p,m) ((p) &= ~(m)) 
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m)) 

void ledOn(void) {
	PORTD |= (1<<6);
}

void ledOff(void) {
	PORTD &= ~(1<<6);
}

int main(void) {

	// Set Teensy clock @ 16Mhz
	CPU_PRESCALE(0);
	
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0x60; // D5,D6 - OUTPUT (LED)
    PORTB = 0xFF;
    PORTC = 0xFF;
    PORTD = 0x9F; // D5,D6 - LOW (LED)
	bit_set(PORTD,0x20);	

	uint8_t b, c, d;
	uint8_t shift = 0, shift_last = 0, shift_count = 0, shift_lock = 0;
	uint8_t up, down, left, right;

	
	// Set callback function for USB connect event
	vs_set_connect_callback(&ledOn);

	// Set callback function for USB disconnect event
	vs_set_disconnect_callback(&ledOff);

	// Init USB pad emulation
	vs_init(true);

    //flash them leds
	#include "../shared/disco.c"

	// Pins polling and gamepad status updates
	for (;;) {
		vs_reset_watchdog();
		
		b = PINB;
		c = PINC;
		d = PIND;

		//set shifted status and detect shift lock (double click)
		if(!(d & 0x80)) {
			shift = 1;
			if (shift_last == 0) {
				if (shift_count > 1 && shift_count < 50) {  
					if (shift_lock == 0) {shift_lock = 1;} else {shift_lock = 0;}
				}
				shift_count = 0;
			}
		} else {
			shift = 0;
		} 
		shift_last = shift;
		if (shift_count <= 50) {shift_count += 1;}  //no reason to continue counting
		if (shift_lock == 1) {shift = 1;}


		//reset direction to centre
		gamepad_state.direction = 8;          //centre
		
		//DPAD (and shifted analog)
		up    = !(c&0x04);
		down  = !(d&0x01);
		left  = !(d&0x02);
		right = !(d&0x04);
		
		
		if(shift==1) {		     
			bit_clear(PORTD,0x20);
			//Analog
			if ((up)||(down)) {
					if (up) {gamepad_state.l_y_axis = 0x00;}		//A1-Up
					if (down) {gamepad_state.l_y_axis = 0xff;}		//A2-Down
			} else {gamepad_state.l_y_axis = 0x80;}
			
			if ((left)||(right)) {
					if (left) {gamepad_state.l_x_axis = 0x00;}		//A3-Left
					if (right) {gamepad_state.l_x_axis = 0xff;}	//A4-Right
			} else {gamepad_state.l_x_axis = 0x80;}			
			
		} else {
			bit_set(PORTD,0x20);			
			//Digital
			//left and right directions
			if (!(d & 0x02)) { gamepad_state.direction = 6; }	//A3-Left
			if (!(d & 0x04)) {	gamepad_state.direction = 2; }	//(A4-Right)						
			
			//up, down and diagonal directions
			if (!(c & 0x04)) {									//A1-up
				if (!(d & 0x02)) {								//A3-left
					gamepad_state.direction = 7;				//(up-left)
				}
				else if (!(d & 0x04)) {    					//A4-right
					gamepad_state.direction = 1;				//(up-right)
				} else {
					gamepad_state.direction = 0;				//(up)
				}		
			}
			if (!(d & 0x01)) {									//A2-down
				if (!(d & 0x02)) {								//A3-left
					gamepad_state.direction = 5;				//(down-left)
				}
				else if (!(d & 0x04)) {    					//A4-right
					gamepad_state.direction = 3;				//(down-right)
				} else {
					gamepad_state.direction = 4;				//(down)
				}
			}

		}
		

		//PS3 buttons
		gamepad_state.square_btn = (!(d & 0x08) == 1);		//A5-Square
		gamepad_state.cross_btn = (!(d & 0x10) == 1);		//A6-Cross
		gamepad_state.circle_btn = (!(b & 0x01) == 1);		//A9-Circle
		gamepad_state.triangle_btn = (!(b & 0x02) == 1);	//A10-Triangle
		
		//PS3 Triggers
		gamepad_state.l1_btn = (!(b & 0x04) == 1);			//B1-L1
		gamepad_state.r1_btn = (!(b & 0x08) == 1);			//B2-R1
		gamepad_state.l2_btn = (!(b & 0x10) == 1);			//B3-L2
		gamepad_state.r2_btn = (!(b & 0x20) == 1);			//B4-R2
		gamepad_state.l3_btn = (!(c & 0x80) == 1);			//B7-L3
		gamepad_state.r3_btn = (!(c & 0x40) == 1);			//B8-R3

		//PS3 Special
		gamepad_state.select_btn = (!(b & 0x40) == 1);	    //B5-L3
		gamepad_state.start_btn = (!(b & 0x80) == 1);		//B6-R3
		gamepad_state.ps_btn = (!(c & 0x20) == 1);			//B9-PS Button
		

		_delay_ms(10);  //debounce
		vs_send_pad_state();

		
	}
}
