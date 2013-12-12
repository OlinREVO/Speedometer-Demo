/* Simple Seven-Segment Display Driver
 * ===================================
 * 
 * Expects the segments of a display to be connected to one output port in 
 * the diagram below:
 *
 *      __0__
 *     |     |
 *     5     1
 *     |__6__|
 *     |     |
 *     4     2
 *     |__3__| (7)
 *
 * Olin REVO, 2013
 */

#ifndef _sevensegment_h
#define _sevensegment_h

#include <inttypes.h>

/* Converts one decimal digit to a pin mask */
uint8_t ssDigit(uint8_t dec);

/* Display a value as two digits across two output ports */
void ssDisplay(int value);

#endif

