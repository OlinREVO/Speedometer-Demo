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

volatile int i = 0;
volatile float dt = 0;
float time = 0;
float Times[SIZE];
float velocity = 0;

int main(void) {
    /* Initialize Times to all zeros *///changed to 88 for testing.  Put this back later!
    /*for (i = 0; i < SIZE; i++) {
      Times[i] = 88;
    }
    i = 0;*/

    /* Set PC3 to input */
    DDRD &= ~(_BV(DDC3));
    /* Enable pin change interrupt 1(PCINT2) */
    //PCICR |= _BV(PCIE1);
    /* Set PCImake flashNT2 to be triggered by PCINT15 (on PC7) */
    //PCMSK1 |= _BV(PCINT15);

    /* Set PORTB and PORTC, [0-6] to output */
    DDRB |= 0xFF;
    DDRC |= ~(_BV(DDC3));
    DDRD |= 0xFF;

    /* Set Timer/Counter1 on with prescaler at clk_io/1024 */
    TCCR1B |= (_BV(CS12) | _BV(CS10));

    /* All set up, start listening for interrupts */
    sei();

    /* Loop */
    while (-1) {
        uint16_t test;
        dt = (Times[i] + 0.0) * TIMESCALAR / F_IO;
        velocity = (SIZE - 1.0)*CIRCUM/(dt ) * UNITSCALAR;
        ssDisplay(lround(88));
    }
}

/* Service routine for the hall latch */
ISR(PCINT1_vect) {
    uint16_t timerValue;
    
    /* Grab value from TC1 and reset it */
    timerValue = TCNT1;
    TCNT1 = 0;
    /* Save timerValue */
    Times[i] = timerValue;
    /* Increment i */
    i = (i + 1) % SIZE;
}

void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen){
    uint8_t* val = msg;
    velocity = (int)val;

}