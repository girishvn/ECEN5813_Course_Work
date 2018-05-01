#
# @file conversion.c
# @brief Additional make file used by Makefile with src information
#
# This make file contains a list of the additional source files needed depending on the patform
#
# @author Girish Narayanswamy
# @date March 4 2018
# @version 1.0
#
#

SOURCES = main.c \
	circbuf.c \
	conversion.c \
	data.c \
	debug.c \
	memory.c \
	profiling.c \
	project1.c \
	project2.c \
	project3.c \
	timer.c

ifeq ($(PLATFORM),KL25Z)
SOURCES += arch_arm32.c \
	dma.c \
	GPIO.c \
	nordic.c \
	SPI.c \
	startup_MKL25Z4.S \
	system_MKL25Z4.c \
	uart.c
endif

ifeq ($(PLATFORM),HOST)
UNITTESTSOURCES = unit_tests.c \
	memory.c \
	circbuf.c \
	conversion.c
endif
