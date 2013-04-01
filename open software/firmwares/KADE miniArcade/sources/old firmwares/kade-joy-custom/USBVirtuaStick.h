/*
* USB RetroPad Adapter - PC/PS3 USB adapter for retro-controllers!
* Copyright (c) 2012 Bruno Freitas - bootsector@ig.com.br
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

#ifndef _USBVIRTUASTICK_H_
#define _USBVIRTUASTICK_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <string.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/USB/USB.h>


	/* Type Defines: */
		/** Type define for the joystick HID report structure, for creating and sending HID reports to the host PC.
		 *  This mirrors the layout described to the host in the HID report descriptor, in Descriptors.c.
		 */
		typedef struct
		{
			// digital buttons, 0 = off, 1 = on

			uint8_t square_btn : 1;
			uint8_t cross_btn : 1;
			uint8_t circle_btn : 1;
			uint8_t triangle_btn : 1;

			uint8_t l1_btn : 1;
			uint8_t r1_btn : 1;
			uint8_t l2_btn : 1;
			uint8_t r2_btn : 1;

			uint8_t select_btn : 1;
			uint8_t start_btn : 1;
			uint8_t l3_btn : 1;
			uint8_t r3_btn : 1;
			uint8_t ps_btn : 1;
			uint8_t : 3;

			// digital direction, use the dir_* constants(enum)
			// 8 = center, 0 = up, 1 = up/right, 2 = right, 3 = right/down
			// 4 = down, 5 = down/left, 6 = left, 7 = left/up

			uint8_t direction;

			// left and right analog sticks, 0x00 left/up, 0x80 middle, 0xff right/down

			uint8_t l_x_axis;
			uint8_t l_y_axis;
			uint8_t r_x_axis;
			uint8_t r_y_axis;

			uint8_t unknown[4];

			// button axis, 0x00 = unpressed, 0xff = fully pressed

			uint8_t triangle_axis;
			uint8_t circle_axis;
			uint8_t cross_axis;
			uint8_t square_axis;

			uint8_t l1_axis;
			uint8_t r1_axis;
			uint8_t l2_axis;
			uint8_t r2_axis;

		} USB_JoystickReport_Data_t;

		extern USB_JoystickReport_Data_t gamepad_state;

	/* Function Prototypes: */
		void vs_reset_pad_status(void);
		void vs_init(bool watchdog);
		void vs_reset_watchdog(void);
		void vs_send_pad_state(void);
		void vs_set_connect_callback(void (*callbackPtr)(void));
		void vs_set_disconnect_callback(void (*callbackPtr)(void));

#endif

