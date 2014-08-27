/*
* USB RetroPad Adapter - PC/PS3 USB adapter for retro-controllers!
* Copyright (c) 2012 Bruno Freitas - bruno@brunofreitas.com
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

/** \file
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include <avr/pgmspace.h>

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;

			// Joystick HID Interface
			USB_Descriptor_Interface_t            HID_Interface;
			USB_HID_Descriptor_HID_t              HID_JoystickHID;
	        USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
		} USB_Descriptor_Configuration_t;

	/* Macros: */
		/** Endpoint address of the Joystick HID reporting IN endpoint. */
		#define JOYSTICK_EPADDR           (ENDPOINT_DIR_IN | 1)

		/** Size in bytes of the Joystick HID reporting IN endpoint. */
		#define JOYSTICK_EPSIZE           64

		/** Descriptor header type value, to indicate a HID class HID descriptor. */
		#define DTYPE_HID                 0x21

		/** Descriptor header type value, to indicate a HID class HID report descriptor. */
		#define DTYPE_Report              0x22

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

