/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/
#ifndef HOSTUSE
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#endif

#include "project2.h"

int main(void) {

#ifndef HOSTUSE
  /* Init board hardware. */
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();
#endif

  /* Add your code here */
  project2(); 
}
