/**
 * @file main.c
 * @brief file with main function of program
 *
 * This source file holds the delaration of the main function of the program.
 * It calls the project1 test function.
 *
 * @author Girish Narayanswamy
 * @date February 6 2018
 * @version 1.0
 *
 */

#include "project2.h"

int main()
{
#ifdef PROJECT2
	project2();
#endif

	return 0;
}
