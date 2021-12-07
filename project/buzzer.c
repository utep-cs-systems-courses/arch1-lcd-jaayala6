#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

void no_buzzer(){
  CCR0 = 0;
  CCR1 = 0;
}

void bump_wall() {
  buzzer_set_period(150);
}
void bump_wall1() {
  buzzer_set_period(200);
}
int count = 0;
void song() {
  short A4 = 440;
  short D4 = 293;
  short E4 = 329;
  short C4 = 261;
  short G4 = 392;
  short G3 = 195;
  short E3 = 164;
  short A3 = 220;
  short B3 = 246;
  short B3f = 233;
  short F4 = 349;

  int mario[] = {E4, E4, E4, C4, E4, G4, G3, C4, G3, A3, B3, B3f, A3, G3, E4, G4, A4, F4, G4, E4, C4, D4, B3};
  buzzer_set_period(mario[count]);

  if (count >= 23) {
    count = 0;
  }
  else {
    count++;
  }
}
