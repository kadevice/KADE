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

// PSX Buttons
int up 			= 0;
int down 		= 0;
int left 		= 0;
int right 		= 0;
int sqre 		= 0;
int cross 		= 0;
int circle 		= 0;
int triangle 	= 0;
int select 		= 0;
int start 		= 0;
int l1 			= 0;
int r1 			= 0;
int l2 			= 0;
int r2 			= 0;
int l3 			= 0;
int r3 			= 0;
int lx 			= 0x7F;
int ly 			= 0x7F;
int rx 			= 0x7F;
int ry 			= 0x7F;

#define PIN_UP 			9
#define PIN_DOWN 		8
#define PIN_LEFT 		7
#define PIN_RIGHT 		6
#define PIN_SQUARE 		5
#define PIN_CROSS 		4
#define PIN_CIRCLE 		3
#define PIN_TRIANGLE 	2
#define PIN_SELECT 		1 // TX
#define PIN_START 		0 // RX
#define PIN_L1 			A1
#define PIN_R1 			A2

#define PIN_SHIFT A3

/*
 * Missing button mappings:
 * L2, R2, L3, R3, Analog Sticks
 *
 * TODO: Try to find the best shifting scheme for the missing buttons above.
 *
 */

void setup(void) {
	// Init PSX pad emulator
	pspad_init();

	// Configure arcade pins as INPUT and pullups ON
	for(int i = 0; i < 10; i++) {
		pinModeFast(i, INPUT);
		digitalWriteFast(i, HIGH);
	}

	pinModeFast(A1, INPUT);
	digitalWriteFast(A1, HIGH);

	pinModeFast(A2, INPUT);
	digitalWriteFast(A2, HIGH);

	pinModeFast(A3, INPUT);
	digitalWriteFast(A3, HIGH);
}

void loop(void) {
	left 		= !digitalReadFast(PIN_LEFT);
	right 		= !digitalReadFast(PIN_RIGHT);
	up 			= !digitalReadFast(PIN_UP);
	down 		= !digitalReadFast(PIN_DOWN);
	sqre 		= !digitalReadFast(PIN_SQUARE);
	triangle 	= !digitalReadFast(PIN_TRIANGLE);
	circle 		= !digitalReadFast(PIN_CIRCLE);
	cross 		= !digitalReadFast(PIN_CROSS);
	select 		= !digitalReadFast(PIN_SELECT);
	start 		= !digitalReadFast(PIN_START);
	l1 			= !digitalReadFast(PIN_L1);
	r1 			= !digitalReadFast(PIN_R1);

	pspad_set_pad_state(left, right, up, down, sqre, triangle, circle,
		cross, select, start, l1, l2, r1, r2, l3, r3, lx, ly, rx, ry);
}
