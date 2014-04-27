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

    while(1){//just keep displaying the current velocity
    	//if(velocity >80){
    	   //velocity = 80;
    	//}
        /*UART_putString("HELLO\n");*/
        //High is |=~_BV..\.
        //Low is &=
        //PORTC |= _BV(PC1);

        ssDisplay(velocity);
 
    }
}

void handleCANmsg(uint8_t destID, uint8_t msgID, char* msg, uint8_t msgLen){
    sscanf(msg, "%d", &velocity);
    UART_putString("Hi\n");
    UART_putString(msg);
}
