#include <msp430.h>
#include "led.h"


void led_init() {
  P1DIR |= LED;		//< Green led on when CPU on 
  P1OUT |= LED;
}
