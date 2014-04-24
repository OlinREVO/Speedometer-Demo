/*Speedometer Display
*======================================================
*
*Function for running the 7-segment speed display node.
*
*Olin REVO, 2014
*/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "sevensegment.h"
#include "api.h"

int NODE_HOME = NODE_speedometer;

int velocity = 55;

int main(void){

    DDRC |= _BV(PC0);
    DDRC |= _BV(PC1);
    DDRC |= _BV(PC4);
    DDRC |= _BV(PC5);
    DDRC |= _BV(PC6);
    DDRC |= _BV(PC7);

    DDRB |= 0xFF;

	initCAN(NODE_HOME);

    while(1){//just keep displaying the current velocity
    	if(velocity >80){
    		velocity = 80;
    	}

    	ssDisplay(velocity);
    }
}

void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen){
    uint8_t* val = msg;
    velocity = 10;
}
