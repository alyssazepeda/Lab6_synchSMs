/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: https://youtu.be/QsOodpvzljc
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/timer.h"
#endif
#define A ~PINA&0x01
enum states{start, led1, led2, led3, press, release, reset} state;

void Tick() {
	switch(state) {
		case start: state = (A) ? press : led1; break;
		case led1: state = (A) ? press : led2; break;
		case led2: state = (A) ? press : led3; break;
		case led3: state = (A) ? press : led1; break;
		//when A0 is released we go to release, else still pressed
		case press: state = (A) ? press : release; break;
		//when A0 again we reset, else stay in release
		case release: state = (A) ? reset : release; break;
		//when in reset we wait for the button to release 
		//to restart at led1
		case reset: state = (A) ? reset : led1; break;
		default: state = start; break;
	}
	switch(state) {
		case start: break;
		case led1: PORTC = 0x01; break;
		case led2: PORTC = 0x02; break;
		case led3: PORTC = 0x04; break;
		case press:
		case release:
		case reset:
			   break;
		default: PORTC = 0x00; break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF; PORTC = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	TimerSet(300);
	TimerOn();
	state = start;
    while (1) {
	Tick();
	while(!TimerFlag) {}
	TimerFlag = 0;
    }
    return 1;
}
