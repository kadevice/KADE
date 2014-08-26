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

#include <avr/interrupt.h>
#include <string.h>
#include "PSPadEmu.h"

#define PORT_SPI PORTB
#define DDR_SPI  DDRB

#define bitATT  1 << 0
#define bitCMD  1 << 2
#define bitDAT  1 << 3
#define bitCLK  1 << 1

#define PORT_ACK PORTB
#define DDR_ACK  DDRB

#define bitACK  1 << 4

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

/* Response header */
static byte response_header[2] = { 0x41, 0x5A };

/* Main polling command */
static byte response_42[6] = { 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F };

/* 0x44: Switch modes between digital and analog */
/* ox4F: Add or remove analog response bytes from the main polling command  */
static byte response_44_4F[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* Get more status info - index 2 tells if LED is OFF (0x00) or ON (0x01)*/
static byte response_45[6] = { 0x01, 0x02, 0x00, 0x02, 0x01, 0x00 };

/* Read an unknown constant value from controller (two pass) */
static byte response_4C_0[6] = { 0x00, 0x00, 0x00, 0x04, 0x00, 0x00 };
static byte response_4C_1[6] = { 0x00, 0x00, 0x00, 0x07, 0x00, 0x00 };

/* Map bytes in the 0x42 command to actuate the vibration motors */
static byte response_4D[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

/* Read an unknown constant value from controller */
static byte response_47[6] = { 0x00, 0x00, 0x02, 0x00, 0x01, 0x00 };

/* Read an unknown constant value from controller (two pass) */
static byte response_46_0[6] = { 0x00, 0x00, 0x01, 0x02, 0x00, 0x0A };
static byte response_46_1[6] = { 0x00, 0x00, 0x01, 0x01, 0x01, 0x14 };

/* Pointer to the data array that should be returned based on the current CMD received */
volatile static byte *data_pointer = response_42;

/* Current index of the data array to be returned */
volatile static byte idx = 0;

/* Last byte received from the SPI master (i.e. PlayStation) */
volatile static byte c = 0xFF;

/* Last command received from SPI master */
volatile static byte last_command = 0xFF;

/* Tells whether we are in digital or analog mode */
volatile static byte analog_mode = 0x00;

/* Timeout so we don't change modes more than once within a second */
#define TOGGLE_MODE_TIMEOUT_VALUE 60
volatile static byte toggle_mode_timeout = TOGGLE_MODE_TIMEOUT_VALUE;

/* Maximum numbers of bytes to return based on the current CMD and data array */
volatile static byte limit = 4;

/* Optional callback function to be called after SPI bytes transfer */
static void (*spi_callback)(void) = NULL;

/* Setup pins and initialize SPI hardware */
void pspad_init(int mode) {
	bit_set(DDR_ACK, bitACK);
	bit_set(PORT_ACK, bitACK);

	bit_clear(DDR_SPI, bitATT);
	bit_set(PORT_SPI, bitATT);

//	bit_clear(DDR_SPI, bitCMD);
//	bit_set(PORT_SPI, bitCMD);

	bit_set(DDR_SPI, bitDAT);
	bit_set(PORT_SPI, bitDAT);

//	bit_clear(DDR_SPI, bitCLK);
//	bit_set(PORT_SPI, bitCLK);

	pspad_set_mode(mode);

	SPCR |= (1 << CPOL); // SCK HIGH when idle
	SPCR |= (1 << CPHA); // setup data on falling edge of CLK, read on rising edge

	// turn on SPI in slave mode
	SPCR |= _BV(SPE);

	SPCR |= (1 << DORD); // data order to LSB first

	// turn on interrupts
	SPCR |= _BV(SPIE);

	// SS line Pin Change Interrupt Enable
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT0);

	/* Initializes SPI data register */
	SPDR = 0xFF;

	sei();
}

/* SPI interrupt routine */
ISR (SPI_STC_vect) {

	/* Read byte from SPI data register */
	c = SPDR;

	/* If first byte is not 0x01 or we're sending the last buffer byte, don't ACK and reset */
	if(((idx == 0) && (c != 0x01)) || (idx >= limit)) {

		idx = 0;
		SPDR = 0xFF;

	} else {

		/* Send data from header or response buffer depending on the current index */
		SPDR = (idx > 1) ? data_pointer[idx - 2] : response_header[idx];

		/* Acknowledge byte received from SPI master */
		bit_clear(PORT_ACK, bitACK);

		asm volatile ("nop\nnop\nnop\nnop\n");
		asm volatile ("nop\nnop\nnop\nnop\n");
		asm volatile ("nop\nnop\nnop\nnop\n");
		asm volatile ("nop\nnop\nnop\nnop\n");

		bit_set(PORT_ACK, bitACK);

		/* Process known commands sent by SPI master */
		if(idx == 1) {

			last_command = c;

			switch(c) {
			case 0x43:
			case 0x42:
				data_pointer = response_42;
				break;
			case 0x45:
				data_pointer = response_45;
				break;
			case 0x4c:
				data_pointer = response_4C_0;
				break;
			case 0x4d:
				data_pointer = response_4D;
				break;
			case 0x44:
			case 0x4f:
				data_pointer = response_44_4F;
				break;
			case 0x46:
				data_pointer = response_46_0;
				break;
			case 0x47:
				data_pointer = response_47;
				break;
			default:
				data_pointer = response_42;
				break;
			}

			// If in config mode, limit should be always 8
			if(response_header[0] == 0xF3) {
				limit = 8;
			} else {
				limit = analog_mode ? 8 : 4;
			}

		/* When idx == 3 we might process some parameters depending on the current command */
		} else if(idx == 3) {

			switch(last_command) {
			case 0x4C:
				data_pointer = (c == 0x00) ? response_4C_0 : response_4C_1;
				break;
			case 0x46:
				data_pointer = (c == 0x00) ? response_46_0 : response_46_1;
				break;
			case 0x43:
				if(c == 0x01) {
					response_header[0] = 0xF3;
				} else {
					response_header[0] = analog_mode ? 0x73 : 0x41;
				}
				break;
			case 0x44:
				analog_mode = c;
				response_45[2] = analog_mode ? 0x01 : 0x00;
				break;
			}

			// Revert toggle status byte on header if changed by the set_mode function
			response_header[1] = 0x5A;

		}

		idx++;
	}
}

ISR(PCINT0_vect)
{
	pspad_ss_int_handler();
}

void pspad_ss_int_handler(void) {
	if(PINB & bitATT) {
		SPDR = 0xFF;
		idx = 0;

		if(toggle_mode_timeout > 0) {
			toggle_mode_timeout--;
		}

		if(spi_callback)
			spi_callback();
	}
}

void pspad_toggle_mode(void) {

	if(toggle_mode_timeout > 0)
		return;

	if(analog_mode) {
		pspad_set_mode(PSPADEMU_MODE_DIGITAL);
	} else {
		pspad_set_mode(PSPADEMU_MODE_ANALOG);
	}

	toggle_mode_timeout = TOGGLE_MODE_TIMEOUT_VALUE;
}

int pspad_get_mode(void) {
	return analog_mode ? PSPADEMU_MODE_ANALOG : PSPADEMU_MODE_DIGITAL;
}

void pspad_set_pad_state(int left, int right, int up, int down, int square, int triangle, int circle, int cross, int select, int start, int l1, int l2, int r1, int r2, int l3, int r3, int lx, int ly, int rx, int ry) {
	response_42[0]  = (!select << 0) | (!l3 << 1) | (!r3 << 2) | (!start << 3) | (!up << 4) | (!right << 5) | (!down << 6) | (!left << 7);
	response_42[1]  = (!l2 << 0) | (!r2 << 1) | (!l1 << 2) | (!r1 << 3) | (!triangle << 4) | (!circle << 5) | (!cross << 6) | (!square << 7);
	response_42[2]  = rx;
	response_42[3]  = ry;
	response_42[4]  = lx;
	response_42[5]  = ly;
}

void pspad_set_mode(int mode) {
	if(mode == PSPADEMU_MODE_ANALOG) {
		analog_mode = 0x01;

		if(response_header[0] != 0xF3)
			response_header[0] = 0x73;

		response_45[2] = 0x01;
	} else {
		analog_mode = 0x00;

		if(response_header[0] != 0xF3)
			response_header[0] = 0x41;

		response_45[2] = 0x00;
	}

	response_header[1] = 0x00;
}

void pspad_set_spi_callback(void (*callback)(void)) {
	spi_callback = callback;
}


