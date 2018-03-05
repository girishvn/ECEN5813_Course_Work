ECEN5813 Project 2 Authors: Girish Narayanswamy & Karros Huang

This is the code base containing all the headers and source code for project 2. The purpose of the project is to develop portable code, which will build and run for 3 different platforms: The host linux machine, the Beagle Bone Black, and the KL25Z

This directory contains 3 folders src: This folder contains all c implementation code for the project and the Makefile include: This folder contains all header files used as dependencies in the source code platform: This folder contains the linker file needed to build for the KL25Z

To build and run on the host machine, clone this repo, move to the /src directory, and type the "$ make" command.

This will create all of the object (.o), dependency (.d), map (.map), and exacutable (.elf) for the project. To run type the "$ ./project1.elf" command. Additional rules for make are specified and commented in the usage comments below:

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

This following is the Unit Test Output:

[==========] Running 28 test(s).

[ RUN      ] memMvTstInvldPtr

[       OK ] memMvTstInvldPtr

[ RUN      ] memMvTstNoOvrlp

[       OK ] memMvTstNoOvrlp

[ RUN      ] memMvTstSrcOvrlpDst

[       OK ] memMvTstSrcOvrlpDst

[ RUN      ] memMvTstDstOvrlpSrc

[       OK ] memMvTstDstOvrlpSrc

[ RUN      ] memMvTstDstEqSrc

[       OK ] memMvTstDstEqSrc

[ RUN      ] memSetTstInvldPtr

[       OK ] memSetTstInvldPtr

[ RUN      ] memSetTstSetVal

[       OK ] memSetTstSetVal

[ RUN      ] memZeroTstInvldPtr

[       OK ] memZeroTstInvldPtr

[ RUN      ] memZeroTstSetVal

[       OK ] memZeroTstSetVal

[ RUN      ] memRvrsTstInvldPtr

[       OK ] memRvrsTstInvldPtr

[ RUN      ] memRvrsTstOddLen

[       OK ] memRvrsTstOddLen

[ RUN      ] memRvrsTstEvenLen

[       OK ] memRvrsTstEvenLen

[ RUN      ] memRvrsTstAllChars

[       OK ] memRvrsTstAllChars

[ RUN      ] cnvrsnAtoiTstInvldPtr

[       OK ] cnvrsnAtoiTstInvldPtr

[ RUN      ] cnvrsnAtoiTstZeroInt

[       OK ] cnvrsnAtoiTstZeroInt

[ RUN      ] cnvrsnAtoiTstMaxInt

[       OK ] cnvrsnAtoiTstMaxInt

[ RUN      ] cnvrsnItoaTstInvldPtr

[       OK ] cnvrsnItoaTstInvldPtr

[ RUN      ] cnvrsnItoaTstZeroInt

[       OK ] cnvrsnItoaTstZeroInt

[ RUN      ] cnvrsnItoaTstMaxInt

[       OK ] cnvrsnItoaTstMaxInt

[ RUN      ] CBTstAllocFree

[       OK ] CBTstAllocFree

[ RUN      ] CBTstInvldPtr

[       OK ] CBTstInvldPtr

[ RUN      ] CBTstAddRmv

[       OK ] CBTstAddRmv

[ RUN      ] CBTstFullBuff

[       OK ] CBTstFullBuff

[ RUN      ] CBTstEmptBuff

[       OK ] CBTstEmptBuff

[ RUN      ] CBTstWrpAdd

[       OK ] CBTstWrpAdd

[ RUN      ] CBTstWrpRmv

[       OK ] CBTstWrpRmv

[ RUN      ] CBTstOverFull

[       OK ] CBTstOverFull

[ RUN      ] CBTstOverEmpt

[       OK ] CBTstOverEmpt

[==========] 28 test(s) run.

[  PASSED  ] 28 test(s).

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
