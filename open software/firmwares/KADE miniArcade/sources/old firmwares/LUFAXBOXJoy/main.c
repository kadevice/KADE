/* 
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
 */

#include "XBOXPad.h"

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
	uint8_t use_lstick = 1;
	uint8_t inverted = -1;
	

	// Set callback function to be executed after controller is detected
	xbox_set_detected_callback(&ledOn);

	// Set callback function for USB disconnect event
	xbox_set_disconnect_callback(&ledOff);

	// Init XBOX pad emulation
	xbox_init(true);

    //flash them leds
	#include "..\shared\disco.c"

    #ifdef TESTMODE
        // Don't wait for pad detection in test mode
	#else
		// Wait for pad to be detected
		while (!xbox_pad_detected()) {
			xbox_reset_watchdog();
			_delay_ms(10);
			xbox_send_pad_state();
		}
	#endif
		
	
	// Pins polling and gamepad status updates
	for (;;) {
		xbox_reset_watchdog();				
		
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
				
				
		//DPAD (and shifted analog)
		up    = !(c&0x04);
		down  = !(d&0x01);
		left  = !(d&0x02);
		right = !(d&0x04);
		
		if(shift==1) {		     
			bit_clear(PORTD,0x20);
			
			if (b & 0x01) {  //Skip button reassignment when A9 Jumper is set
			
				if (!(b & 0x40)) { //Invert Y axis on analog stick			
					inverted = inverted *-1;   							
                }
				if (inverted == 1) {
					down = !(c&0x04);
					up = !(d&0x01);
				}


				if (!(b & 0x80)) { //Toggle analog stick input			
					use_lstick = use_lstick *-1;   							
				}
				
	 
				//HWB shifted triggers for thumb buttons
				bit_write((!(d&0x08)), gamepad_state.digital_buttons, XBOX_LEFT_STICK);  //A5-LThumb
				bit_write((!(d&0x10)), gamepad_state.digital_buttons, XBOX_RIGHT_STICK); //A6-RThumb
				gamepad_state.l = 0x00;
				gamepad_state.r = 0x00;	


				if (!(c & 0x20)) { //Exit to Dashboard				
					gamepad_state.l = 0xFF;									//L/Trigger
					gamepad_state.r = 0xFF;									//R/Trigger
					gamepad_state.black = 0xFF;								//Black
					bit_write(1,gamepad_state.digital_buttons,0x20); 		//Back				
				}

			}			
			
		    //HWB shifted input to emulate left and right analog using DPAD
			if ((up)||(down)) {
				if (use_lstick == 1) {
					if (up) {gamepad_state.l_y = -32768;}				//A1-Up
					if (down) {gamepad_state.l_y = 32767;}				//A2-Down
				}
				else {
					if (up) {gamepad_state.r_y = -32768;}				//A1-Up
					if (down) {gamepad_state.r_y = 32767;}				//A2-Down
				}
			} else {
				gamepad_state.l_y = 0;
				gamepad_state.r_y = 0;
				
			}
			
			if ((left)||(right)) {
				if (use_lstick == 1) {
					if (left) {gamepad_state.l_x = -32768;}			//A3-Left
					if (right) {gamepad_state.l_x = 32767;}			//A4-Right
				} else {
					if (left) {gamepad_state.r_x = -32768;}			//A3-Left
					if (right) {gamepad_state.r_x = 32767;}			//A4-Right
				}
			} else {
				gamepad_state.l_x = 0;
				gamepad_state.r_x = 0;
			}

		} else 
		{
			bit_set(PORTD,0x20);
			
		    //normal DPAD input
			bit_write((up),gamepad_state.digital_buttons,0x01);	//A1-Up
			bit_write((down),gamepad_state.digital_buttons,0x02);	//A2-Down
			bit_write((left),gamepad_state.digital_buttons,0x04);	//A3-Left
			bit_write((right),gamepad_state.digital_buttons,0x08);	//A4-Right
		}
		
		
		if (shift==0||(!(b&0x01)) ) {
		    //normal triggers
			gamepad_state.l = (!(d&0x08)) * 0xFF;					//A5-L/Trigger
			gamepad_state.r = (!(d&0x10)) * 0xFF;		 			//A6-R/Trigger
			bit_clear(gamepad_state.digital_buttons, XBOX_LEFT_STICK);
			bit_clear(gamepad_state.digital_buttons, XBOX_RIGHT_STICK);
		}
		
		
        //ABXY Buttons
        gamepad_state.a = (!(b&0x04)) * 0xFF;						//B1-A
        gamepad_state.b = (!(b&0x08)) * 0xFF;						//B2-B
        gamepad_state.x = (!(b&0x10)) * 0xFF;						//B3-X
        gamepad_state.y = (!(b&0x20)) * 0xFF;						//B4-Y
		
		
		//White and Black
		gamepad_state.black = (!(b & 0x40)) * 0xFF;				//B5-Black
		gamepad_state.white = (!(b & 0x80)) * 0xFF;				//B6-White
		        

        //Back and Start
		//Also Exit assigned to specific pin.		
		if(!(c&0x20)) { // B9-Exit(Start+Back)
		
			////detect a short or a long press of the exit button
			uint8_t longcount = 0;        
			while ((!(c&0x20)) && longcount <= 40) {
				xbox_reset_watchdog();		
				c = PINC;
				_delay_ms(100);      //wait for 1/10th second
				longcount ++;		
			}
							
			//a short press will exit game,  a long press will exit to dash
			if (longcount < 40) {    // a short press
				bit_write(1,gamepad_state.digital_buttons,0x10); 		// Start
				bit_write(1,gamepad_state.digital_buttons,0x20); 		// Back
			} else {                 // a long press
				gamepad_state.l = 0xFF;									//L/Trigger
				gamepad_state.r = 0xFF;									//R/Trigger
				gamepad_state.black = 0xFF;								//Black
				bit_write(1,gamepad_state.digital_buttons,0x20); 		//Back				
			}		
			
			
		} else {
		    if ( (!(b&0x02)) && (!(c&0x80)) && (!(c&0x40)) ){
			  //Don't allow simultaneous start+back if A10 jumper is set to disabled
			}
			else {
				bit_write((!(c&0x80)),gamepad_state.digital_buttons,0x10); //B7-Start
				bit_write((!(c&0x40)),gamepad_state.digital_buttons,0x20); //B8-Back
			}
		}
				
		
		/* REFERENCE TO MINIMUS MAPPINGS
		(!(c & 0x04)) //PIN A1
        (!(d & 0x01)) //PIN A2
        (!(d & 0x02)) //PIN A3
        (!(d & 0x04)) //PIN A4
        (!(d & 0x08)) //PIN A5
        (!(d & 0x10)) //PIN A6
        (!(d & 0x20)) //PIN A7
        (!(d & 0x40)) //PIN A8
        (!(b & 0x01)) //PIN A9
        (!(b & 0x02)) //PIN A10
        (!(b & 0x04)) //PIN B1
        (!(b & 0x08)) //PIN B2
        (!(b & 0x10)) //PIN B3
        (!(b & 0x20)) //PIN B4
        (!(b & 0x40)) //PIN B5
        (!(b & 0x80)) //PIN B6
        (!(c & 0x80)) //PIN B7
        (!(c & 0x40)) //PIN B8
        (!(c & 0x20)) //PIN B9
        (!(c & 0x10)) //PIN B10
        */
		_delay_ms(10);  //debounce
		xbox_send_pad_state();
	}
}
