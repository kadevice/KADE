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
* Copyright (c) 2014
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

#include "USBVirtuaStick.h"
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

uint8_t old_tbX=0, old_tbX_pinc, old_tbX_pind;
uint8_t old_tbY=0, old_tbY_pinc, old_tbY_pind;
uint8_t old_tbZ=0, old_tbZ_pinc, old_tbZ_pind;
uint8_t tb=0;
uint8_t update_cycles = 0;

uint8_t centering = 0;
uint8_t sensitivity = 1;
uint8_t resistance = 1;

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
		
	// Init USB pad emulation
	vs_init(true);

	//initial values for axis
	gamepad_state.l_x_axis=128;
	gamepad_state.l_y_axis=128;
	gamepad_state.r_x_axis=128;
	gamepad_state.r_y_axis=128;

	old_tbX_pinc = PINC; old_tbX_pind = PIND;
	old_tbY_pinc = PINC; old_tbY_pind = PIND;
	old_tbZ_pinc = PINC; old_tbZ_pind = PIND;
	
	// Pins polling and gamepad status updates
	for (;;) {
		vs_reset_watchdog();				
		//set default button states - reset direction to centre
		gamepad_state.direction=8;
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

		//HWB switches the auto-centering and resistance
		if (!(PIND&0x80)) {
			centering = 1;
		} else {
			centering = 0;
		}

		//X Axis - Read quadrative state from pins A1 and A2
		if(!(old_tbX_pinc&0x04) != !(PINC&0x04) || !(old_tbX_pind&0x01) != !(PIND&0x01) ) {		
			tb = 0;
			if (!(PINC&0x04)){ tb += 1; }
			if (!(PIND&0x01)){ tb += 2; }
			
			//Set X Axis
			if ( ((tb==0)&&(old_tbX==2)) || ((tb==1)&&(old_tbX==0)) || ((tb==3)&&(old_tbX==1)) || ((tb==2)&&(old_tbX==3)) ){
			    //Increase X Axis Position
				if ((gamepad_state.l_x_axis + sensitivity) < 256) { gamepad_state.l_x_axis += sensitivity; }
			} else if ( ((tb==0)&&(old_tbX==1)) || ((tb==2)&&(old_tbX==0)) || ((tb==3)&&(old_tbX==2)) || ((tb==1)&&(old_tbX==3)) ){
			    //Decrease X Axis Position
				if ((gamepad_state.l_x_axis - sensitivity) > -1) { gamepad_state.l_x_axis -= sensitivity; }
			}
			old_tbX = tb;
			old_tbX_pinc = PINC; old_tbX_pind = PIND;
		} else {
			if (centering==1&&update_cycles==0){
				if (gamepad_state.l_x_axis < 128){
					gamepad_state.l_x_axis += resistance;
				} else if (gamepad_state.l_x_axis > 128){
					gamepad_state.l_x_axis -= resistance;
				}
			}
		}

		//Y Axis - Read quadrative state from pins A3 and A4
		if(!(old_tbY_pind&0x02) != !(PIND&0x02) || !(old_tbY_pind&0x04) != !(PIND&0x04) ) {		
			tb = 0;
			if (!(PIND&0x02)){ tb += 1; }
			if (!(PIND&0x04)){ tb += 2; }
			
			//Set X Axis
			if ( ((tb==0)&&(old_tbY==2)) || ((tb==1)&&(old_tbY==0)) || ((tb==3)&&(old_tbY==1)) || ((tb==2)&&(old_tbY==3)) ){
			    //Increase X Axis Position
				if ((gamepad_state.l_y_axis + sensitivity) < 256) { gamepad_state.l_y_axis += sensitivity; }
			} else if ( ((tb==0)&&(old_tbY==1)) || ((tb==2)&&(old_tbY==0)) || ((tb==3)&&(old_tbY==2)) || ((tb==1)&&(old_tbY==3)) ){
			    //Decrease X Axis Position
				if ((gamepad_state.l_y_axis - sensitivity) > -1) { gamepad_state.l_y_axis -= sensitivity; }
			}
			old_tbY = tb;
			old_tbY_pinc = PINC; old_tbY_pind = PIND;
		} else {
			if (centering==1&&update_cycles==0){
				if (gamepad_state.l_y_axis < 128){
					gamepad_state.l_y_axis += resistance;
				} else if (gamepad_state.l_y_axis > 128){
					gamepad_state.l_y_axis -= resistance;
				}
			}
		}

		//Z Axis - Read quadrative state from pins A5 and A6
		if(!(old_tbZ_pind&0x08) != !(PIND&0x08) || !(old_tbZ_pind&0x10) != !(PIND&0x10) ) {		
			tb = 0;
			if (!(PIND&0x08)){ tb += 1; }
			if (!(PIND&0x10)){ tb += 2; }
			
			//Set X Axis
			if ( ((tb==0)&&(old_tbZ==2)) || ((tb==1)&&(old_tbZ==0)) || ((tb==3)&&(old_tbZ==1)) || ((tb==2)&&(old_tbZ==3)) ){
			    //Increase X Axis Position
				if ((gamepad_state.r_x_axis + sensitivity) < 256) { gamepad_state.r_x_axis += sensitivity; }
			} else if ( ((tb==0)&&(old_tbZ==1)) || ((tb==2)&&(old_tbZ==0)) || ((tb==3)&&(old_tbZ==2)) || ((tb==1)&&(old_tbZ==3)) ){
			    //Decrease X Axis Position
				if ((gamepad_state.r_x_axis - sensitivity) > -1) { gamepad_state.r_x_axis -= sensitivity; }
			}
			old_tbZ = tb;
			old_tbZ_pinc = PINC; old_tbZ_pind = PIND;
		} else {
			if (centering==1&&update_cycles==0){
				if (gamepad_state.r_x_axis < 128){
					gamepad_state.r_x_axis += resistance;
				} else if (gamepad_state.r_x_axis > 128){
					gamepad_state.r_x_axis -= resistance;
				}
			}
		}
		
		
		//send inputs every x cycles
		update_cycles += 1;
		if (update_cycles > 3){

			//read digital gamepad inputs
			//Digital
			//left and right directions
			if (!(PIND&0x20)) { gamepad_state.direction = 6; }		//A7-left
			if (!(PIND&0x40)) { gamepad_state.direction = 2; }		//A8-right						
			
			//up, down and diagonal directions
			if (!(PINB&0x01)) {									//A9-up
				if (!(PIND&0x20)) {								
					gamepad_state.direction = 7;					//(up-left)
				}
				else if (!(PIND&0x40)) {    						
					gamepad_state.direction = 1;					//(up-right)
				} else {
					gamepad_state.direction = 0;					//(up)
				}		
			}
			if (!(PINB&0x02)) {									//A10-down
				if (!(PIND&0x20)) {								
					gamepad_state.direction = 5;					//(down-left)
				}
				else if (!(PIND&0x40)) {    						
					gamepad_state.direction = 3;					//(down-right)
				} else {	
					gamepad_state.direction = 4;					//(down)
				}
			}
			
			//digital buttons
			if(!(PINB&0x04)) { gamepad_state.square_btn=0xff; }	//PIN B1
			if(!(PINB&0x08)) { gamepad_state.cross_btn=0xff; }		//PIN B2
			if(!(PINB&0x10)) { gamepad_state.circle_btn=0xff; }	//PIN B3
			if(!(PINB&0x20)) { gamepad_state.triangle_btn=0xff; }	//PIN B4
			if(!(PINB&0x40)) { gamepad_state.l1_btn=0xff; } 		//PIN B5
			if(!(PINB&0x80)) { gamepad_state.r1_btn=0xff; } 		//PIN B6
			if(!(PINC&0x80)) { gamepad_state.l2_btn=0xff; } 		//PIN B7
			if(!(PINC&0x40)) { gamepad_state.r2_btn=0xff; } 		//PIN B8
			if(!(PINC&0x20)) { gamepad_state.select_btn=0xff; }	//PIN B9
			if(!(PINC&0x10)) { gamepad_state.start_btn=0xff; } 	//PIN B10
		
			vs_send_pad_state();
			update_cycles = 0;
		}
		_delay_ms(0.3);
	}
}
