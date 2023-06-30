/*	Author: lab
 *  Partner(s) Name: Yanjun Guan
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//DEMO LINK: https://drive.google.com/file/d/1d9vbbPdQ5icNqrhnjQ8kAH4d70NCCWjm/view?usp=sharing
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
unsigned char column[4] = {0x04,0x20,0x3C,0x3C};
unsigned char row[4] = {0x10,0x10,0x1E,0x17};
unsigned char i = 0;
// ====================
// SM1: DEMO LED matrix
// ====================
enum SM1_States {start, square_right, square_left, square_top, square_bottom}state;
void SM1_Tick() {
    // === Local Variables ===
    static unsigned char temp_column = 0x80;
    static unsigned char temp_row = 0x00;

    // === Transitions ===
    switch (state) {
        case start:
            state = square_right;
            break;
        case square_right:
            state = square_left;
            break;
        case square_left:
            state = square_top;
            break;
        case square_top:
            state = square_bottom;
            break;
        case square_bottom:
            state = start;
            break;
        default:
            break;
    }

    // === Actions ===
    switch (state) {
        case start:
            break;
        case square_right:
            temp_column = column[0];
            temp_row = row[0];
            break;
        case square_left:
            temp_column = column[1];
            temp_row = row[1];
            break;
        case square_top:
            temp_column = column[2];
            temp_row = row[2];
            break;
        case square_bottom:
            temp_column = column[3];
            temp_row = row[3];
            break;
        default:
            break;
    }
    PORTC = temp_column;
    PORTD = temp_row;
}

enum SM2_States {start2, up, up2, down, down2, left, left2, right, right2} SM2_state;
void SM2_Tick(){
    switch(SM2_state){
        case start2:
            if((~PINA & 0x0F) == 0x01){
                SM2_state = up2;
            }
            else if((~PINA & 0x0F) == 0x02){
                SM2_state = down2;
            }
            else if((~PINA & 0x0F) == 0x04){
                SM2_state = left2;
            }
            else if((~PINA & 0x0F) == 0x08){
                SM2_state = right2;
            }
            else{
                SM2_state = start2;
            }
            break;
        case up:
            SM2_state = start2;
            break;
        case up2:
            if((~PINA & 0x0F) == 0x00){
                SM2_state = up;
            }
            else {
                SM2_state = up2;
            }
            break;
        case down:
            SM2_state = start2;
            break;
        case down2:
            if((~PINA & 0x0F) == 0x00){
                SM2_state = down;
            }
            else {
                SM2_state = down2;
            }
            break;
        case left:
            SM2_state = start2;
            break;
        case left2:
            if((~PINA & 0x0F) == 0x00){
                SM2_state = left;
            }
            else {
                SM2_state = left2;
            }
            break;
        case right:
            SM2_state = start2;
            break;
        case right2:
            if((~PINA & 0x0F) == 0x00){
                SM2_state = right;
            }
            else {
                SM2_state = right2;
            }
            break;
        default:
            break;
    }
    switch(SM2_state){
        case start2:
            break;
        case up:
            if((row[2] & 0x01) != 0x00){
                for(i = 0; i < 4; i++){
                    row[i] = ~(~row[i] >> 1);
                }
            }
            break;
        case up2:
            break;
        case down:
            if((row[3] & 0x10) != 0x00){
                for(i = 0; i < 4; i++){
                    row[i] = ~(~row[i] << 1);
                }
            }
            break;
        case down2:
            break;
        case right:
            if(column[0] != 0x01){
                for(i = 0; i < 4; i++){
                    column[i] = column[i] >> 1;
                }
            }
            break;
        case right2:
            break;
        case left:
            if(column[1] != 0x80){
                for(i = 0; i < 4; i++){
                    column[i] = column[i] << 1;
                }
            }
            break;
        case left2:
            break;
        default:
        break;
    }
}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;    PORTA = 0xFF;
    DDRC = 0xFF;	PORTC = 0x00;
    DDRD = 0xFF;	PORTD = 0x00;
    /* Insert your solution below */
    while (1) {
        SM2_Tick();
        SM1_Tick();
    }
    return 1;
}
