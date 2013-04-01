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

#include "PSPadEmu.h"

//#define F_USB 8000000
//#include "..\shared\jump.c"

#include <util/delay.h>

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
#define bit_set(p,m) ((p) |= (m)) 
#define bit_clear(p,m) ((p) &= ~(m)) 
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m)) 

//eeprom
#include <avr/eeprom.h>
#define read_eeprom_byte(address) eeprom_read_byte ((const uint8_t*)address)
#define write_eeprom_byte(address,value) eeprom_write_byte ((uint8_t*)address,(uint8_t)value)

int main(void) {

	// Disable AVR internal Voltage Regulator
	REGCR |= (1 << REGDIS);

	// Set clock @ 8Mhz
	CPU_PRESCALE(1);

	//Set initial pin states.  These are adjusted based on eeprom settings.
	bit_clear(DDRD, 0x80); bit_set(PORTD, 0x80); //hwb
	bit_clear(DDRC, 0x04); bit_set(PORTC, 0x04); //a1
	bit_clear(DDRD, 0x01); bit_set(PORTD, 0x01); //a2
	bit_clear(DDRD, 0x02); bit_set(PORTD, 0x02); //a3
	bit_clear(DDRD, 0x04); bit_set(PORTD, 0x04); //a4
	bit_clear(DDRD, 0x08); bit_set(PORTD, 0x08); //a5
	bit_clear(DDRD, 0x10); bit_set(PORTD, 0x10); //a6
	bit_clear(DDRD, 0x20); bit_set(PORTD, 0x20); //a7
	bit_clear(DDRD, 0x40); bit_set(PORTD, 0x40); //a8
	bit_clear(DDRB, 0x20); bit_set(PORTB, 0x20); //b4
	bit_clear(DDRB, 0x40); bit_set(PORTB, 0x40); //b5
	bit_clear(DDRB, 0x80); bit_set(PORTB, 0x80); //b6
	bit_clear(DDRC, 0x80); bit_set(PORTC, 0x80); //b7
	bit_clear(DDRC, 0x40); bit_set(PORTC, 0x40); //b8
	bit_clear(DDRC, 0x20); bit_set(PORTC, 0x20); //b9
	bit_clear(DDRC, 0x10); bit_set(PORTC, 0x10); //b10 ***added

	//dpad and pad restrictions
	uint8_t	u=0, d=0, l=0, r=0, pu=0, pd=0, pl=0, pr=0;
	uint8_t dp_pp=0, dp_lp=0, set;
	
	//pin assignments and button states
	uint8_t	pos=0, cnt=0;
	uint8_t ass[40], state[20];
	
	//handle shift and shift lock
	uint8_t shift=0, shift_last=0, shift_count=0, shift_lock=0;
	
	//handle settings
	uint8_t invert, restrict4;
	uint8_t setting_delay;
	uint8_t autofire, auto_toggle=1;
	uint8_t active=0, delay_power=0, led_active=0;
	int up, down, left, right, sqre, cross, circle, triangle, select, start, l1, r1, l2, r2, l3, r3, lx, ly, rx, ry;
	
    //Flash LEDs
	//Commented out for testing of XBOX 360 adapter!!
	//#include "..\shared\disco.c"

	//read first 40 eeprom into an array (pins + shifted pins)
	for(cnt=0;cnt<40;cnt++){	
		ass[cnt]=read_eeprom_byte(cnt);
		
		//set output pins
		if ((ass[cnt]==27)||(ass[cnt]==28)){
			#include "..\shared\outputs.c"		
		}
		if (ass[cnt]==28){delay_power=1;}
		
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
			if (ass[cnt]==28){
				led_active = shift;
				#include "..\shared\showleds.c"
			}
		}
	}	

	// Init PS Pad emulator SPI hardware
	pspad_init();

	for(;;) {

		//read KADE pin states into an array
		#include "..\shared\state.c"		
		
		//set shifted status and detect shift lock (double click)
		#include "..\shared\shift.c"		

		//set default button states
		up=0;
		down=0;
		left=0;
		right=0;
		sqre=0;
		cross=0;
		circle=0;
		triangle=0;
		select=0;
		start=0;
		l1=0;
		r1=0;
		l2=0;
		r2=0;
		l3=0;
		r3=0;
		lx=0x7F;
		ly=0x7F;
		rx=0x7F;
		ry=0x7F;
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
				
				if ((ass[cnt]==22)||(ass[pos]==22)){invert=1;}     //invert Y axis
				if ((ass[cnt]==21)||(ass[pos]==21)){restrict4=1;}  //restrict dPad 4-way
				if ((ass[pos]>=23)&&(ass[pos]<=26)){autofire=1;}   //autofire mode
				if (ass[pos]==1){u=1;}
				if (ass[pos]==2){d=1;}				
				if (ass[pos]==3){l=1;}
				if (ass[pos]==4){r=1;}
			}
			
			//Show the shift status LED(s) and power up externals with delay
			if (ass[cnt]==27){
				active = shift;
				#include "..\shared\showleds.c"								
			}
		}

		//autofire toggle
		if(autofire==1){
			auto_toggle = auto_toggle * -1;
		}

		//Handle dpad and restricted movement
		if(restrict4==0){
			if (u==1){up=1;}
			if (d==1){down=1;}
			if (l==1){left=1;}
			if (r==1){right=1;}					
		} else {
			//Restrict Dpad to 4-way operation.  
			//Movement is based on weighting of directions compared to current position
			set=0;
			if ((u==pu)&&(d==pd)&&(l==pl)&&(r==pr)){ dp_pp = dp_lp; }						
			dp_lp=dp_pp;
			
			if(dp_pp==1){
				if ((d==1)&&(set==0)){down=1;  dp_pp=2; set=1;}
				if ((l==1)&&(set==0)){left=1;  dp_pp=3; set=1;}
				if ((r==1)&&(set==0)){right=1; dp_pp=4; set=1;}											
				if ((u==1)&&(set==0)){up=1;    dp_pp=1; set=1;}
			}						
			if(dp_pp==2){
				if ((u==1)&&(set==0)){up=1;    dp_pp=1; set=1;}
				if ((l==1)&&(set==0)){left=1;  dp_pp=3; set=1;}
				if ((r==1)&&(set==0)){right=1; dp_pp=4; set=1;}											
				if ((d==1)&&(set==0)){down=1;  dp_pp=2; set=1;}
			}						
			if(dp_pp==3){
				if ((r==1)&&(set==0)){right=1; dp_pp=4; set=1;}											
				if ((u==1)&&(set==0)){up=1;    dp_pp=1; set=1;}
				if ((d==1)&&(set==0)){down=1;  dp_pp=2; set=1;}
				if ((l==1)&&(set==0)){left=1;  dp_pp=3; set=1;}
			}						
			if((dp_pp==4)||(dp_pp==0)){
				if ((l==1)&&(set==0)){left=1;  dp_pp=3; set=1;}
				if ((u==1)&&(set==0)){up=1;    dp_pp=1; set=1;}
				if ((d==1)&&(set==0)){down=1;  dp_pp=2; set=1;}
				if ((r==1)&&(set==0)){right=1; dp_pp=4; set=1;}											
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
					if (ass[pos]==5){sqre=1;}
					if (ass[pos]==6){cross=1;}
					if (ass[pos]==7){circle=1;}
					if (ass[pos]==8){triangle=1;}
					
					//Autofire
					if (autofire==1){
						if(auto_toggle==1){
							if (ass[pos]==23){sqre=1;}
							if (ass[pos]==24){cross=1;}
							if (ass[pos]==25){circle=1;}
							if (ass[pos]==26){triangle=1;}
						}
						_delay_ms(15);
					}
					
					//Triggers
					if (ass[pos]==9){l1=1;}   		    //L1
					if (ass[pos]==10){r1=1;}  		    //R1					
					if (ass[pos]==11){l2=1;}  		    //L2
					if (ass[pos]==12){r2=1;}   		//R2
					if (ass[pos]==15){l3=1;}  		    //L3
					if (ass[pos]==16){r3=1;}			//R3
					
					//Special
					if (ass[pos]==13){select=1;}		//Select
					if (ass[pos]==14){start=1;}		//Start
					
					//Left Analog Stick
					if (ass[pos]==17+invert){ly = 0x00;} 	//Left Analog Up
					if (ass[pos]==18-invert){ly = 0xff;} 	//Left Analog Down
					if (ass[pos]==19){lx = 0x00;} 			//Left Analog Left
					if (ass[pos]==20){lx = 0xff;} 			//Left Analog Right

					//Right Analog Stick
					if (ass[pos]==29+invert){ly = 0x00;} 	//Right Analog Up
					if (ass[pos]==30-invert){ly = 0xff;} 	//Right Analog Down
					if (ass[pos]==31){lx = 0x00;} 			//Right Analog Left
					if (ass[pos]==32){lx = 0xff;} 			//Right Analog Right	

//					//Enter programming mode
//					if (ass[pos]==33){Jump_To_Bootloader();}					//Program mode									
				}
			}
		}
			
		pspad_set_pad_state(left, right, up, down, sqre, triangle, circle,
			cross, select, start, l1, l2, r1, r2, l3, r3, lx, ly, rx, ry);
		_delay_ms(2);  //debounce
	}
}