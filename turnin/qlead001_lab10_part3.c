/*	Author: Quinn Leader qlead001@ucr.edu
 *  Partner(s) Name: NA
 *	Lab Section: 026
 *	Assignment: Lab 10  Exercise 3
 *	Exercise Description: Lab 10 Exercise 2 but with speaker
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SP_States {
    SP_Start,
    SP_On,
    SP_Off,
} SP_state;

unsigned char speaker;

void SP_Tick() {
    switch (SP_state) {
        case SP_Start:
            SP_state = SP_Off;
            break;
        case SP_Off:
            if ((~PINA)&0x04) SP_state = SP_On;
            break;
        case SP_On:
            SP_state = SP_Off;
            break;
    }
    switch (SP_state) {
        case SP_Off:
            speaker = 0;
            break;
        case SP_On:
            speaker = 1<<4;
            break;
        default:
            speaker = 0;
            break;
    }
}

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
    PORTB = (threeLEDs + blinkingLED + speaker);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    unsigned short TL_elapsedTime = 0;
    unsigned short BL_elapsedTime = 0;
    unsigned short SP_elapsedTime = 0;
    unsigned short OUT_elapsedTime = 0;
    const unsigned short timerPeriod = 1;

    TimerSet(timerPeriod);
    TimerOn();
    TL_state = TL_Start;
    BL_state = BL_Start;
    while (1) {
        if (TL_elapsedTime >= 300) {
            TL_Tick();
            TL_elapsedTime = 0;
        }
        if (BL_elapsedTime >= 1000) {
            BL_Tick();
            BL_elapsedTime = 0;
        }
        if (SP_elapsedTime >= 2) {
            SP_Tick();
            SP_elapsedTime = 0;
        }
        if (OUT_elapsedTime >= 1) {
            OUT_Tick();
            OUT_elapsedTime = 0;
        }

        while (!TimerFlag);
        TimerFlag = 0;

        TL_elapsedTime += timerPeriod;
        BL_elapsedTime += timerPeriod;
        SP_elapsedTime += timerPeriod;
        OUT_elapsedTime += timerPeriod;
    }
    return 1;
}
