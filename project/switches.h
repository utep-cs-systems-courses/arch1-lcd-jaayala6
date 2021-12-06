#ifndef switches_included
#define switches_included

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8
#define SWITCHES 15

static char switch_update_interrupt_sense();
void switch_init();
void switch_interrupt_handler();
extern int switches;

#endif
