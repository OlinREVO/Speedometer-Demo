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

volatile int velocity = 0;

int main(void){

	initCAN(NODE_HOME);

	DDRB |= 0xFF;
    DDRC |= ~(_BV(DDC3));
    DDRD |= 0xFF;

    while(-1){//just keep displaying the current velocity
    	if(velocity >80){
    		velocity = 80;
    	}

    	ssDisplay(velocity);
    }
}

void handleCANmsg(uint8_t destID, uint8_t msgID, uint8_t* msg, uint8_t msgLen){
    uint8_t* val = msg;
    velocity = (int)val;

}
