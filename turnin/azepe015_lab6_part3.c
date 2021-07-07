/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: https://youtu.be/CFWz2q36ats
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 */
 

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

//keep in mind that i need to add ~ to PINA to read on breadboard
//to test this w test files remove ~
#define A0 ~PINA&0x01
#define A1 ~PINA&0x02

unsigned char timePress = 0x0A; //10 -> 10*100 = 1sec
unsigned char cnt;

enum states{start, wait, inc, dec, reset} state;

void Tick() {
	switch(state) {
		case start:
			PORTC = 0X07;
			state = wait;
		       	break;
		case wait:
			if(!(A0) && !(A1)) {
				state = wait;
			}
			else if ((A0) && !(A1)) {
				cnt = timePress;
				state = inc;
			}
			else if(!(A0) && (A1)) {
				cnt = timePress;
				state = dec;
			}
			else {
				state = reset;
			}
			break;
		case inc:
			if(!(A0) && !(A1)) {
                                state = wait;
                        }
                        else if ((A0) && !(A1)) {
                                state = inc;
                        }
                        else if(!(A0) && (A1)) {
                                state = dec;
                        }
                        else {
                                state = reset;
                        }
                        break;
		case dec:
			if(!(A0) && !(A1)) {
                                state = wait;
                        }
                        else if ((A0) && !(A1)) {
                                state = inc;
                        }
                        else if(!(A0) && (A1)) {
                             	state = dec;
                        }
                        else {
                                state = reset;
                        }
                        break;
		case reset:
			if((A0) || (A1)) {
				state = reset;
			}
			else {
				state = wait;
			}
			break;

		default: state = start; break;
	}
	switch(state) {
		case start:

			break;
		case wait:
			cnt = 0;
			break;
		case inc:
			if(cnt < timePress && PORTC < 9) {
				cnt ++;
			}
			else if(cnt >= timePress && PORTC < 9) {
				cnt = 0;
				PORTC++;
			}
			break;
		case dec:
			if(cnt < timePress && PORTC > 0) {
				cnt++;
			}
			else if(cnt >= timePress && PORTC > 0) {
				cnt = 0;
				PORTC--;
			}
			break;
		case reset:
			PORTC = 0;
			break;

		default: PORTB = 0x00; break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0XFF;
	DDRC = 0XFF; PORTC = 0X00;
    /* Insert your solution below */

	TimerSet(100);
	TimerOn();

	state = start;

    while (1) {
	Tick();
	while(!TimerFlag) {}
	TimerFlag = 0;
    }
    return 1;
}
