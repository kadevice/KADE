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
 
#ifndef PS2PADEMU_H_
#define PS2PADEMU_H_

void ps2pad_init(void);
void ps2pad_set_pad_state(int left, int right, int up, int down, int square, int triangle, int circle, int cross, int select, int start, int l1, int l2, int r1, int r2, int lx, int ly, int rx, int ry);

#endif /* PS2PADEMU_H_ */
