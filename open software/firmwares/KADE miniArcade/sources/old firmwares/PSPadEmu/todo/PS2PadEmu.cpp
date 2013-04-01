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
#include "PS2PadEmu.h"

#define pinACK  9
#define pinATT  10
#define pinCMD  11
#define pinDAT  12
#define pinCLK  13

/*
 * Last 6 bytes from 0x42 response (Analog Mode):
 *
 * 	Bit0 Bit1 Bit2 Bit3 Bit4 Bit5 Bit6 Bit7
 * 	SLCT           STRT UP   RGHT DOWN LEFT - Leftmost Byte
 * 	L2   R2    L1  R1   /\   O    X    |_|
 * 	Right Joy 0x00 = Left  0xFF = Right
 * 	Right Joy 0x00 = Up    0xFF = Down
 * 	Left Joy  0x00 = Left  0xFF = Right
 * 	Left Joy  0x00 = Up    0xFF = Down      - Rightmost Byte
*/

/*
 * NON-CONFIG MODE RESPONSES
 */

/* Main polling command */
static byte response_42[8] = { 0x73, 0x5A, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F };

/* Enter/Exit Config Mode, also poll all button states, joysticks and pressures */
static byte response_43_out_config[8] = { 0x73, 0x5A, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F };

/*
 * CONFIG MODE RESPONSES
 */

/* Find out what buttons are included in poll responses. */
static byte response_41[8] = { 0xF3, 0x5A, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x5A };

/* Enter/Exit Config Mode, also poll all button states, joysticks and pressures */
static byte response_43_in_config[8] = { 0xF3, 0x5A, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F };

/* Switch modes between digital and analog */
static byte response_44[8] = { 0xF3, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* Get more status info */
static byte response_45[8] = { 0xF3, 0x5A, 0x03, 0x02, 0x01, 0x02, 0x01, 0x00 };

/* Read an unknown constant value from controller */
static byte response_46[2][8] = {{ 0xF3, 0x5A, 0x00, 0x00, 0x01, 0x02, 0x00, 0x0A },
								{ 0xF3, 0x5A, 0x00, 0x00, 0x01, 0x01, 0x01, 0x14 }};

/* Read an unknown constant value from controller */
static byte response_47[8] = { 0xF3, 0x5A, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00 };

/* Read an unknown constant value from controller */
static byte response_4c[2][8] = {{ 0xF3, 0x5A, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 },
								{ 0xF3, 0x5A, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00 }};


/* Pointer to the data array that should be returned based on the current CMD received */
volatile static byte *data_pointer = response_42;

/* Current index of the data array to be returned */
volatile static byte idx = 0;

/* Last byte received from the SPI master (i.e. PlayStation) */
volatile static byte c = 0xFF;

/* Maximum numbers of bytes to return based on the current CMD and data array */
volatile static byte limit = 8;

/* Last CMD received */
volatile static byte cmd = 0xFF;

///* Last DATA byte received */
//volatile static byte data_in = 0x00;

/* Are we in config mode or not? */
volatile static byte config_mode = 0;

/* Setup pins and initialize SPI hardware */
void ps2pad_init(void) {
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

	SPDR = data_pointer[idx];

	// Are we getting the CMD from the console?
	if (idx == 1) {

		cmd = c;

		// Respond to commands that make sense only during config_mode
		if(config_mode) {

			switch(cmd) {
			case 0x41:
				data_pointer = response_41;
				limit = 8;
				break;
			case 0x43:
				data_pointer = response_43_in_config;
				limit = 8;
				break;
			case 0x44:
				data_pointer = response_44;
				limit = 8;
				break;
			case 0x45:
				data_pointer = response_45;
				limit = 8;
				break;
			case 0x46:
				data_pointer = response_46[0];
				limit = 8;
				break;
			case 0x47:
				data_pointer = response_47;
				limit = 8;
				break;
			case 0x4C:
				data_pointer = response_4c[0];
				limit = 8;
				break;
			default:
				data_pointer = response_42; // TODO: Do not ACK and reset stuff
				limit = 8;
				break;
			}

		// We are NOT in config mode. Respond to commands that make sense.
		} else {

			switch(cmd) {
			case 0x42:
				data_pointer = response_42;
				limit = 8;
				break;
			case 0x43:
				data_pointer = response_43_out_config;
				limit = 8;
				break;
			default:
				data_pointer = response_42; // TODO: Do not ACK and reset stuff
				limit = 8;
				break;
			}

		}

		// ACK after receiving command byte

		digitalWriteFast(pinACK, LOW);

		idx++;

		digitalWriteFast(pinACK, HIGH);

	// Data received is NOT the CMD byte (idx != 1)
	} else {

		// Are we getting DATA byte in? (used by CMDs below and passed via idx 3)
		if(idx == 3) {

			//data_in = c;

			switch(cmd) {
			case 0x43:
				config_mode = c;
				break;
			case 0x46:
				data_pointer = response_46[c];
				limit = 8;
				break;
			case 0x4C:
				data_pointer = response_4c[c];
				limit = 8;
				break;
			}

//			// Last CMD is "Enter/Exit config mode". Check DATA so we know we're in config mode now.
//			if(cmd == 0x43) {
//
//				if(c == 0x01) {
//					config_mode = 1;
//				} else {
//					config_mode = 0;
//				}
//
//			// Last CMD is "Read an unknown constant value". DATA identifies the data chunk to be sent back.
//			} else if(cmd == 0x46) {
//
//				if(c == 0x01) {
//					data_pointer = response_46_1;
//					limit = 8;
//				} else {
//					data_pointer = response_46_0;
//					limit = 8;
//				}
//
//			// Last CMD is "Read an unknown constant value". DATA identifies the data chunk to be sent back.
//			} else if(cmd == 0x4C) {
//
//				if(c == 0x01) {
//					data_pointer = response_4c_1;
//					limit = 8;
//				} else {
//					data_pointer = response_4c_0;
//					limit = 8;
//				}
//
//			}
		}

		// Increment idx if there's more data to send back or cleanup if we're done for the current CMD
		if (idx < limit) {
			digitalWriteFast(pinACK, LOW);

			idx++;

			digitalWriteFast(pinACK, HIGH);
		} else {
			idx = 0;
			SPDR = 0xFF;
		}
	}
}

void ps2pad_set_pad_state(int left, int right, int up, int down, int square, int triangle, int circle, int cross, int select, int start, int l1, int l2, int r1, int r2, int lx, int ly, int rx, int ry) {
	response_43_out_config[2] = response_43_in_config[2] = response_42[2]  = (!select << 0) | (1 << 1) | (1 << 2) | (!start << 3) | (!up << 4) | (!right << 5) | (!down << 6) | (!left << 7);
	response_43_out_config[3] = response_43_in_config[3] = response_42[3]  = (!l2 << 0) | (!r2 << 1) | (!l1 << 2) | (!r1 << 3) | (!triangle << 4) | (!circle << 5) | (!cross << 6) | (!square << 7);
	response_43_out_config[4] = response_43_in_config[4] = response_42[4]  = rx;
	response_43_out_config[5] = response_43_in_config[5] = response_42[5]  = ry;
	response_43_out_config[6] = response_43_in_config[6] = response_42[6]  = lx;
	response_43_out_config[7] = response_43_in_config[7] = response_42[7]  = ly;
}
