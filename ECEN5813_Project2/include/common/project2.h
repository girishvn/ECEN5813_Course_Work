/*
* @file project2.h
* @brief
* @author Karros Huang & Girish Narayanswamy
* @date 3/3/2017
*/

#ifndef PROJECT2_H_
#define PROJECT2_H_

/*
 * @brief Main function
 * Main function that begins setting up the MCU to process a set of data and reporting it
 * @param none
 *
 * @return VOID
 */
void project2();

/*
 * @brief Process an input sequence of characters
 * Reads through the data stored in the circular buffer and counts how many alphabet, numerical, punctional, and misc. characters there are
 * @param none
 *
 * @return VOID
 */
void processData();

/*
 * @brief Prints the data
 * Prints the counts of characters through the UART and out to a terminal
 * @param none
 *
 * @return VOID
 */
void printData();


#endif /* PROJECT2_H_ */
