/**
 * @file project4.h
 * @brief Implementation of the project3.h file
 *
 * This source file holds functions stubs and includes for project3.c
 *
 * @author Girish Narayanswamy
 * @date April 10 2018
 * @version 1.0
 *
 */

#ifndef SOURCE_PROJECT4_H_
#define SOURCE_PROJECT4_H_

#include <stdint.h>


void printdataHost(void);

void printData(void);

void processData(void);

#if defined(BBBUSE) || defined(HOSTUSE)
void processDataHost(uint8_t *dataPointer);
#endif




/*
 * @brief Runs the program flow for project 4
 *
 * Calls ... functions
 *
 * @param none
 *
 * @return VOID
 */
uint8_t project4(void);

#endif /* SOURCE_PROJECT4_H_ */
