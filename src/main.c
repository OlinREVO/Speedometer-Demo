/* Speedometer Demo
 * ================
 *
 * A simple test of the LED speed display and wheel speed sensor.
 *
 * Olin REVO, 2013
 */

#define F_CPU (1000000L)
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

#include "api.h"
#include "uart.h"


#define maxDataLength 8
#define SIZE 5
#define CIRCUM .3175 * M_PI//meters
#define TIMESCALAR 1024.0
#define F_IO 1000000
#define DT F_IO/TIMESCALAR

volatile int i = 0;
volatile float dt = 1;
float time = 0;
float times[SIZE];
float velocity = 10;

int shunt_res= 5000;

int size = sizeof(uint8_t)/sizeof(char);

/* Service routine for the hall latch */
ISR(INT1_vect) {

    times[i] = TCNT1;
    i = (i+1)%SIZE;
    TCNT1 = 0;
}


int main(void) {

    uint8_t msg[1];
    initUART();

    int j = 0;
    int time = 0;
    char output[size];
    //Initialize Times to all zeros 
    for (i = 0; i < SIZE; i++) {
      times[i] = 0;
    }
    i = 0;
 
    //Enable pin change interrupt 2(PCINT2) 
    PCICR |= _BV(PCIE0);

    // Set Timer/Counter1 on with prescaler at clk_io/1024 //for Hall latch
    TCCR1B |= (_BV(CS12) | _BV(CS10));

    initCAN(NODE_speedometer);
    sei(); // enable global interrupts  
    EICRA |= _BV(ISC10);
    EIMSK |= _BV(INT1);
    /* All set up, start listening for interrupts */

    /* Loop */
    while (1) {
        _delay_ms(100);

        for(j = 0; j < SIZE; j++){
            time = time+times[j];
        }

        uint8_t v = (int)(CIRCUM*SIZE/(time/F_IO/TIMESCALAR));
        v= time/DT;
        msg[0] = v;

        sendCANmsg(NODE_speedometer, MSG_speed,(uint8_t*)msg,1);

    }
}


void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen){
}

