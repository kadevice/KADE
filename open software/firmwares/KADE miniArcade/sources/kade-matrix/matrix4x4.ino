/*
Matrix Firmware for KADE Encoder 
Made using Arduino keypad and keyboard libraries
4x4 matrix (16 key) using pins B1 to B8 (for testing with the 16 key keypad modules).

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
*/
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

//table of ascii values to represent the matrix
char keys[ROWS][COLS] = {
  {48,49,50,51},
  {52,53,54,55},
  {56,57,97,98},
  {99,100,101,102},
};

byte rowPins[ROWS] = {17,16,15,14}; 
byte colPins[COLS] = {13,12,11,10};

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
