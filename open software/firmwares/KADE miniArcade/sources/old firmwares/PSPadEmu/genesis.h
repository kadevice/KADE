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
 
#ifndef GENESIS_H_
#define GENESIS_H_

void genesis_init();
int genesis_read();

#define GENESIS_UP 0x01
#define GENESIS_DOWN 0x02
#define GENESIS_LEFT 0x04
#define GENESIS_RIGHT 0x08
#define GENESIS_A 0x40
#define GENESIS_B 0x10
#define GENESIS_C 0x20
#define GENESIS_X 0x400
#define GENESIS_Y 0x200
#define GENESIS_Z 0x100
#define GENESIS_START 0x80
#define GENESIS_MODE 0x800

#endif /* GENESIS_H_ */
