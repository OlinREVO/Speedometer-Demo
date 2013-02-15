/* Simple Seven-Segment Display Driver
 * ===================================
 *
 * Olin REVO, 2013
 */

#include <inttypes.h>

uint8_t ssDigit(uint8_t dec) {
    switch (dec) {
    case 9:
        return 0b01101111;
    case 8:
        return 0b01111111;
    case 7:
        return 0b00000111;
    case 6:
        return 0b01111101;
    case 5:
        return 0b01101101;
    case 4:
        return 0b01100110;
    case 3:
        return 0b01001111;
    case 2:
        return 0b01011011;
    case 1:
        return 0b00000110;
    default:
        return 0b00111111;
    }
}

void ssDisplay(int value, volatile uint8_t *port0, volatile uint8_t *port1){
    uint8_t digit0;

    /* Get pinmask for the lower digit and cache it for later */
    digit0= ssDigit(value % 10);
    /* Move over one digit */
    value /= 10;
    /* Get pinmask for upper digit and write both to output ports */
    *port1 = ssDigit(value % 10);
    *port0 = digit0;
}

