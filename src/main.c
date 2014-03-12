/* Speedometer Demo
 * ================
 *
 * A simple test of the LED speed display and wheel speed sensor.
 *
 * Olin REVO, 2013
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "sevensegment.h"
#include "api.h"

#define SIZE 2
#define CIRCUM .3175 * M_PI
#define TIMESCALAR 1024
#define F_IO 1000000
/* m/s to mph */
#define UNITSCALAR 2.23694
#define DT TIMESCALAR/F_IO

volatile int i = 0;
volatile float dt = 0;
float time = 0;
float Times[SIZE];
float velocity = 0;

int shunt_res= 5000;

int NODE_HOME = NODE_halleffect;
int NODE_TARGET_1 = NODE_watchdog;
int NODE_TARGET_2 = NODE_speedometer;

uint8_t vel[1];
uint8_t v[2];

void sendVelocity(){
    dt = (Times[i] + 0.0) * DT;
    velocity = (SIZE - 1.0)*CIRCUM/(dt) * UNITSCALAR;
    vel[0] = velocity;

    sendCANmsg(NODE_TARGET_2, MSG_speed,vel,1);
}

void stateOfCharge(){
    //Reset the ADMUX channel select bits (lowest 5)
    ADMUX &= ~(0x1F);
    //the low 4 bits of ADMUX select the ADC channel
    ADMUX |= 0x02;
    //Wait for ADC reading
    ADCSRA |=  _BV(ADSC);
    while(bit_is_set(ADCSRA, ADSC));

    //ADC is a macro to combine ADCL and ADCH
    v[0]= ADC;
    sendCANmsg(NODE_TARGET_1,MSG_data_other, v, 2);
}

int main(void) {
    //Initialize Times to all zeros 
    for (i = 0; i < SIZE; i++) {
      Times[i] = 0;
    }
    i = 0; //Reset Index Counter

    /* Set PC3 to input */
    DDRD &= ~(_BV(DDC3));
    /* Enable pin change interrupt 1(PCINT2) */
    PCICR |= _BV(PCIE1);
    /* Set PCImake flashNT2 to be triggered by PCINT15 (on PC7) */
    PCMSK1 |= _BV(PCINT15);

    //Turn on ADC
    ADCSRA |= _BV(ADEN);
    //Enable internal reference voltage
    ADCSRB &= _BV(AREFEN);
    //Set internal reference voltage as AVcc
    ADMUX |= _BV(REFS0);

    /* Set PORTB and PORTC, [0-6] to output */
    /*
    DDRB |= 0xFF;
    DDRC |= ~(_BV(DDC3));
    DDRD |= 0xFF;
    */

    DDRB &= ~(_BV(PB0)); //Interrupt pin for hall-latch
    DDRB &= ~(_BV(PB5)); //State of Charge Input
    DDRB &= ~(_BV(PB4)); //State of Charge Input

    /* Set Timer/Counter1 on with prescaler at clk_io/1024 *///for Hall latch
    TCCR1B |= (_BV(CS12) | _BV(CS10));

    /* All set up, start listening for interrupts */
    sei();

    /* Loop */
    while (1) {
        sendVelocity();
        stateOfCharge();
    }
}

/* Service routine for the hall latch */
ISR(PCINT0_vect) {
    uint16_t timerValue;
    PORTB |= _BV(PB4); //Check if hall-latch is registering - LED
    
    /* Grab value from TC1 and reset it */
    timerValue = TCNT0;
    TCNT0 = 0;
    /* Save timerValue */
    Times[i] = timerValue;
    /* Increment i */
    i = (i + 1) % SIZE;
}

void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen){
}

