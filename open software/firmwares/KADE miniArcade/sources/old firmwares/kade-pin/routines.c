/*
DEGENATRONS ARCADE ENCODER: 20 Input Keyboard Encoder 
by Degenatrons
https://sites.google.com/site/degenatrons/

Routines for switching mapping mode and storing eeprom
Toggle is not used because there is just one mapping but code has
been retained for potential future mappings.
*/


//Set the active key mapping mode
void set_active_mode(void){
  switch (ee_byte) {
    case(0x01): A1(); break;
	default: A1(); break;
  } 
}


//Toggle the active mode
void switch_mode(void){

  //toggle mode
  switch (ee_byte)
  {
    case(0x01):	ee_byte = 0x01; break;
    default: 	ee_byte = 0x01; break;
  }
  
  write_eeprom_byte(1,ee_byte);
  set_active_mode();    
  flash_leds();
  
  _delay_ms(10);  //prevent multiple presses
}


//flash leds
void flash_leds(void){  
  switch (ee_byte)
  {
    case(0x01):	flashes = 1; break;
    default: 	flashes = 1; break;
  }
      
  //Flash LEDs x times to indicate mode
  DDRD = (1<<LED_B);
  
  uint8_t flash_cnt = 0;
  while(flash_cnt < flashes) {
    PORTD = (1<<LED_B);	
    _delay_ms(160);
    PORTD = (0<<LED_B);
    _delay_ms(160);
	
	flash_cnt++;
  }
	
  //Reset LEDs
  DDRD = 0x60; // D5,D6 - OUTPUT (LED)
  PORTD = 0xFF;  

}