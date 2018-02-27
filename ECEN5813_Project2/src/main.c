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

#include "project1.h"

int main()
{
#ifdef PROJECT1
	project1();
#endif

	return 0;
}
