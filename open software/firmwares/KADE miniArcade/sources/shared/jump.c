/*
Bootloader start function adapted from LUFA example at:    
http://www.fourwalledcubicle.com/files/LUFA/Doc/100807/html/_page__software_bootloader_start.html
*/
#include <avr/wdt.h>
#include <LUFA/Common/Common.h>
#include <LUFA/Drivers/USB/USB.h>
uint32_t Boot_Key ATTR_NO_INIT;
#define MAGIC_BOOT_KEY            0xDC42ACCA

//Bootloader location varies for MCU (Added JW 29/07/2013)
#if defined (__AVR_AT90USB162__)
#define BOOTLOADER_START_ADDRESS  0x1800
#else
#define BOOTLOADER_START_ADDRESS  0xF000
#endif

void Bootloader_Jump_Check(void) ATTR_INIT_SECTION(3);
void Bootloader_Jump_Check(void)
{
  // If the reset source was the bootloader and the key is correct, clear it and jump to the bootloader
  if ((MCUSR & (1<<WDRF)) && (Boot_Key == MAGIC_BOOT_KEY))
  {
	  Boot_Key = 0;
	  ((void (*)(void))BOOTLOADER_START_ADDRESS)(); 
  }
}

void Jump_To_Bootloader(void)
{
  // If USB is used, detach from the bus
  USB_Disable();

  // Disable all interrupts
  cli();

  // Wait two seconds for the USB detachment to register on the host
  for (uint8_t i = 0; i < 128; i++)
	_delay_ms(16);

  // Set the bootloader key to the magic value and force a reset
  Boot_Key = MAGIC_BOOT_KEY;
  wdt_enable(WDTO_250MS);
  for (;;); 
}