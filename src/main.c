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
#include "sevensegment.h"

#define SIZE 5
#define CIRCUM .3175 * 3.14
#define TIMESCALAR 1024
#define F_IO 8000000

volatile int i = 0;
float dt = 0;
float time = 0;
float Times[SIZE];
long velocity = 0;

volatile uint8_t out = 0;

int main(void) {
    for (i = 0; i < SIZE; i++)
      Times[i] = 0;
    i = 0;

    /* Set PD0 to input */
    DDRD &= ~(_BV(DDD0));
    /* Enable pin change interrupt 2 (PCINT2) */
    PCICR |= _BV(PCIE2);
    /* Set PCINT2 to be triggered by PCINT16 (on PD0) */
    PCMSK2 |= _BV(PCINT16);

    /* Set PB0 to output */
    DDRB |= _BV(DDB0);

    /* Set Timer/Counter1 on with prescaler at clk_io/64 */
    TCCR1B |= (_BV(CS11) | _BV(CS10));

    /* All set up, start listening for interrupts */
    sei();

    /* Loop */
    while (-1) {
        dt = Times[(i + SIZE -1)%SIZE] - Times[i];
        velocity = (SIZE - 1.0)*TIMESCALAR*CIRCUM/(dt * F_IO);
        /* If TC1 greater than half full, try to turn on PB0 */
        if (TCNT1 & 0x1000) {
            PORTB |= out & _BV(PORTB0);
        }
        /* Turn off PB0 */
        else {
            PORTB &= ~(_BV(PORTB0));
        }
    }
}

/* Service routine for the hall latch */
ISR(PCINT2_vect) {
    /* Toggle PB0 */
    Times[i] = time;
    out = ~out;
}

