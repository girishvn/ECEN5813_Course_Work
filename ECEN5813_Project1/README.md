ECEN5813 Project 1
Authors: Girish Narayanswamy & Karros Huang

This is the codebase containing all the headers and source code for project 1.
The purpose of the project is to develop portable code, which will build and run for 3
different platforms: The host linux machine, the Beagle Bone Black, and the KL25Z

This directory contains 3 folders
src: This folder contains all c implementation code for the project and the Makefile
include: This folder contains all header files used as dependecies in the source code
platform: This folder contains the linker file needed to build for the KL25Z

The 3 .elf files are the exactuables for the 3 platforms (HOST, BBB, KL25Z)
They are primarily for test purposes.

To build and run on the host machine, clone this repo, move to the /src directory,
and type the "$ make" command. 

This will create all of the object (.o), dependency (.d), map (.map), and exacutable
(.elf) for the project. To run type the "$ ./project1.elf" command. Additional rules for make are specified and commented in the usage comments in the Makefile.

All function descriptons exist in the header files. 


Here is a little description of how this project went:

░░▄▀░░░░░░░░░░░░░░░▀▀▄▄░░░░░ 
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
