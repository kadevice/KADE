/*
DEGENATRONS ARCADE ENCODER: Configurable 20 Input Keyboard Encoder 
https://sites.google.com/site/degenatrons/

In the arrays, 0-9 is A1-A10 and 10-19 is B1-B10
*/

//----------------------------------------------------------------------------
//Group A, Mode 1: Player 1 MAME Compatible
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
  map[17] = KEY_TILDE;
  map[18] = KEY_TAB;
  map[19] = KEY_ESC;
} 

//----------------------------------------------------------------------------
//Group A, Mode 2: Player 2 MAME Compatible
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
  map[17] = KEY_TILDE;
  map[18] = KEY_TAB;
  map[19] = KEY_ESC;
} 
//----------------------------------------------------------------------------
//Group A, Mode 3: Players 1 and 2 MAME Compatible
//----------------------------------------------------------------------------
void A3(void)
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
//Group A, Mode 4: Players 3 and 4 MAME Compatible
//----------------------------------------------------------------------------
void A4(void)
{
  map[0]  = KEY_7;
  map[1]  = KEY_3;
  map[2]  = KEY_L;
  map[3]  = KEY_J;
  map[4]  = KEY_I;
  map[5]  = KEY_K;
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

//----------------------------------------------------------------------------
//Group A, Mode 5: Player 1 Pinball
//----------------------------------------------------------------------------
void A5(void)
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

//----------------------------------------------------------------------------
//Group A, Mode 6: Generic Alphabetic
//----------------------------------------------------------------------------
void A6(void)
{
  map[0]  = KEY_A;
  map[1]  = KEY_B;
  map[2]  = KEY_C;
  map[3]  = KEY_D;
  map[4]  = KEY_E;
  map[5]  = KEY_F;
  map[6]  = KEY_G;
  map[7]  = KEY_H;
  map[8]  = KEY_I;
  map[9]  = KEY_J;
  map[10] = KEY_K;
  map[11] = KEY_L;
  map[12] = KEY_M;
  map[13] = KEY_N;
  map[14] = KEY_O;
  map[15] = KEY_P;
  map[16] = KEY_Q;
  map[17] = KEY_R;
  map[18] = KEY_S;
  map[19] = KEY_ESC;
} 


//----------------------------------------------------------------------------
//Group A, Mode 7: Generic Hexadecimal
//----------------------------------------------------------------------------
void A7(void)
{
  //KEY MAPPINGS
  map[0]  = KEY_0;
  map[1]  = KEY_1;
  map[2]  = KEY_2;
  map[3]  = KEY_3;
  map[4]  = KEY_4;
  map[5]  = KEY_5;
  map[6]  = KEY_6;
  map[7]  = KEY_7;
  map[8]  = KEY_8;
  map[9]  = KEY_9;
  map[10] = KEY_A;
  map[11] = KEY_B;
  map[12] = KEY_C;
  map[13] = KEY_D;
  map[14] = KEY_E;
  map[15] = KEY_F;
  map[16] = KEY_SPACE;
  map[17] = KEY_ENTER;
  map[18] = KEY_TAB;
  map[19] = KEY_ESC;
} 


//----------------------------------------------------------------------------
//Group B, Mode 1: Extended Players 1 and 2 MAME
//----------------------------------------------------------------------------
void B1(void)
{
  map[0]  = KEY_RIGHT;
  map[1]  = KEY_LEFT;
  map[2]  = KEY_UP;
  map[3]  = KEY_DOWN;
  map[4]  = KEY_LEFT_CTRL;
  map[5]  = KEY_LEFT_ALT;
  map[6]  = KEY_SPACE;
  map[7]  = KEY_LEFT_SHIFT;
  map[8]  = KEY_Z;
  map[9]  = KEY_ENTER;
  map[10] = KEY_G;
  map[11] = KEY_D;
  map[12] = KEY_R;
  map[13] = KEY_F;
  map[14] = KEY_A;
  map[15] = KEY_S;
  map[16] = KEY_Q;
  map[17] = KEY_W;
  map[18] = KEY_C;
  map[19] = KEY_V;
} 

//----------------------------------------------------------------------------
//Group B, Mode 2: Extended Players 3 and 4 MAME
//----------------------------------------------------------------------------
void B2(void)
{
  map[0]  = KEY_RIGHT;
  map[1]  = KEY_LEFT;
  map[2]  = KEY_UP;
  map[3]  = KEY_DOWN;
  map[4]  = KEY_LEFT_CTRL;
  map[5]  = KEY_LEFT_ALT;
  map[6]  = KEY_SPACE;
  map[7]  = KEY_LEFT_SHIFT;
  map[8]  = KEY_Z;
  map[9]  = KEY_ENTER;
  map[10] = KEY_G;
  map[11] = KEY_D;
  map[12] = KEY_R;
  map[13] = KEY_F;
  map[14] = KEY_A;
  map[15] = KEY_S;
  map[16] = KEY_Q;
  map[17] = KEY_W;
  map[18] = KEY_C;
  map[19] = KEY_V;
} 

//----------------------------------------------------------------------------
//Group C, Mode 1: Player 1 MAME Compatible
//----------------------------------------------------------------------------
void C1(void)
{
  A1();
} 

//----------------------------------------------------------------------------
//Group C, Mode 2: Player 1 Pinball
//----------------------------------------------------------------------------
void C2(void)
{
  A5();
} 

//----------------------------------------------------------------------------
//Group D, Mode 1: Hotswap MAME and Pinball
//----------------------------------------------------------------------------
void D1(void)
{
  map[0]  = KEY_RIGHT;
  map[1]  = KEY_LEFT;
  map[2]  = KEY_UP;
  map[3]  = KEY_DOWN;
  map[4]  = KEY_LEFT_CTRL;
  map[5]  = KEY_LEFT_ALT;
  map[6]  = KEY_SPACE;
  map[7]  = KEY_LEFT_SHIFT;
  map[8]  = KEY_Z;
  map[9]  = KEY_ENTER;
  map[10] = KEY_G;
  map[11] = KEY_D;
  map[12] = KEY_R;
  map[13] = KEY_F;
  map[14] = KEY_A;
  map[15] = KEY_S;
  map[16] = KEY_Q;
  map[17] = KEY_W;
  map[18] = KEY_C;
  map[19] = KEY_V;
} 

//----------------------------------------------------------------------------
//Group D, Mode 2: Hotswap MAME and Pinball
//----------------------------------------------------------------------------
void D2(void)
{
  map[0]  = KEY_RIGHT;
  map[1]  = KEY_LEFT;
  map[2]  = KEY_UP;
  map[3]  = KEY_DOWN;
  map[4]  = KEY_LEFT_CTRL;
  map[5]  = KEY_RIGHT_CTRL;
  map[6]  = KEY_SPACE;
  map[7]  = KEY_LEFT_SHIFT;
  map[8]  = KEY_Z;
  map[9]  = KEY_ENTER;
  map[10] = KEY_SLASH;
  map[11] = KEY_RIGHT_SHIFT;
  map[12] = KEY_ESC;
  map[13] = KEY_QUOTE;
  map[14] = KEY_A;
  map[15] = KEY_TAB;
  map[16] = KEY_Q;
  map[17] = KEY_5;
  map[18] = KEY_1;
  map[19] = KEY_PAUSE;
} 


//----------------------------------------------------------------------------
//Group E, Mode 1: Player 1 MAME Compatible
//----------------------------------------------------------------------------
void E1(void)
{
  A1();
} 

//----------------------------------------------------------------------------
//Group E, Mode 2: Generic Alphabetic
//----------------------------------------------------------------------------
void E2(void)
{
  A6();
} 


//----------------------------------------------------------------------------
//Group E, Mode 3: Generic Hexadecimal
//----------------------------------------------------------------------------
void E3(void)
{
  A7();
} 


//----------------------------------------------------------------------------
//Group F - Sound modes as per GROUP A
//----------------------------------------------------------------------------
void F1(void) { A1(); map[19] = KEY_NONE;} 
void F2(void) { A2(); map[19] = KEY_NONE;} 
void F3(void) { A3(); map[19] = KEY_NONE;} 
void F4(void) { A4(); map[19] = KEY_NONE;} 
void F5(void) { A5(); map[19] = KEY_NONE;} 
void F6(void) { A6(); map[19] = KEY_NONE;} 
void F7(void) { A7(); map[19] = KEY_NONE;} 

//----------------------------------------------------------------------------
//Group G - Placeholder for custom mapping
//----------------------------------------------------------------------------
void G1(void) {
  map[0]  = KEY_NONE;
  map[1]  = KEY_NONE;
  map[2]  = KEY_NONE;
  map[3]  = KEY_NONE;
  map[4]  = KEY_NONE;
  map[5]  = KEY_NONE;
  map[6]  = KEY_NONE;
  map[7]  = KEY_NONE;
  map[8]  = KEY_NONE;
  map[9]  = KEY_NONE;
  map[10] = KEY_NONE;
  map[11] = KEY_NONE;
  map[12] = KEY_NONE;
  map[13] = KEY_NONE;
  map[14] = KEY_NONE;
  map[15] = KEY_NONE;
  map[16] = KEY_NONE;
  map[17] = KEY_NONE;
  map[18] = KEY_NONE;
  map[19] = KEY_NONE;
}
