/*Speedometer Display
*======================================================
*
*Function for running the 7-segment speed display node.
*
*Olin REVO, 2014
*/

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "sevensegment.h"
#include "api.h"

int NODE_HOME = NODE_speedometer;

int velocity = 0;

int main(void){

    DDRC |= _BV(PC0);
    DDRC |= _BV(PC1);
    DDRC |= _BV(PC4);
    DDRC |= _BV(PC5);
    DDRC |= _BV(PC6);
    DDRC |= _BV(PC7);

    DDRB |= 0xFF;

    DDRD |= _BV(PD0);
    DDRD |= _BV(PD1);
    DDRD |= _BV(PD2);
    DDRD |= _BV(PD3);
    DDRD |= _BV(PD4);
    DDRD |= _BV(PD5);
    DDRD |= _BV(PD6);
    DDRD |= _BV(PD7);

	initCAN(NODE_HOME);
    initUART();
    char output[size];

    while(1){
        ssDisplay(velocity);
     }
}

void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen){
    velocity = msg[0];
    int size = sizeof(int)/sizeof(char);
    sscanf(velocity, "%d", output);
    UART_putString("\nHi\n");
    UART_putString(output);
}
