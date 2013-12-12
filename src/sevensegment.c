/* Simple Seven-Segment Display Driver
 * ===================================
 *
 * Olin REVO, 2013
 */

#include <inttypes.h>
#include <avr/io.h>

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

void ssDisplay(int value){
    uint8_t digit0;
    uint8_t digit1;

    /* Cap value at 99 */
    if (value > 99) {
        value = 99;
    }
    /* Get pinmask for the lower digit and cache it for later */
    digit0= ssDigit(value % 10);
    /* Move over one digit */
    value = (value / 10) % 10;
    /* Get pinmask for upper digit, blank if 0 */
    if (value > 0) {
        digit1 = ssDigit(value);
    }
    else {
        digit1 = 0x00;
    }
    port0(digit0);
    port1(digit1);
}

void port0(uint8_t digit){

    if (digit&(1<<0)){
        PORTC |=_BV(PC0)|1;
    }

    else{
        PORTC &= _BV(PC0)&0;
    }

    if (digit&(1<<1)){
        PORTC |=_BV(PC1)|1;
    }
    else{
        PORTC &=_BV(PC1)&0;
    }

    if (digit&(1<<2)){
        PORTC |=_BV(PC4)|1;
    }
    else{
        PORTC &=_BV(PC4)&0;
    }

    if (digit&(1<<3)){
        PORTC |=_BV(PC5)|1;
    }
    else{
        PORTC &=_BV(PC5)&0;
    }

    if (digit&(1<<4)){  //bottom left,d2
        PORTC |=_BV(PC6)|1;
    }
    else{
        PORTC &=_BV(PC6)&0;
    }

    if (digit&(1<<5)){  //top left, d2
        PORTC |=_BV(PC7)|1;
    }
    else{
        PORTC &=_BV(PC7)&0;
    }

    if (digit&(1<<6)){
        PORTB |=_BV(PB7)|1;
    }
    else{
        PORTB &=_BV(PB7)&0;
    }



    /*PORTC |= (_BV(PC0)&(digit))
|(_BV(PC1)&digit)|(_BV(PC4)&digit)|(_BV(PC5)&digit)|(_BV(PC6)&digit)|(_BV(PC7)&digit);
    PORTC &= ((_BV(PC0)&&(~digit))|(_BV(PC1)&&(~digit))|(_BV(PC4)&&(~digit))|(_BV(PC5)&&(~digit))|(_BV(PC6)&&(~digit))|(_BV(PC7)&&(~digit)));
    PORTB |= _BV(PB7)&&digit;
    PORTB &= ~(_BV(PB7)&&(~digit));*/
}

void port1(uint8_t digit){

    if (digit&(1<<0)){
        PORTB |=_BV(PB0)|1;
    }

    else{
        PORTB &= _BV(PB0)&0;
    }

    if (digit&(1<<1)){
        PORTB |=_BV(PB1)|1;
    }
    else{
        PORTB &=_BV(PB1)&0;
    }

    if (digit&(1<<2)){
        PORTB |=_BV(PB2)|1;
    }
    else{
        PORTB &=_BV(PB2)&0;
    }

    if (digit&(1<<3)){
        PORTB |=_BV(PB3)|1;
    }
    else{
        PORTB &=_BV(PB3)&0;
    }

    if (digit&(1<<4)){
        PORTB |=_BV(PB4)|1;
    }
    else{
        PORTB &=_BV(PB4)&0;
    }

    if (digit&(1<<5)){
        PORTB |=_BV(PB5)|1;
    }
    else{
        PORTB &=_BV(PB5)&0;
    }

    if (digit&(1<<6)){
        PORTB |=_BV(PB6)|1;
    }
    else{
        PORTB &=_BV(PB6)&0;
    }

    /*PORTB |= (_BV(PB0)&&(digit))|(_BV(PB1)&&(digit))|(_BV(PB2)&&(digit))|(_BV(PB3)&&(digit))|(_BV(PB4)&&(digit))|(_BV(PB5)&&(digit))|(_BV(PB6)&&(digit))|(_BV(PB7)&&(digit));
    PORTB &= ~(_BV(PB0)&&(~digit))|(_BV(PB1)&&(~digit))|(_BV(PB2)&&(~digit))|(_BV(PB3)&&(~digit))|(_BV(PB4)&&(~digit))|(_BV(PB5)&&(~digit))|(_BV(PB6)&&(~digit))|(_BV(PB7)&&(~digit));*/
}

