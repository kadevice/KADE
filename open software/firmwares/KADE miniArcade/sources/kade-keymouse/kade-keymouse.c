/* 
Keyboard/Mouse Hybrid Firmware for KADE 
Adapted from the LUFA KeyboardMouseMultiReport demo by Dean Camera

Press HWB to toggle between keyboard and mouse input modes.

For keyboard:
  All pins A1-A10 and B1-B10 are mapped to letters A to T
  e.g. A1=A, A2=B, A3=C, B10=T
  
For mouse:
  A1=Mouse Up
  A2=Mouse Down
  A3=Mouse Left
  A4=Mouse Right
  A5=Left Click
  A6=Right Click
  A7=Middle Click
*/

#include "kade-keymouse.h"
#include "lufa-setup.c"

uint8_t b, c, d;
uint8_t inputmode = 0;
uint8_t b_prev=0xFF, c_prev=0xFF, d_prev=0xFF;
uint8_t keycount = 0;


int main(void)
{
	SetupHardware();
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;

	sei();

	for (;;)
	{
		HID_Device_USBTask(&Device_HID_Interface);
		USB_USBTask();
	}
}


/* HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
*/
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{

	if(inputmode==0){									
		USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;
		keycount = 0;
		if(!(PINC & 0x10)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_T; } //PIN B10
		if(!(PINC & 0x20)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_S; } //PIN B9
		if(!(PINC & 0x40)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_R; } //PIN B8
		if(!(PINC & 0x80)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_Q; } //PIN B7
		if(!(PINB & 0x80)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_P; } //PIN B6
		if(!(PINB & 0x40)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_O; } //PIN B5
		if(!(PINB & 0x20)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_N; } //PIN B4
		if(!(PINB & 0x10)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_M; } //PIN B3
		if(!(PINB & 0x08)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_L; } //PIN B2
		if(!(PINB & 0x04)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_K; } //PIN B1
		if(!(PINB & 0x02)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_J; } //PIN A10
		if(!(PINB & 0x01)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_I; } //PIN A9
		if(!(PIND & 0x40)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_H; } //PIN A8
		if(!(PIND & 0x20)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_G; } //PIN A7
		if(!(PIND & 0x10)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_F; } //PIN A6
		if(!(PIND & 0x08)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_E; } //PIN A5
		if(!(PIND & 0x04)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_D; } //PIN A4
		if(!(PIND & 0x02)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_C; } //PIN A3
		if(!(PIND & 0x01)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_B; } //PIN A2
		if(!(PINC & 0x04)) { KeyboardReport->KeyCode[keycount++] = HID_KEYBOARD_SC_A; } //PIN A1
		
		if(!(PIND & 0x80)) { // HWB PIN
			if(keycount==0) { inputmode = 1; }
			_delay_ms(500);
		} 

		*ReportID   = HID_REPORTID_KeyboardReport;
		*ReportSize = sizeof(USB_KeyboardReport_Data_t);
		_delay_ms(10); // Debounce
		return false;

	} else {
		USB_MouseReport_Data_t* MouseReport = (USB_MouseReport_Data_t*)ReportData;
		
		//mouse direction
		if(!(PIND & 0x04)) { MouseReport->X =  1; } //PIN A4
		if(!(PIND & 0x02)) { MouseReport->X = -1; } //PIN A3
		if(!(PIND & 0x01)) { MouseReport->Y =  1; } //PIN A2
		if(!(PINC & 0x04)) { MouseReport->Y = -1; } //PIN A1
		
		//mouse buttons
		if(!(PIND & 0x20)) { MouseReport->Button |= (1 << 2); } //PIN A7
		if(!(PIND & 0x10)) { MouseReport->Button |= (1 << 1); } //PIN A6
		if(!(PIND & 0x08)) { MouseReport->Button |= (1 << 0); } //PIN A5
		
		if(!(PIND & 0x80)) { // HWB PIN
			inputmode = 0;
			_delay_ms(500); 
		} 

		*ReportID   = HID_REPORTID_MouseReport;
		*ReportSize = sizeof(USB_MouseReport_Data_t);
		_delay_ms(2); // Debounce
		return true;
	}

}

/*  HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
*/
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	uint8_t  LEDMask   = LEDS_NO_LEDS;
	uint8_t* LEDReport = (uint8_t*)ReportData;

}