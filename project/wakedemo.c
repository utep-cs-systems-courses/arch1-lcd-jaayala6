#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"

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
  unsigned int color = (blue << 11) | (green << 5) | red;
  unsigned int color2 = (blue << 9) | (green << 2) | red;
  static unsigned char step = 0;
  static unsigned char bottomEdge = 159;
  static unsigned char topEdge = 0;
  static unsigned char sideEdge = 127;
  static unsigned char xspeed = 1;
  static unsigned char yspeed = 1;
  static unsigned char x = 0;
  static unsigned char y = 80;

  if (switches & SW4) return;
  clearScreen(COLOR_BLACK);
  drawString5x7(x, y, "DVD", color, color2);
  if (switches & SW3) green = (green + 1) % 64;
  if (switches & SW2) blue = (blue + 2) % 32;
  if (switches & SW1) red = (red - 3) % 32;
  x = x + xspeed;
  y = y + yspeed;
  if (x + 5 == sideEdge || x == 0) {
    xspeed = xspeed * -1;
    //int startCol = col - step;
    //int endCol = col + step;
    //int width = 1 + endCol - startCol;
    // a color in this BGR encoding is BBBB BGGG GGGR RRRR
    //unsigned int color = (blue << 11) | (green << 5) | red;
    // unsigned int color2 = (blue << 9) | (green << 2) | red;
    //fillRectangle(startCol, row+step, width, 1, color);
    //fillRectangle(startCol, row-step, width, 1, color);
    //clearScreen(COLOR_BLACK);
    //drawString5x7(x, y, "DVD", color, color2);
    //step ++;
  }
  if (y + 7 == bottomEdge || y == 0) {     
    yspeed = yspeed * -1;
  }
}
