/*
DEGENATRONS ARCADE ENCODER: 20 Input Keyboard Encoder 
by Degenatrons
https://sites.google.com/site/degenatrons/

Routines for switching mapping mode and storing eeprom
*/

#include "sound.c"

//Set the active key mapping mode
void set_active_group(void){
  switch (ee_group) {
    case(0x01):	break;
    case(0x02):	break;
	case(0x03):	break;
	case(0x04):	break;
	case(0x05):	break;
	case(0x06):	break;
	case(0x07):	break;
	default: ee_group = 0x01; break;
  } 
}

//Set the active key mapping mode
void set_active_mode(void){
  if (ee_group == 0x01) {
    switch (ee_byte) {
      case(0x01): A1(); break;
      case(0x02): A2(); break;
	  case(0x03): A3(); break;
	  case(0x04): A4(); break;
	  case(0x05): A5(); break;
	  case(0x06): A6(); break;
	  case(0x07): A7(); break;
	  default: A1(); break;
	}
  } 
  if (ee_group == 0x02) {
    switch (ee_byte) {
      case(0x01): B1(); break;
      case(0x02): B2(); break;
	  default: B1(); break;
	}
  } 
  if (ee_group == 0x03) {
    switch (ee_byte) {
      case(0x01): C1(); break;
      case(0x02): C2(); break;
	  default: C1(); break;
	}
  }
  if (ee_group == 0x04) {
    switch (ee_byte) {
      case(0x01): D1(); break;
      case(0x02): D2(); break;
	  default: D1(); break;
	}	
  } 
  if (ee_group == 0x05) {
    switch (ee_byte) {
      case(0x01): E1(); break;
      case(0x02): E2(); break;
      case(0x03): E3(); break;
	  default: E1(); break;
	}
  } 
  if (ee_group == 0x06) {
    switch (ee_byte) {
      case(0x01): F1(); break;
      case(0x02): F2(); break;
	  case(0x03): F3(); break;
	  case(0x04): F4(); break;
	  case(0x05): F5(); break;
	  case(0x06): F6(); break;
	  case(0x07): F7(); break;
	  default: F1(); break;
	}
  } 
  if (ee_group == 0x07) {
    switch (ee_byte) {
      case(0x01): G1(); break;
	  default: G1(); break;
	}
  } 

}


//(added v1.4) Toggle the active group
void switch_group(void){  
  switch (ee_group)
  {
    case(0x01):	ee_group = 0x02; break;
    case(0x02):	ee_group = 0x03; break;
    case(0x03):	ee_group = 0x04; break;
    case(0x04):	ee_group = 0x05; break;
    case(0x05):	ee_group = 0x06; break;
    case(0x06):	ee_group = 0x07; break;
    case(0x07):	ee_group = 0x01; break;
    default: 	ee_group = 0x01; break;
  }
  write_eeprom_byte(2,ee_group);
  
  //Force mode to toggle back to 1.
  ee_byte=0x99;
  switch_mode();

  _delay_ms(10);  //prevent multiple presses
}


//Toggle the active mode
void switch_mode(void){

  //toggle mode
  switch (ee_byte)
  {
    case(0x01):	ee_byte = 0x02; break;
    case(0x02):	ee_byte = 0x03; break;
    case(0x03):	ee_byte = 0x04; break;
    case(0x04):	ee_byte = 0x05; break; //(added v1.3)
    case(0x05):	ee_byte = 0x06; break;
    case(0x06):	ee_byte = 0x07; break;
    case(0x07):	ee_byte = 0x01; break;
    default: 	ee_byte = 0x01; break;
  }
  //Some groups have less than 7 modes...
  //group B has 2 modes.
  if ((ee_group == 0x02) && (ee_byte == 0x03)) {
    ee_byte = 0x01;
  }
  //group C has 2 modes.
  if ((ee_group == 0x03) && (ee_byte == 0x03)) {
    ee_byte = 0x01;
  }
  //group D has 2 modes.
  if ((ee_group == 0x04) && (ee_byte == 0x03)) {
    ee_byte = 0x01;
  }
  //group E has 3 modes.
  if ((ee_group == 0x05) && (ee_byte == 0x04)) {
    ee_byte = 0x01;
  }
  //group G has 1 mode.
  if ((ee_group == 0x07) && (ee_byte == 0x02)) {
    ee_byte = 0x01;
  }
  
  write_eeprom_byte(1,ee_byte);
  set_active_mode();
    
  flash_leds();
  
  _delay_ms(10);  //prevent multiple presses
}

//(added v1.4) Flash LEDs and external LEDs
void flash_leds(void){
  switch (ee_group)
  {
    case(0x01):	g_flashes = 1; break;
    case(0x02):	g_flashes = 2; break;
    case(0x03):	g_flashes = 3; break;
    case(0x04):	g_flashes = 4; break;
    case(0x05):	g_flashes = 5; break;
    case(0x06):	g_flashes = 6; break;
    case(0x07):	g_flashes = 7; break;
    default:    g_flashes = 1; break;
  }
  
  switch (ee_byte)
  {
    case(0x01):	flashes = 1; break;
    case(0x02):	flashes = 2; break;
    case(0x03):	flashes = 3; break;
    case(0x04):	flashes = 4; break;
    case(0x05):	flashes = 5; break;
    case(0x06):	flashes = 6; break;
    case(0x07):	flashes = 7; break;
    default: 	flashes = 1; break;
  }
  

  uint8_t flash_cnt = 0; //i don't dig counting in hex)
  
  //Flash LEDs x times to indicate group
  DDRD = (1<<LED_B);
  flash_cnt = 0;
  while(flash_cnt < g_flashes) {
    PORTD = (1<<LED_B);
    _delay_ms(160);
    PORTD = (0<<LED_B);
    _delay_ms(160);
		
	flash_cnt++;
  }
  
  //Flash LEDs x times to indicate mode
  DDRD = (1<<LED_A);
  //if (ee_group == 0x05) { DDRB = (1<<2); }    //**external LED**  
  
  flash_cnt = 0;
  while(flash_cnt < flashes) {
    PORTD = (1<<LED_A);	
	//if (ee_group == 0x05) { PORTB = (1<<2); } //**external LED**
    _delay_ms(160);
    PORTD = (0<<LED_A);
    //if (ee_group == 0x05) { PORTB = (0<<2); } //**external LED**
    _delay_ms(160);
	
    if (ee_group == 0x06) { play_sound(); }    //**external sound**  

	flash_cnt++;
  }
  
  //if (ee_group == 0x07) { demo_sound(); }      //***Demo Sound Output ***

	
  //Reset LEDs
  DDRD = 0x00;
  PORTD = 0xFF;  
  DDRC = 0x00;  //(added v1.5)
  PORTC = 0xFF; //(added v1.5)
  DDRB = 0x00;
  PORTB = 0xFF;
}


//(added v1.4) Flash LEDs and external LEDs
void play_sound(void){
  TCCR0B |= _BV(CS00);
  TIMSK0 |= _BV(TOIE0);
  //DDRB = _BV(PB2); //(Removed v1.5)
  DDRC = _BV(PC4);  //(Added v1.5)
  TCNT0 = 0;
  intrs = 0;
  curNote = REST;
  sei();
  play(A_4, 1);
  
  //DDRB = 0x00; //(Removed v1.5)
  DDRC = 0x00; //(Added v1.5)
  PORTC = 0xFF; //(added v1.5)  
}