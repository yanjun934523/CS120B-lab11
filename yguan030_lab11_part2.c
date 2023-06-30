/*	Author: lab
 *  Partner(s) Name: Yanjun Guan
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//DEMO LINK: https://drive.google.com/file/d/1gBiwLyqtRLu1bqNJkr0cRgVgH1WMxJ8T/view?usp=sharing
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
enum SM1_States {start, right, left, right2, left2}state;
void SM1_Tick() {
    // === Local Variables ===
    static unsigned char column = 0x80;
    static unsigned char row = 0x00;

    // === Transitions ===
    switch (state) {
        case start:
            if((~PINA & 0x03) == 0x01){
                state = right2;
            }
            else if((~PINA & 0x03) == 0x02){
                state = left2;
            }
            else{
                state = start;
            }
            break;
        case right:
            state = start;
            break;
        case left:
            state = start;
            break;
        case right2:
            if((~PINA & 0x03) == 0x00){
                state = right;
            }
            else {
                state = right2;
            }
            break;
        case left2:
            if((~PINA & 0x03) == 0x00){
                state = left;
            }
            else {
                state = left2;
            }
            break;
        default:
            break;
    }

    // === Actions ===
    switch (state) {
        case start:
            break;
        case right:
            if((PORTC & 0xFF) == 0x01){
                column = 0x01;
            }
            else{
                column >>= 1;
            }
            break;
        case left:
            if((PORTC & 0xFF) == 0x80){
                column = 0x80;
            }
            else{
                column <<= 1;
            }
            break;
        case right2:
            break;
        case left2:
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
