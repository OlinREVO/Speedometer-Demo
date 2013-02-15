/* Speedometer Demo
 * ================
 *
 * A simple test of the LED speed display and wheel speed sensor. 
 *
 * Olin REVO, 2013
 */

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
    /* Set PD0 to input */
    DDRD &= ~(_BV(DDD0));
    /* Enable pin change interrupt 2 (PCINT2) */
    PCICR |= _BV(PCIE2);
    /* Set PCINT2 to be triggered by PCINT16 on PD0 */
    PCMSK2 |= _BV(PCINT16);

    /* Set PB0 to output */
    DDRB |= _BV(DDB0);
    /* Turn PB0 on */
    PORTB |= _BV(PORTD0);

    /* Ok, start listening for interrupts */
    sei();

    /* Loop */
    while (-1) { }
}

/* Service routine for the hall latch */
ISR(PCINT2_vect) {
    /* Toggle PB0 */
    PORTB = ~PORTB;
}

