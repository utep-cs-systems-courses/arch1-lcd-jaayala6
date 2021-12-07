#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"


// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
    secCount = 0;
    redrawScreen = 1;
  }
}
  
void update_shape();

void main()
{
  led_init();
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}
   
void
update_shape()
{

  static unsigned char row = screenHeight / 2, col = screenWidth / 2;
  static char blue = 31, green = 0, red = 31;
  static char blue2 = 31, green2 = 0, red2 = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;
  unsigned int color2 = (blue << 9) | (green << 2) | red;
  unsigned int color3 = (blue2 << 3) | (green2 << 7) | red2;
  static unsigned char step = 0;
  static unsigned char bottomEdge = 159;
  static unsigned char left_topEdge = 0;
  static unsigned char rightEdge = 115;
  static unsigned char xspeed = 3;
  static unsigned char yspeed = 3;
  static unsigned char x = 0;
  static unsigned char y = 81;
  
  if (switches & SW4){
    no_buzzer(); 
    return;
  }
  //clearScreen(COLOR_BLACK);
  fillRectangle(x, y-1, 18, 10, color3);
  drawString5x7(x, y, "DVD", color, color3);
  
  x = x + xspeed;
  y = y + yspeed;
  if (switches & SW3){
    green = (green + 1) % 64;
    xspeed = xspeed * -1;
  }
  if (switches & SW2) {
    blue = (blue + 2) % 32;
    yspeed = yspeed * -1;
  }
 
  if (switches & SW1) {
    if (step <= 22) {
      int startCol = col - step;
      int endCol = col + step;
      int width = 1 + endCol - startCol;
      int startCol2 = col - step;
      int endCol2 = col + step;
      int width2 = 1 + endCol - startCol;
    // a color in this BGR encoding is BBBB BGGG GGGR RRRR
      unsigned int color = (blue << 11) | (green << 5) | red;
      unsigned int color2 = (blue << 9) | (green << 2) | red;
      fillRectangle(startCol, row+step-30, width, 1, color);
      fillRectangle(startCol2, row-step, width, 1, color);
      step++;
    } else {
      step = 0;
    }
    red = (red - 3) % 32;
    song();
  }
  
  if (x + 5 >= rightEdge || x == left_topEdge) {
    xspeed = xspeed * -1;
    green2 = (green2 + 1) % 64;
    blue = (blue2 + 2) % 32;
    red = (red2 - 3) % 32;
    bump_wall();
  }
  
  if (y + 7 >= bottomEdge || y == left_topEdge) {     
    green2 = (green + 1) % 64;
    blue2 = (blue + 2) % 32;
    red2 = (red - 3) % 32;
    yspeed = yspeed * -1;
    bump_wall1();
  }
}
