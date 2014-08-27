/* 
 * KADE - Kick Ass Dynamic Encoder
 * Copyright (c) 2012 Bruno Freitas - bruno@brunofreitas.com
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
#include "PSPadEmu.h"

void setup(void) {
	pspad_init();
}

void loop(void) {
	int button_data;
	int lx, ly;

	genesis_init();

	for (;;) {

		button_data = genesis_read();

		if(button_data & GENESIS_LEFT) {
			lx = 0x00;
		} else if(button_data & GENESIS_RIGHT) {
			lx = 0xFF;
		} else {
			lx = 0x7F;
		}

		if(button_data & GENESIS_UP) {
			ly = 0x00;
		} else if(button_data & GENESIS_DOWN) {
			ly = 0xFF;
		} else {
			ly = 0x7F;
		}

//		pspad_set_pad_state(button_data & GENESIS_LEFT, button_data & GENESIS_RIGHT,
//				button_data & GENESIS_UP, button_data & GENESIS_DOWN,
//				button_data & GENESIS_A, button_data & GENESIS_Y, button_data & GENESIS_C,
//				button_data & GENESIS_B, button_data & GENESIS_MODE,
//				button_data & GENESIS_START, button_data & GENESIS_X,
//				0, button_data & GENESIS_Z, 0, 0x7F, 0x7F, 0x7F, 0x7F);

		pspad_set_pad_state(0, 0,
				0, 0,
				button_data & GENESIS_A, button_data & GENESIS_Y, button_data & GENESIS_C,
				button_data & GENESIS_B, button_data & GENESIS_MODE,
				button_data & GENESIS_START, 0,
				button_data & GENESIS_X, 0, button_data & GENESIS_Z, 0, 0, lx, ly, 0x7F, 0x7F);
	}
}
