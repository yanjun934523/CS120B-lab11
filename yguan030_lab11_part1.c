/*	Author: lab
 *  Partner(s) Name: Yanjun Guan
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//DEMO LINK: https://drive.google.com/file/d/1K_0K-On6mj8FLvjMcaA2AxFyIrxFj5R6/view?usp=sharing
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
enum SM1_States {start, up, down, up2, down2}state;
void SM1_Tick() {
    // === Local Variables ===
    static unsigned char column_val = 0xFF;
    static unsigned char column_sel = 0xFE;

    // === Transitions ===
    switch (state) {
        case start:
            if((~PINA & 0x03) == 0x01){
                state = up2;
            }
            else if((~PINA & 0x03) == 0x02){
                state = down2;
            }
            else{
                state = start;
            }
            break;
        case up:
            state = start;
            break;
        case down:
            state = start;
            break;
        case up2:
            if((~PINA & 0x03) == 0x00){
                state = up;
            }
            else {
                state = up2;
            }
            break;
        case down2:
            if((~PINA & 0x03) == 0x00){
                state = down;
            }
            else {
                state = down2;
            }
            break;
        default:
        break;
    }

    // === Actions ===
    switch (state) {
        case start:
            break;
        case up:
            if((PORTD & 0x01) == 0x00){
                    row = 0x1D;
                }
                else if((PORTD & 0x02) == 0x00){
                    row = 0x1B;
                }
                else if((PORTD & 0x04) == 0x00){
                    row = 0x17;
                }
                else if((PORTD & 0x08) == 0x00){
                    row = 0x0F;
                }
                else if((PORTD & 0x10) == 0x00){
                    row = 0x0F;
                }
            break;
        case down:
            if((PORTD & 0x01) == 0x00){
                row = 0x1E;
            }
            else if((PORTD & 0x02) == 0x00){
                row = 0x1E;
            }
            else if((PORTD & 0x04) == 0x00){
                row = 0x1D;
            }
            else if((PORTD & 0x08) == 0x00){
                row = 0x1B;
            }
            else if((PORTD & 0x10) == 0x00){
                row = 0x17;
            }
            break;
        case up2:
            break;
        case down2:
            break;
        default:
            break;
    }
    PORTC = column_val ;
    PORTD = column_sel ;
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
