/*
Matrix Firmware for KADE Encoder 
Made using Arduino keypad and keyboard libraries
8x6 matrix (48 key)

/* Matrix key layouts (B1-B8 rows, A1-A6 columns)

         A1 A2 A3 A4 A5 A6
       +------------------- 
    B1 | 0  1  2  3  4  5
    B2 | 6  7  8  9  a  b
    B3 | c  d  e  f  g  h
    B4 | i  j  k  l  m  n
    B5 | o  p  q  r  s  t
    B6 | u  v  w  x  y  z
    B7 | -  +  [  ]  ;  '
    B8 | `  ,  .  /  #  space

Arduino Pins Mapped to the KADE pins on Minimus AVR:

               USB
             +-----+
             |     |
             |     |
          +--+     +--+
       A1 |20         | (Vcc) 
       A2 |0        19| B10
       A3 |1        18| B9
       A4 |2          | (Rst)
       A5 |3        17| B8
       A6 |4        16| B7
       A7 |5        15| B6
       A8 |6        14| B5
    (Hwb) |7        13| B4
       A9 |8        12| B3
      A10 |9        11| B2
    (Gnd) |         10| B1
          +-----------+
		  
Supports multiple key press. Using a diode with each button will prevent blocking and ghosting issues with the matrix.
Recommend Schottkey diodes but general purpose diodes like 1N4148 will work.
		  
Here's a great reference to how a keypad matrix works: http://pcbheaven.com/wikipages/How_Key_Matrices_Works/ 
*/
#include <Keypad.h>

const byte ROWS = 8;
const byte COLS = 6;

//table of ascii values to represent the matrix
char keys[ROWS][COLS] = {
  {48,49,50,51,52,53},
  {54,55,56,57,97,98},
  {99,100,101,102,103,104},
  {105,106,107,108,109,110},
  {111,112,113,114,115,116},
  {117,118,119,120,121,122},
  {45,61,91,93,59,39},
  {96,44,46,47,92,32},
};

byte rowPins[ROWS] = {10,11,12,13,14,15,16,17}; 
byte colPins[COLS] = {20,0,1,2,3,4};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Keyboard.begin();
  keypad.setDebounceTime(10);
}

void loop() {
  if (keypad.getKeys())
  {
    for (int i=0; i<LIST_MAX; i++)
    {
        switch (keypad.key[i].kstate) {
            case HOLD:
              Keyboard.press(keypad.key[i].kchar);
              break;
            case RELEASED:
              Keyboard.release(keypad.key[i].kchar);
              break;
      }
    }
  }
}
