ECEN5813 Project 4 Authors: Girish Narayanswamy & Karros Huang

This is the code base containing all the headers and source code for project 4. The purpose of the project is to develop portable code, which will build and run for 3 different platforms: The host linux machine, the Beagle Bone Black, and the KL25Z

This directory contains 3 folders src: This folder contains all c implementation code for the project and the Makefile include: This folder contains all header files used as dependencies in the source code platform: This folder contains the linker file needed to build for the KL25Z

To build and run on the host machine, clone this repo, move to the /src directory, and type the "$ make" command.

This will create all of the object (.o), dependency (.d), map (.map), and exacutable (.elf) for the project. To run type the "$ ./project2.elf" command. Additional rules for make are specified and commented in the usage comments below:

Make Usage:

$ make Builds project for HOST (linux) platform Generates all .o .d .map .elf files

$ make build PLATFORM=<HOST,BBB,KL25Z> Builds project for HOST, BBB, or KL25Z platform Generates all .o .d .map .elf files

$ make compile-all PLATFORM=<HOST,BBB,KL25Z> Compiles project source code for HOST, BBB, or KL25Z platform Generates all .o .d files

$ make unit_tests PLATFORM=HOST builds all unit test in unit_test.elf

$ make clean Removes all generate files Removes all .o .d .asm .i .elf .asm files

$ make %.i Generates preprocessed output of a c-implementation file Generates .i files

$ make %.asm Generates assembly output of a c-implementation file Generates .i files

$ make %.o Generates object output of a c-implementation file Generates .o files

All function descriptions exist in the header files. Here is a little description of how this project went:

It is important to note that for the BBB, the make command generates .su files which
provide stack usage information.

It is further important to note that all profiling information can be found in the statistics.txt
Additional information can be found in the screen capture images in the repo.

The following is a sample of the non-blocking logging functionality from
the KL25Z over UART.

===============================
[GPIO]: 0 - [GPIO_INITIALIZED] - GPIO_INIT
[PROJECTFOUR]: 0 - [LOGGER_INITIALIZED] -
[PROJECTFOUR]: 0 - [SYSTEM_ID] - ECEN5813_Project4
[PROJECTFOUR]: 0 - [SYSTEM_VERSION] - PROJECT4_v1.0
[PROJECTFOUR]: 0 - [SYSTEM_INITIALIZED] -
[PROFILING]: 0 - [PROFILING_STARTED] - Profiling_analysis_has_started
[PROF_STDSET]: 0 - [PROFILING_RESULT] - 126
[PROF_MYSET]: 0 - [PROFILING_RESULT] - 306
[PROF_DMASET]: 0 - [PROFILING_RESULT] - 551
[PROF_STDMV]: 0 - [PROFILING_RESULT] - 163
[PROF_MYMV]: 0 - [PROFILING_RESULT] - 367
[PROF_DMAMV]: 0 - [PROFILING_RESULT] - 588
[PROF_STDSET]: 0 - [PROFILING_RESULT] - 756
[PROF_MYSET]: 0 - [PROFILING_RESULT] - 2286
[PROF_DMASET]: 0 - [PROFILING_RESULT] - 731
[PROF_STDMV]: 0 - [PROFILING_RESULT] - 973
[PROF_MYMV]: 0 - [PROFILING_RESULT] - 2707
[PROF_DMAMV]: 0 - [PROFILING_RESULT] - 768
[PROF_STDSET]: 0 - [PROFILING_RESULT] - 7056
[PROF_MYSET]: 0 - [PROFILING_RESULT] - 22086
[PROF_DMASET]: 0 - [PROFILING_RESULT] - 2531
[PROF_STDMV]: 0 - [PROFILING_RESULT] - 9073
[PROF_MYMV]: 0 - [PROFILING_RESULT] - 26107
[PROF_DMAMV]: 0 - [PROFILING_RESULT] - 2568
[PROF_STDSET]: 0 - [PROFILING_RESULT] - 35056
[PROF_MYSET]: 0 - [PROFILING_RESULT] - 110086
[PROF_DMASET]: 0 - [PROFILING_RESULT] - 10531
[PROF_STDMV]: 0 - [PROFILING_RESULT] - 45073
[PROF_MYMV]: 0 - [PROFILING_RESULT] - 130107
[PROF_DMAMV]: 0 - [PROFILING_RESULT] - 10568
[PROFILING]: 0 - [PROFILING_COMPLETED] - Profiling_analysis_has_completed
[PROJECTFOUR]: 0 - [DATA_ANALYSIS_STARTED] -
[PROJECTFOUR]: 0 - [DATA_ALPHA_COUNT] - 56
[PROJECTFOUR]: 0 - [DATA_NUMERIC_COUNT] - 358
[PROJECTFOUR]: 0 - [DATA_PUNCTUATION_COUNT] - 0
[PROJECTFOUR]: 0 - [DATA_MISC_COUNT] - 17
[PROJECTFOUR]: 0 - [DATA_ANALYSIS_COMPLETED] -
[PROJECTFOUR]: 0 - [INFO] - Will_flush_and_coredump_before_infinite_loop
[PROJECTFOUR]: 0 - [CORE_DUMP] - 536883064
[PROJECTFOUR]: 0 - [SYSTEM_HALTED] -
===============================

░░▄▀░░░░░░░░░░░░░░░▀▀▄▄░░░░░░

░░▄▀░░░░░░░░░░░░░░░░░░░░▀▄░░░

░▄▀░░░░░░░░░░░░░░░░░░░░░░░█░░

░█░░░░░░░░░░░░░░░░░░░░░░░░░█░

▐░░░░░░░░░░░░░░░░░░░░░░░░░░░█

█░░░░▀▀▄▄▄▄░░░▄▌░░░░░░░░░░░░▐

▌░░░░░▌░░▀▀█▀▀░░░▄▄░░░░░░░▌░▐

▌░░░░░░▀▀▀▀░░░░░░▌░▀██▄▄▄▀░░▐

▌░░░░░░░░░░░░░░░░░▀▄▄▄▄▀░░░▄▌

▐░░░░▐░░░░░░░░░░░░░░░░░░░░▄▀░

░█░░░▌░░▌▀▀▀▄▄▄▄░░░░░░░░░▄▀░░

░░█░░▀░░░░░░░░░░▀▌░░▌░░░█░░░░

░░░▀▄░░░░░░░░░░░░░▄▀░░▄▀░░░░░

░░░░░▀▄▄▄░░░░░░░░░▄▄▀▀░░░░░░░

░░░░░░░░▐▌▀▀▀▀▀▀▀▀░░░░░░░░░░░

░░░░░░░░█░░░░░░░░░░░░░░░░░░░░

░░╔═╗╔═╗╔═╗░░░░░║░║╔═╗║░║░░░░

░░╠═╣╠╦╝╠╣░░░░░░╚╦╝║░║║░║░░░░

░░║░║║╚═╚═╝░░░░░░║░╚═╝╚═╝░░░░

║╔═░╦░╦═╗╦═╗╦╔╗║╔═╗░░╔╦╗╔═╗╔╗

╠╩╗░║░║░║║░║║║║║║═╗░░║║║╠╣░╔╝

║░╚░╩░╩═╝╩═╝╩║╚╝╚═╝░░║║║╚═╝▄░

from: http://copy.r74n.com/ascii-art
