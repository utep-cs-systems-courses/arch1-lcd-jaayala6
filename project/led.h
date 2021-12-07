#ifndef led_included
#define led_included

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 
#define LED BIT6      /* note that bit zero req'd for display */

void led_init();

#endif
