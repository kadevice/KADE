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
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
#define bit_set(p,m) ((p) |= (m)) 
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m)) 

int main(void) {
	CPU_PRESCALE(0);		
	
	//make everything output
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;
	PORTB = 0xFF;
    PORTC = 0xFF;
    PORTD = 0xFF;
	//...except inputs on B9 and B10
	PORTC = (0<<5);
	PORTC = (0<<6);
		
	uint8_t delay = 25;
	uint8_t s, d;

	uint8_t seq[36][12] = {
		//single vertical bar moving left/right
		{0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,0,0,1,0},
        {0,0,0,0,0,0,0,0,1,0,0,1},
        {0,0,0,0,0,0,0,1,0,0,1,0},
        {0,0,0,0,0,0,1,0,0,1,0,0},
        {0,0,1,0,0,1,0,0,0,0,0,0},
        {0,1,0,0,1,0,0,0,0,0,0,0},
        {1,0,0,1,0,0,0,0,0,0,0,0},

		//single vertical bar moving left/right with fill
		{1,1,0,1,1,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,0,0,1,0,0},
        {1,1,1,1,1,1,1,1,0,1,1,0},
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,0,1,1,0},
        {1,1,1,1,1,1,1,0,0,1,0,0},
        {1,1,1,1,1,1,0,0,0,0,0,0},
        {1,1,0,1,1,0,0,0,0,0,0,0},
        {1,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},

		//single led clockwise loop
        {1,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,0,0,0},
	};			
	
	while(1) {				

		for (s=0; s<35; s++) {						
			bit_write(seq[s][0], DDRC, 0x04); bit_write(seq[s][0]*-1, PORTC, 0x04); //A1
			bit_write(seq[s][1], DDRD, 0x01); bit_write(seq[s][1]*-1, PORTD, 0x01); //A2
			bit_write(seq[s][2], DDRD, 0x02); bit_write(seq[s][2]*-1, PORTD, 0x02); //A3
			bit_write(seq[s][3], DDRD, 0x04); bit_write(seq[s][3]*-1, PORTD, 0x04); //A4
			bit_write(seq[s][4], DDRD, 0x08); bit_write(seq[s][4]*-1, PORTD, 0x08); //A5
			bit_write(seq[s][5], DDRD, 0x10); bit_write(seq[s][5]*-1, PORTD, 0x10); //A6
			bit_write(seq[s][6], DDRB, 0x01); bit_write(seq[s][6]*-1, PORTB, 0x01); //A9
			bit_write(seq[s][7], DDRB, 0x02); bit_write(seq[s][7]*-1, PORTB, 0x02); //A10
			bit_write(seq[s][8], DDRB, 0x04); bit_write(seq[s][8]*-1, PORTB, 0x04); //B1
			bit_write(seq[s][9], DDRB, 0x08); bit_write(seq[s][9]*-1, PORTB, 0x08); //B2
			bit_write(seq[s][10],DDRB, 0x10); bit_write(seq[s][10]*-1,PORTB, 0x10); //B3
			bit_write(seq[s][11],DDRB, 0x20); bit_write(seq[s][11]*-1,PORTB, 0x20); //B4

			if(!(PINC & 0x20)) { 
			  delay = 50; _delay_ms(2);
			} else if (!(PINC & 0x10)) {
			  delay = 10; _delay_ms(2);
			} else {
			  delay = 18;
			}
			
			for (d=0; d<delay; d++) {
				_delay_ms(10);
			}
		}		
	} 
}
