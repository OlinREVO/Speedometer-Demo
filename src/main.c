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
#include <util/delay.h>

#define SIZE 2
#define CIRCUM .3175 * M_PI
#define TIMESCALAR 1024
#define F_IO 1000000
#define F_CPU 1000000
/* m/s to mph */
#define UNITSCALAR 2.23694

volatile int i = 0;
volatile float dt = 0;
float time = 0;
float Times[SIZE];
float velocity = 0;

int main(void) {
    /* Initialize Times to all zeros */
    for (i = 0; i < SIZE; i++) {
      Times[i] = 0;
    }
    i = 0;

    /* Set PD0 to input */
    //DDRD &= ~(_BV(DDD0));
    /* Enable pin change interrupt 2 (PCINT2) */
    //PCICR |= _BV(PCIE2);
    /* Set PCINT2 to be triggered by PCINT16 (on PD0) */
    //PCMSK2 |= _BV(PCINT16);

    /* Set PORTB and PORTC, [0-6] to output */
    DDRB |= ~(_BV(DDB7));
    DDRC |= ~(_BV(DDC7));
    DDRD = 0xff;

    /* Set Timer/Counter1 on with prescaler at clk_io/1024 */
    //TCCR1B |= (_BV(CS12) | _BV(CS10));

    /* All set up, start listening for interrupts */
    //sei();
    int val = 0;
    int ledval = val * 2/5;

    /* Loop */
    while (-1) {
        //dt = (Times[i] + 0.0) * TIMESCALAR / F_IO;
        //velocity = (SIZE - 1.0) * CIRCUM/ dt * UNITSCALAR;
        //ssDisplay(lround(velocity), &PORTC, &PORTB);
        ssDisplay(val, &PORTC, &PORTB);
        PORTD = ~(0xff >> ledval);
        //_delay_ms(500);
        //val = (val + 1) % 22;
        //ledval = val * 2/5;
    }
}

/* Service routine for the hall latch */
ISR(PCINT2_vect) {
    uint16_t timerValue;
    
    /* Grab value from TC1 and reset it */
    timerValue = TCNT1;
    TCNT1 = 0;
    /* Save timerValue */
    Times[i] = timerValue;
    /* Increment i */
    i = (i + 1) % SIZE;
}

