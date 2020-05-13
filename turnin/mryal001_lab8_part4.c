/*	Author: Mayur Ryali
 *  Partner(s) Name:
 *	Lab Section: 21
 *	Assignment: Lab #8 Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "io.h"
#endif

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

    ADC_init();
    unsigned short max = 816; //max value
    unsigned short min; //min value
    unsigned char oneInterval = (max - min)/8;
    unsigned char tempB;
    while (1) {
        unsigned short threshold = ADC; //Value of ADC register is now stored in variable

        if (threshold <= min + oneInterval ) { //level 0 brightness
            tempB = 0x00;
        }
        else if (threshold <= min + (oneInterval * 2)) { //level 1 brightness
            tempB = 0x01;
        }
        else if (threshold <= min + (oneInterval * 3)) { //level 2 brightness
            tempB = 0x02;
        }
        else if (threshold <= min + (oneInterval * 4)) { //level 3 brightness
            tempB = 0x03;
        }
        else if (threshold <= min + (oneInterval * 5)) { //level 4 brightness
            tempB = 0x04;
        }
        else if (threshold <= min + (oneInterval * 6)) { //level 5 brightness
            tempB = 0x05;
        }
        else if (threshold <= min + (oneInterval * 7)) { //level 6 brightness
        }
        else { //level 7 brightness
            tempB = 0x07;
        }

        PORTB = tempB;
    }
    return 1;
}
