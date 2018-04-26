/**
 * @file platform.h
 * @brief An abstraction that chooses between which platform specific lower level functions to use
 *
 * This header file creates an independent layer to switch between
 * which platform specific lower level functions to use, as well as print useful architecture sizes.
 *
 * @author Karros Huang & Girish Narayanswamy
 * @date April. 15, 2018
 * @version 2.0
 *
 */

#ifndef SOURCE_PLATFORM_H_
#define SOURCE_PLATFORM_H_

#include <stdio.h> /* for print */

#if defined(VERBOSE) && (defined(BBBUSE) || defined(HOSTUSE))

#define PRINTF printf /* for print */

#else

#define PRINTF

#endif

#endif /* SOURCE_PLATFORM_H_ */
