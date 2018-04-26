/**
 * @file main.c
 * @brief Main file of the program
 *
 * @author Girish Narayanswamy & Karros Huang
 * @date April 10, 2018
 * @version 1.0
 *
 */


/* CORE FILES IF TARGET KL25Z */
#if !defined(KL25ZCMNDLNBLD) && defined(KL25ZUSE) /* includes for on ide debugging */
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#endif

#include "project3.h"

int main(void) {
  /* Init board hardware. */
#if !defined(KL25ZCMNDLNBLD) && defined(KL25ZUSE)
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();
#endif

#ifdef PROJECT3
  return project3();
#endif

#ifdef PROJECT2

#endif

#ifdef PROJECT1

#endif

}
