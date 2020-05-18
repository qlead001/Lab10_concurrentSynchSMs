/*	Author: Quinn Leader qlead001@ucr.edu
 *  Partner(s) Name: NA
 *	Lab Section: 026
 *	Assignment: Lab 10  Exercise 1
 *	Exercise Description: Cycle through 3 LEDs and blink 1 LED
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum TL_States {
    TL_Start,
    TL_One,
    TL_Two,
    TL_Three,
} TL_state;

unsigned char threeLEDs;

void TL_Tick() {
    switch (TL_state) {
        case TL_Start:
            TL_state = TL_One;
            break;
        case TL_One:
            TL_state = TL_Two;
            break;
        case TL_Two:
            TL_state = TL_Three;
            break;
        case TL_Three:
            TL_state = TL_One;
            break;
    }
    switch (TL_state) {
        case TL_One:
            threeLEDs = 1;
            break;
        case TL_Two:
            threeLEDs = 2;
            break;
        case TL_Three:
            threeLEDs = 4;
            break;
        default:
            threeLEDs = 0;
            break;
    }
}

enum BL_States {
    BL_Start,
    BL_On,
    BL_Off,
} BL_state;

unsigned char blinkingLED;

void BL_Tick() {
    switch (BL_state) {
        case BL_Start:
            BL_state = BL_On;
            break;
        case BL_On:
            BL_state = BL_Off;
            break;
        case BL_Off:
            BL_state = BL_On;
            break;
    }
    switch (BL_state) {
        case BL_On:
            blinkingLED = 1<<3;
            break;
        case BL_Off:
            blinkingLED = 0;
            break;
        default:
            blinkingLED = 0;
            break;
    }
}

void OUT_Tick() {
    PORTB = (threeLEDs + blinkingLED);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    unsigned short TL_elapsedTime = 0;
    unsigned short BL_elapsedTime = 0;
    unsigned short OUT_elapsedTime = 0;
    const unsigned short timerPeriod = 1000;

    TimerSet(timerPeriod);
    TimerOn();
    TL_state = TL_Start;
    BL_state = BL_Start;
    while (1) {
        if (TL_elapsedTime >= 1000) {
            TL_Tick();
            TL_elapsedTime = 0;
        }
        if (BL_elapsedTime >= 1000) {
            BL_Tick();
            BL_elapsedTime = 0;
        }
        if (OUT_elapsedTime >= 1000) {
            OUT_Tick();
            OUT_elapsedTime = 0;
        }

        while (!TimerFlag);
        TimerFlag = 0;

        TL_elapsedTime += timerPeriod;
        BL_elapsedTime += timerPeriod;
        OUT_elapsedTime += timerPeriod;
    }
    return 1;
}
