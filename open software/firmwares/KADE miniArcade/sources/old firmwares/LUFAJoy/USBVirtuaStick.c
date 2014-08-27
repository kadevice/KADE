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

#include "USBVirtuaStick.h"

USB_JoystickReport_Data_t gamepad_state;

static uint8_t ps3_magic_bytes[8] = { 0x21, 0x26, 0x01, 0x07, 0x00, 0x00, 0x00,	0x00 };

void (*padUSBConnectEventCallback)(void) = NULL;

void (*padUSBDisconnectEventCallback)(void) = NULL;


/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Device_Connect(void)
{
	if(padUSBConnectEventCallback)
		padUSBConnectEventCallback();
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and joystick reporting tasks.
 */
void EVENT_USB_Device_Disconnect(void)
{
	if(padUSBDisconnectEventCallback)
		padUSBDisconnectEventCallback();
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the joystick reporting task started.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	/* Setup HID Report Endpoint */
	Endpoint_ConfigureEndpoint(JOYSTICK_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
}

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	/* Handle HID Class specific requests */
	switch (USB_ControlRequest.bRequest)
	{
		case HID_REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				if(USB_ControlRequest.wValue == 0x0300) {
					Endpoint_ClearSETUP();

					Endpoint_Write_Control_Stream_LE(ps3_magic_bytes, sizeof(ps3_magic_bytes));

					Endpoint_ClearOUT();
				} else {
					Endpoint_ClearSETUP();

					/* Write the report data to the control endpoint */
					Endpoint_Write_Control_Stream_LE(&gamepad_state, sizeof(gamepad_state));
					Endpoint_ClearOUT();
				}
			}

			break;
	}
}

/** Function to manage HID report generation and transmission to the host. */
void HID_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	/* Select the Joystick Report Endpoint */
	Endpoint_SelectEndpoint(JOYSTICK_EPADDR);

	/* Check to see if the host is ready for another packet */
	if (Endpoint_IsINReady())
	{
		/* Write Joystick Report Data */
		Endpoint_Write_Stream_LE(&gamepad_state, sizeof(gamepad_state), NULL);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();
	}
}

void vs_reset_pad_status(void) {
	memset(&gamepad_state, 0x00, sizeof(USB_JoystickReport_Data_t));
	gamepad_state.direction = 0x08;
	gamepad_state.l_x_axis = 0x80;
	gamepad_state.l_y_axis = 0x80;
	gamepad_state.r_x_axis = 0x80;
	gamepad_state.r_y_axis = 0x80;
}

void vs_init(bool watchdog) {
	if (watchdog) {
		wdt_enable(WDTO_2S);
	} else {
		wdt_disable();
	}

	vs_reset_pad_status();

	USB_Init();

	sei();
}

void vs_reset_watchdog(void) {
	wdt_reset();
}

void vs_send_pad_state(void) {
	HID_Task();
	USB_USBTask();
}

void vs_set_connect_callback(void (*callbackPtr)(void)) {
	padUSBConnectEventCallback = callbackPtr;
}

void vs_set_disconnect_callback(void (*callbackPtr)(void)) {
	padUSBDisconnectEventCallback = callbackPtr;
}
