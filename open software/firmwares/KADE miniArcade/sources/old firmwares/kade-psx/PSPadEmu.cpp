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

#include <WProgram.h>
#include "digitalWriteFast.h"
#include "PSPadEmu.h"

#define pinACK  A0
#define pinATT  10
#define pinCMD  11
#define pinDAT  12
#define pinCLK  13

/*
 * Last 6 bytes from 0x42 response (Analog Mode):
 *
 * 	Bit0 Bit1 Bit2 Bit3 Bit4 Bit5 Bit6 Bit7
 * 	SLCT L3    R3  STRT UP   RGHT DOWN LEFT - Leftmost Byte
 * 	L2   R2    L1  R1   /\   O    X    |_|
 * 	Right Joy 0x00 = Left  0xFF = Right
 * 	Right Joy 0x00 = Up    0xFF = Down
 * 	Left Joy  0x00 = Left  0xFF = Right
 * 	Left Joy  0x00 = Up    0xFF = Down      - Rightmost Byte
*/

/* Main polling command */
static byte response_42[8] = { 0x73, 0x5A, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F };

/* Enter/Exit config mode + polling */
static byte response_43[3] = { 0x73, 0x5A, 0x01 };

/* Pointer to the data array that should be returned based on the current CMD received */
volatile static byte *data_pointer = response_42;

/* Current index of the data array to be returned */
volatile static byte idx = 0;

/* Last byte received from the SPI master (i.e. PlayStation) */
volatile static byte c = 0xFF;

/* Maximum numbers of bytes to return based on the current CMD and data array */
volatile static byte limit = 8;

/* Setup pins and initialize SPI hardware */
void pspad_init(void) {
	pinModeFast(pinACK, OUTPUT);
	digitalWriteFast(pinACK, HIGH);

	pinModeFast(pinATT, INPUT);
	digitalWriteFast(pinATT, HIGH);

	pinModeFast(pinCMD, INPUT);
	digitalWriteFast(pinCMD, HIGH);

	pinModeFast(pinDAT, OUTPUT);
	digitalWriteFast(pinDAT, HIGH);

	pinModeFast(pinCLK, INPUT);
	digitalWriteFast(pinCLK, HIGH);

	SPCR |= (1 << CPOL); // SCK HIGH when idle
	SPCR |= (1 << CPHA); // setup data on falling edge of CLK, read on rising edge

	// turn on SPI in slave mode
	SPCR |= _BV(SPE);

	SPCR |= (1 << DORD); // data order to LSB first

	// turn on interrupts
	SPCR |= _BV(SPIE);
}

/* SPI interrupt routine */
ISR (SPI_STC_vect) {
	c = SPDR;

	if(((idx == 0) && (c != 0x01)) || (idx >= limit)) {

		idx = 0;
		SPDR = 0xFF;

	} else {

		SPDR = data_pointer[idx];

		if(idx == 1) {
			switch(c) {
			case 0x42:
				data_pointer = response_42;
				limit = 8;
				break;
			case 0x43:
				data_pointer = response_43;
				limit = 3;
				break;
			default:
				data_pointer = response_42;
				limit = 8;
				break;
			}
		}

		digitalWriteFast(pinACK, LOW);

		idx++;

		digitalWriteFast(pinACK, HIGH);
	}
}

void pspad_set_pad_state(int left, int right, int up, int down, int square, int triangle, int circle, int cross, int select, int start, int l1, int l2, int r1, int r2, int l3, int r3, int lx, int ly, int rx, int ry) {
	response_42[2]  = (!select << 0) | (!l3 << 1) | (!r3 << 2) | (!start << 3) | (!up << 4) | (!right << 5) | (!down << 6) | (!left << 7);
	response_42[3]  = (!l2 << 0) | (!r2 << 1) | (!l1 << 2) | (!r1 << 3) | (!triangle << 4) | (!circle << 5) | (!cross << 6) | (!square << 7);
	response_42[4]  = rx;
	response_42[5]  = ry;
	response_42[6]  = lx;
	response_42[7]  = ly;
}

