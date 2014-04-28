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
#define CIRCUM .3175 * M_PI
#define TIMESCALAR 1024.0
#define F_IO 1000000
/* m/s to mph */
#define UNITSCALAR 2.23694
#define DT TIMESCALAR/F_IO

volatile int i = 0;
volatile float dt = 1;
float time = 0;
float Times[SIZE];
float velocity = 10;

int shunt_res= 5000;

int NODE_HOME = NODE_halleffect;
int NODE_TARGET_1 = NODE_watchdog;
int NODE_TARGET_2 = NODE_speedometer;

/* Service routine for the hall latch */
ISR(INT1_vect) {
    UART_putString("INTERRUPT\n");
    /* Grab value from TC1 and reset it */

        int size = sizeof(uint8_t)/sizeof(char);
        char output[size];
        sprintf(output,"%d",TCNT1);
        UART_putString("\ntime\n");
        UART_putString(output);

    dt = TCNT1;
    TCNT1 = 0;

    //velocity = velocity + TIMESCALAR*CIRCUM/(dt * F_IO)/2.0;
    time = dt*TIMESCALAR/F_IO;
}


int main(void) {
    int size = sizeof(int)/sizeof(char);
    char output[size];
    uint8_t can[1];
    //Initialize Times to all zeros 
    for (i = 0; i < SIZE; i++) {
      Times[i] = 0;
    }
    i = 0;
 
     /*Enable pin change interrupt 1(PCINT2) 
    /*PCICR |= _BV(PCIE0);*/

     /*Set PCImake flashNT2 to be triggered by PCINT15 (on PC7) */
    /*PCMSK1 |= _BV(PCINT0);*/

    //Turn on ADC
    //ADCSRA |= _BV(ADEN);
    //Enable internal reference voltage
    //ADCSRB &= _BV(AREFEN);
    //Set internal reference voltage as AVcc
    //ADMUX |= _BV(REFS0);

    // Set Timer/Counter1 on with prescaler at clk_io/1024 //for Hall latch
    TCCR1B |= (_BV(CS12) | _BV(CS10));

    initCAN(NODE_HOME);
    sei(); // enable global interrupts  
    EICRA |= _BV(ISC10);
    EIMSK |= _BV(INT1);
    /* All set up, start listening for interrupts */

    initUART();
    /* Loop */
    while (1) {
        _delay_ms(100);

        uint8_t v = (int)(CIRCUM/time);

        sprintf(output,"%d",v);
        UART_putString("\nvelocity\n");
        UART_putString(output);
        can[0] = v;
        sendCANmsg(NODE_TARGET_2, MSG_speed,can,1);

        /*ADCSRA |=  _BV(ADSC);
            while(bit_is_set(ADCSRA, ADSC));

            //ADC is a macro to combine ADCL and ADCH
            uint8_t voltage = ADC;
            uint8_t v[2];
            v[0]= voltage;

        sendCANmsg(NODE_TARGET_1,MSG_data_other, v, 2);*/
    }
}


void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen){
}

