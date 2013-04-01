/*
DEGENATRONS ARCADE ENCODER: Configurable 20 Input Keyboard Encoder 
https://sites.google.com/site/degenatrons/

In the arrays, 0-9 is A1-A10 and 10-19 is B1-B10

Additional mappings can be added here.  I think Pinball needs some more!

*/

//----------------------------------------------------------------------------
//Group A, Mode 1: Player 1 Pinball
//----------------------------------------------------------------------------
void A1(void)
{
  map[0]  = KEY_5;
  map[1]  = KEY_1;
  map[2]  = KEY_RIGHT;
  map[3]  = KEY_LEFT;
  map[4]  = KEY_UP;
  map[5]  = KEY_DOWN;
  map[6]  = KEY_LEFT_CTRL;
  map[7]  = KEY_RIGHT_CTRL;
  map[8]  = KEY_SPACE;  
  map[9]  = KEY_LEFT_SHIFT;  
  map[10] = KEY_Z;
  map[11] = KEY_RIGHT_SHIFT;
  map[12] = KEY_SLASH;
  map[13] = KEY_Q;
  map[14] = KEY_ENTER;
  map[15] = KEY_PAUSE;
  map[16] = KEY_A;
  map[17] = KEY_QUOTE;
  map[18] = KEY_TAB;
  map[19] = KEY_ESC;
} 
