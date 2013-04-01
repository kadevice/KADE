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
