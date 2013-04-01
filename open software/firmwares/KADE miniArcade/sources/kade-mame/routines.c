/*afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2afrdg2
DEGENATRONS ARCADE ENCODER: 20 Input Keyboard Encoder 
by Degenatrons
https://sites.google.com/site/degenatrons/

Routines for switching mapping mode and storing eeprom
*/


//Set the active key mapping mode
void set_active_mode(void){
  switch (ee_byte) {
    case(0x01): A1(); break;
    case(0x02): A2(); break;
	case(0x03): A3(); break;
	case(0x04): A4(); break;
	default: A1(); break;
  } 
}


//Toggle the active mode
void switch_mode(void){

  //toggle mode
  switch (ee_byte)
  {
    case(0x01):	ee_byte = 0x02; break;
    case(0x02):	ee_byte = 0x03; break;
    case(0x03):	ee_byte = 0x04; break;
    case(0x04):	ee_byte = 0x01; break;
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
    case(0x02):	flashes = 2; break;
    case(0x03):	flashes = 3; break;
    case(0x04):	flashes = 4; break;
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