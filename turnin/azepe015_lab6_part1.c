/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: https://youtu.be/274KMP-gdkw
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/timer.h"
#endif

enum states{start, led1, led2, led3} state;

void Tick() {
	switch(state) {
		case start: state = led1; break;
		case led1: state = led2; break;
		case led2: state = led3; break;
		case led3: state = led1; break;
		default: state = start; break;
	}
	switch(state) {
		case start: break;
		case led1: PORTC = 0x01; break;
		case led2: PORTC = 0x02; break;
		case led3: PORTC = 0x04; break;
		default: PORTC = 0x00; break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	TimerSet(1000);
	TimerOn();
	state = start;
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
