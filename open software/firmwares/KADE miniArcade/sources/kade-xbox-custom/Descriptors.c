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
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(01.10),
	.Class                  = USB_CSCP_NoDeviceClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = 0x08,

	.VendorID               = 0x045E,
	.ProductID              = 0x0202,
	.ReleaseNumber          = VERSION_BCD(01.00),

	.ManufacturerStrIndex   = 0x00,
	.ProductStrIndex        = 0x00,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

	.NumberOfConfigurations = 0x01

};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = 0x20,
			.TotalInterfaces        = 1,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,

			.ConfigAttributes       = USB_CONFIG_ATTR_RESERVED,

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.HID_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0x00,
			.AlternateSetting       = 0x00,

			.TotalEndpoints         = 2,

			.Class                  = 0x58,
			.SubClass               = 0x42,
			.Protocol               = HID_CSCP_NonBootProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_ReportINEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = JOYSTICK_EPADDR_IN,
			.Attributes             = (EP_TYPE_INTERRUPT),
			.EndpointSize           = JOYSTICK_EPSIZE,
			.PollingIntervalMS      = 0x04
		},

	.HID_ReportOUTEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = JOYSTICK_EPADDR_OUT,
			.Attributes             = (EP_TYPE_INTERRUPT),
			.EndpointSize           = 0x08,
			.PollingIntervalMS      = 0x04
		}
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(12), .Type = DTYPE_String},

	.UnicodeString          = L"kadevice.com"
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(31), .Type = DTYPE_String},

	.UnicodeString          = L"KADE - Kick Ass Dynamic Encoder"
};

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = &LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case 0x01:
					Address = &ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case 0x02:
					Address = &ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
			}

			break;
	}

	*DescriptorAddress = Address;
	return Size;
}

