/*	Author: lab
 *  Partner(s) Name: Yanjun Guan
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//DEMO LINK: https://drive.google.com/file/d/1Bc-Sc43lCAHEjpdQ6nS0_6pZFqa3oJT3/view?usp=sharing
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
/*void transmit_data(unsigned char data) {
    int i;
    for (i = 0; i < 8 ; ++i) {
        // Sets SRCLR to 1 allowing data to be set
        // Also clears SRCLK in preparation of sending data
        PORTC = 0x08;
        // set SER = next bit of data to be sent.
        PORTC |= ((data >> i) & 0x01);
        // set SRCLK = 1. Rising edge shifts next bit of data into the shift register
        PORTC |= 0x02;
    }
    // set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
    PORTC |= 0x04;
    // clears all lines in preparation of a new transmission
    PORTC = 0x00;
}*/

// ====================
// SM1: DEMO LED matrix
// ====================
enum SM1_States {start, square_top, square_bottom, square_left, square_right}state;
void SM1_Tick() {
    // === Local Variables ===
    static unsigned char column = 0x80;
    static unsigned char row = 0x00;

    // === Transitions ===
    switch (state) {
        case start:
            state = square_top;
            break;
        case square_top:
            state = square_bottom;
            break;
        case square_bottom:
            state = square_left;
            break;
        case square_left:
            state = square_right;
            break;
        case square_right:
            state =start;
            break;
        default:
            break;
    }

    // === Actions ===
    switch (state) {
        case start:
            break;
        case square_top:
            column = 0x3C;
            row = 0x1E;
            break;
        case square_bottom:
            column = 0x3C;
            row = 0x17;
            break;
        case square_left:
            column = 0x20;
            row = 0x10;
            break;
        case square_right:
            column = 0x04;
            row = 0x10;
            break;

        default:
            break;
    }
    PORTC = column;
    PORTD = row;
}



int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;    PORTA = 0xFF;
    DDRC = 0xFF;	PORTC = 0x00;
    DDRD = 0xFF;	PORTD = 0x00;
    /* Insert your solution below */
    while (1) {
        SM1_Tick();
    }
    return 1;
}
