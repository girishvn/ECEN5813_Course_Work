/**
 * @file platform.h
 * @brief An abstraction that chooses between which platform specific lower level functions to use
 *
 * This header file creates an independent layer to switch between
 * which platform specific lower level functions to use, as well as print useful architecture sizes.
 *
 * @author Karros Huang
 * @date Feb. 1, 2018
 * @version 1.0
 *
 */
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <stdio.h> /* for print */

#ifdef VERBOSE

#define PRINTF printf /* for print */

#else

#define PRINTF

#endif

#endif /* __PLATFORM_H__ */
