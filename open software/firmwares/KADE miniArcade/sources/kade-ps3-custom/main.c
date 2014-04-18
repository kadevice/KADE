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
* Bruno Freitas - bootsector@ig.com.br
* Jon Wilson    - degenatrons@gmail.com
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
 
#include "USBVirtuaStick.h"
#include "../shared/trackball/common.h"
#include "../shared/generic_header.c"
#include "../shared/jump.c"
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

int main(void) {
	// Set clock @ 16Mhz
	CPU_PRESCALE(0);		

	//Set initial pin states.
    DDRB=0x00;
    DDRC=0x00;
    DDRD=0x00;
    PORTB=0xFF;
    PORTC=0xFF;
    PORTD=0xFF;
	
	//Generic functions used with this firmware	(there are others)
    uint8_t func_dpad_up       = 1;
    uint8_t func_dpad_down     = 2;
    uint8_t func_dpad_left     = 3;
    uint8_t func_dpad_right    = 4;
    uint8_t func_restrict_4way = 22;
    uint8_t func_invert_y_axis = 23;
    uint8_t func_autofire_1    = 24;
    uint8_t func_autofire_2    = 25;
    uint8_t func_autofire_3    = 26;
    uint8_t func_autofire_4    = 27;
	uint8_t func_ext_shift_led = 28;
    uint8_t func_ext_power_led = 29;	
	uint8_t func_program_mode  = 30;	
	
	//Use default restriction logic (in generic_main_preloop.c)
	uint8_t default_restrict   = 0;	
	
	//Generic main
	#include "../shared/generic_main_init.c"
	
	// Init USB pad emulation
	vs_init(true);
	
	// Init Trackball if needed
	if (setting_enable_tb1==1){
		PORTD |= (1<<6);
		initTrackBall(setting_tb1_counts, setting_tb1_samples);
	}

	// Pins polling and gamepad status updates
	for (;;) {
		vs_reset_watchdog();
				
		//generic stuff at start of main loop
		#include "../shared/generic_main_preloop.c"

		//set default button states - reset direction to centre
		gamepad_state.direction=8;
		gamepad_state.l_y_axis=0x80;
		gamepad_state.l_x_axis=0x80;
		gamepad_state.r_y_axis=0x80;
		gamepad_state.r_x_axis=0x80;
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
		gamepad_state.square_axis=0x00;
		gamepad_state.cross_axis=0x00;
		gamepad_state.circle_axis=0x00;
		gamepad_state.triangle_axis=0x00;
		gamepad_state.l1_axis=0x00;
		gamepad_state.r1_axis=0x00;
		gamepad_state.l2_axis=0x00;
		gamepad_state.r2_axis=0x00;
		gamepad_state.select_btn=0x00;
		gamepad_state.start_btn=0x00;
		gamepad_state.ps_btn=0x00;		
				
		//Handle dpad and restricted movement
		//PS3 restriction is easier to manage - ignore mainloop
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

		//Trackballs Analog
		//NOTE: COME BACK AND TIDY THIS LOGIC IF IT WORKS WELL
		if (setting_enable_tb1==1){
			if(setting_tb1_trackball==1){
				if (setting_tb1_stick==1){ 
					//Right Analog (1=Right)
					//
					//Y Axis (Trackball)
					if(abs(ps2_y) < 32){
						gamepad_state.r_y_axis = 255 - (ps2_y + 128);
					} else {
						if (ps2_y > 31){gamepad_state.r_y_axis = 0x00;}
						if (ps2_y < -31){gamepad_state.r_y_axis = 0xFF;}		
					}
					//X Axis (Trackball)
					if(abs(ps2_x) < 32){
						gamepad_state.r_x_axis = ps2_x + 128;
					} else {
						if (ps2_x > 31){gamepad_state.r_x_axis = 0xFF;}
						if (ps2_x < -31){gamepad_state.r_x_axis = 0x00;}		
					}			
				} else {
					//Left Analog (0=Left)
					//
					//Y Axis (Trackball)
					if(abs(ps2_y) < 32){
						gamepad_state.l_y_axis = 255 - (ps2_y + 128);
					} else {
						if (ps2_y > 31){gamepad_state.l_y_axis = 0x00;}
						if (ps2_y < -31){gamepad_state.l_y_axis = 0xFF;}		
					}
					//X Axis (Trackball)
					if(abs(ps2_x) < 32){
						gamepad_state.l_x_axis = ps2_x + 128;
					} else {
						if (ps2_x > 31){gamepad_state.l_x_axis = 0xFF;}
						if (ps2_x < -31){gamepad_state.l_x_axis = 0x00;}		
					}			
				}			
			} else {
				if (setting_tb1_stick==1){ 
					//Right Analog (1=Right)
					gamepad_state.r_y_axis = 255 - (ps2_y + 128);
					gamepad_state.r_x_axis = ps2_x + 128;
				} else {
					//Left Analog (0=Left)
					gamepad_state.l_y_axis = 255 - (ps2_y + 128);
					gamepad_state.l_x_axis = ps2_x + 128;
				}			
			}
		}
		

		//loop through pins checking for inputs from those that are assigned a function
		//for(cnt=0;cnt<20;cnt++) {
		for(cnt=0;cnt<20;cnt++) {
			pos=cnt;					
			if (!(state[cnt])) {
				//there is input on this pin
				if (shift==1){pos=pos+20;}  //+20 if this is shifted input
				
				if (ass[pos]>0) {
					//there is an assignment to a function
					action = ass[pos];
					#include "main_actions.c"
				}
			}
		}
		
		//Trackball Buttons
		if (setting_enable_tb1==1){
			for(pos=0;pos<3;pos++) {
				if (shift==1){
					if (pos==0){action = setting_tb1_but1s;}
					if (pos==1){action = setting_tb1_but2s;}
					if (pos==2){action = setting_tb1_but3s;}
				} else {
					if (pos==0){action = setting_tb1_but1;}
					if (pos==1){action = setting_tb1_but2;}
					if (pos==2){action = setting_tb1_but3;}
				}
			
				if (action > 0) {
					if (((0b00000001 & ps2data[0])&&(pos==0))||((0b00000010 & ps2data[0])&&(pos==1))||((0b00000100 & ps2data[0])&&(pos==2))){
						#include "main_actions.c"
					}
				}
			}
		}
		
		
		_delay_ms(2);  //debounce
		vs_send_pad_state();		
	}
}
