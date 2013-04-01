#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */
#include "pstwo.h"

//====================================================================
extern uint8_t ps2data[3];
extern uint8_t ps2_i;
extern int8_t ps2_x, ps2_y;

//extern uint8_t Bps2data[3];
//extern uint8_t Bps2_i;
//extern int8_t Bps2_x, Bps2_y;
//====================================================================
extern void initTrackBall(int resolution, int rate);
//extern void initTrackBallB(int resolution, int rate);
//====================================================================
