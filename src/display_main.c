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

uint8_t lightArray[7] = {PD0, PD1, PD2, PD3, PD4, PD5, PD6,PD7};

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

    while(1){
        ssDisplay(velocity);
        lightDisplay(velocity);
     }
}

void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen){
    velocity = msg[0];
}

void lightDisplay(int velocity){
    int i = 0;

    for(i = 0;i < velocity/10;i++){
        PORTD |= (1<<lightDisplay[i]);
    }

}