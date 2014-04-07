/*
DEGENATRONS ARCADE ENCODER: Configurable 20 Input Keyboard Encoder 
https://sites.google.com/site/degenatrons/

In the arrays, 0-9 is A1-A10 and 10-19 is B1-B10
*/

//----------------------------------------------------------------------------
//Mode 1: Players 1 and 2 MAME Compatible
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
  map[9]  = KEY_ENTER;
  map[10]  = KEY_6;
  map[11] = KEY_2;
  map[12] = KEY_G;
  map[13] = KEY_D;
  map[14] = KEY_R;
  map[15] = KEY_F;
  map[16] = KEY_A;
  map[17] = KEY_S;
  map[18] = KEY_Q;
  map[19] = KEY_ESC;
} 


//----------------------------------------------------------------------------
//Mode 2: Players 3 and 4 MAME Compatible
//----------------------------------------------------------------------------
void A2(void)
{
  map[0]  = KEY_7;
  map[1]  = KEY_3;
//remap default keys to avoid conflict between P2 and P3
//  map[2]  = KEY_L;
//  map[3]  = KEY_J;
//  map[4]  = KEY_I;
//  map[5]  = KEY_K;
  map[2]  = KEY_END;        //right
  map[3]  = KEY_HOME;       //left
  map[4]  = KEY_PAGE_UP;    //up
  map[5]  = KEY_PAGE_DOWN;  //down
//
  map[6]  = KEY_RIGHT_CTRL;
  map[7]  = KEY_RIGHT_SHIFT;
  map[8]  = KEY_ENTER;
  map[9]  = KEY_P;
  map[10] = KEY_8;
  map[11] = KEY_4;
  map[12] = KEYPAD_6;
  map[13] = KEYPAD_4;
  map[14] = KEYPAD_8;
  map[15] = KEYPAD_2;
  map[16] = KEYPAD_0;
  map[17] = KEYPAD_PERIOD;
  map[18] = KEYPAD_ENTER;
  map[19] = KEY_ESC;
} 

