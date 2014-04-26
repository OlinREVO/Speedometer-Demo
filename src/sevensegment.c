/* Simple Seven-Segment Display Driver
 * ===================================
 *
 * Olin REVO, 2013
 */

#include <inttypes.h>
#include <avr/io.h>
#include <api.h>


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
        return 0b01001011;
    case 3:
        return 0b01100111;
    case 2:
        return 0b01110110;
    case 1:
        return 0b00000011;
    default:
        return 0b00111111;
    }
}



void port(uint8_t digit, volatile uint8_t pinarray[], volatile uint8_t* portarray[]){
    int i;
    for (i = 0; i < 7; i++){
        if (digit&(1<<i)){
            *portarray[i] |= _BV(pinarray[i]);
        } else {
            *portarray[i] &= ~_BV(pinarray[i]);
        }
    }
}

void ssDisplay(int value){
    uint8_t digit0;
    uint8_t digit1;

    //OK list: PB5,PB4,PC0,PC6
    
    volatile uint8_t pin0array[7] = {PC4, PC7, PC1, PC0, PC6, PC5, PB2};
    volatile uint8_t* port0array[7] = {&PORTC, &PORTC, &PORTC, &PORTC, &PORTC, &PORTC, &PORTB};

    volatile uint8_t pin1array[7] = {PB7, PB1, PB0, PB5, PB4, PB3, PB6};
    volatile uint8_t* port1array[7] = {&PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB, &PORTB};

    /* Cap value at 99 */
    if (value > 99) {
        value = 99;
    }
    /* Get pin mask for the lower digit and cache it for later */
    digit0= ssDigit(value % 10);
    /* Move over one digit */
    value = (value / 10) % 10;
    /* Get pin mask for upper digit, blank if 0 */
    if (value > 0) {
        digit1 = ssDigit(value);
    }
    else {
        digit1 = 0x00;
    }
    port(digit0, pin0array, port0array);
    port(digit1, pin1array, port1array);
}