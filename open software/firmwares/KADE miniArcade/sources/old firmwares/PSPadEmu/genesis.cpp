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
#include "genesis.h"
#include "digitalWriteFast.h"

#define DB9P1 A4
#define DB9P2 A5
#define DB9P3 0
#define DB9P4 1
#define DB9P6 2
#define DB9P7 3
#define DB9P9 4

#define DELAY 14

void genesis_init() {
	pinModeFast(DB9P1, INPUT);
	pinModeFast(DB9P2, INPUT);
	pinModeFast(DB9P3, INPUT);
	pinModeFast(DB9P4, INPUT);
	pinModeFast(DB9P6, INPUT);
	pinModeFast(DB9P7, OUTPUT);
	pinModeFast(DB9P9, INPUT);

	digitalWriteFast(DB9P1, HIGH);
	digitalWriteFast(DB9P2, HIGH);
	digitalWriteFast(DB9P3, HIGH);
	digitalWriteFast(DB9P4, HIGH);
	digitalWriteFast(DB9P6, HIGH);
	digitalWriteFast(DB9P7, HIGH);
	digitalWriteFast(DB9P9, HIGH);
}

int genesis_read() {
	int retval;

	int extrabuttons = 0;
	int normalbuttons = 0;

	// Get D-PAD, B, C buttons state
	digitalWriteFast(DB9P7, HIGH);
	delayMicroseconds(DELAY);

	normalbuttons |= (!digitalReadFast(DB9P1) << 0);
	normalbuttons |= (!digitalReadFast(DB9P2) << 1);
	normalbuttons |= (!digitalReadFast(DB9P3) << 2);
	normalbuttons |= (!digitalReadFast(DB9P4) << 3);
	normalbuttons |= (!digitalReadFast(DB9P6) << 4);
	normalbuttons |= (!digitalReadFast(DB9P9) << 5);

	digitalWriteFast(DB9P7, LOW);
	delayMicroseconds(DELAY);

	// Get A and START buttons state
	normalbuttons |= (!digitalReadFast(DB9P6) << 6);
	normalbuttons |= (!digitalReadFast(DB9P9) << 7);

	digitalWriteFast(DB9P7, HIGH);
	delayMicroseconds(DELAY);
	digitalWriteFast(DB9P7, LOW);
	delayMicroseconds(DELAY);

	// Up, Down, Left and Right are low if 6-button controller
	if(!digitalReadFast(DB9P1) && !digitalReadFast(DB9P2) && !digitalReadFast(DB9P3) && !digitalReadFast(DB9P4)) {
		digitalWriteFast(DB9P7, HIGH);
		delayMicroseconds(DELAY);

		extrabuttons |= (!digitalReadFast(DB9P1) << 0);
		extrabuttons |= (!digitalReadFast(DB9P2) << 1);
		extrabuttons |= (!digitalReadFast(DB9P3) << 2);
		extrabuttons |= (!digitalReadFast(DB9P4) << 3);

		digitalWriteFast(DB9P7, LOW);
		delayMicroseconds(DELAY);
		digitalWriteFast(DB9P7, HIGH);
		delayMicroseconds(DELAY);
		digitalWriteFast(DB9P7, LOW);

		// Delay needed for settling joystick down
		delayMicroseconds(2000);
	}

	retval = normalbuttons | (extrabuttons << 8);

	return retval;
}
