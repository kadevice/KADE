/*
DEGENATRONS ARCADE ENCODER: Configurable 20 Input Keyboard Encoder 
https://sites.google.com/site/degenatrons/

In the arrays, 0-9 is A1-A10 and 10-19 is B1-B10
*/

//----------------------------------------------------------------------------
//Mode 1: Player 1 MAME Compatible
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
  map[7]  = KEY_LEFT_ALT;
  map[8]  = KEY_SPACE;
  map[9]  = KEY_LEFT_SHIFT;
  map[10] = KEY_Z;
  map[11] = KEY_X;
  map[12] = KEY_C;
  map[13] = KEY_V;
  map[14] = KEY_ENTER;
  map[15] = KEY_P;
  map[16] = KEY_F7;
  map[17] = KEY_TAB;
  map[18] = KEY_ESC;
  map[19] = KEY_NONE;
} 

//----------------------------------------------------------------------------
//Mode 2: Player 2 MAME Compatible
//----------------------------------------------------------------------------
void A2(void)
{
  map[0]  = KEY_6;
  map[1]  = KEY_2;
  map[2]  = KEY_G;
  map[3]  = KEY_D;
  map[4]  = KEY_R;
  map[5]  = KEY_F;
  map[6]  = KEY_A;
  map[7]  = KEY_S;
  map[8]  = KEY_Q;
  map[9]  = KEY_W;
  map[10] = KEY_I;
  map[11] = KEY_K;
  map[12] = KEY_J;
  map[13] = KEY_L;
  map[14] = KEY_ENTER;
  map[15] = KEY_P;
  map[16] = KEY_F7;
  map[17] = KEY_TAB;
  map[18] = KEY_ESC;
  map[19] = KEY_NONE;
} 
//----------------------------------------------------------------------------
//Mode 3: Player 3 MAME Compatible
//----------------------------------------------------------------------------
void A3(void)
{
  map[0]  = KEY_7;
  map[1]  = KEY_3;
  map[2]  = KEY_END;
  map[3]  = KEY_HOME;
  map[4]  = KEY_PAGE_UP;
  map[5]  = KEY_PAGE_DOWN;
  map[6]  = KEY_RIGHT_CTRL;
  map[7]  = KEY_RIGHT_SHIFT;
  map[8]  = KEY_ENTER;
  map[9]  = KEY_SLASH;
  map[10] = KEY_PERIOD;
  map[11] = KEY_COMMA;
  map[12] = KEY_NONE;
  map[13] = KEY_NONE;
  map[14] = KEY_ENTER;
  map[15] = KEY_P;
  map[16] = KEY_F7;
  map[17] = KEY_TAB;
  map[18] = KEY_ESC;
  map[19] = KEY_NONE;
} 


//----------------------------------------------------------------------------
//Mode 4: Player 4 MAME Compatible
//----------------------------------------------------------------------------
void A4(void)
{
  map[0]  = KEY_8;
  map[1]  = KEY_4;
  map[2]  = KEYPAD_6;
  map[3]  = KEYPAD_4;
  map[4]  = KEYPAD_8;
  map[5]  = KEYPAD_2;
  map[6]  = KEYPAD_0;
  map[7]  = KEYPAD_PERIOD;
  map[8]  = KEYPAD_ENTER;
  map[9]  = KEYPAD_PLUS;
  map[10] = KEYPAD_MINUS;
  map[11] = KEYPAD_ASTERIX;
  map[12] = KEY_NONE;
  map[13] = KEY_NONE;
  map[14] = KEY_ENTER;
  map[15] = KEY_P;
  map[16] = KEY_F7;
  map[17] = KEY_TAB;
  map[18] = KEY_ESC;
  map[19] = KEY_NONE;
} 

