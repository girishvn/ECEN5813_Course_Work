#Make file by Girish Narayanswamy and Karros Huang

#Additional makefile with a list of all source code files 
include sources.mk

TARGET=project1
GENFLAGS=-Wall -Werror -g -O0 -std=c99

#Various platforms to build for: KL25Z, BBB, HOST (default)
#For KL25Z mcu
ifeq ($(PLATFORM),KL25Z)

#Architecture Specific Flags
CPU=cortex-m0plus
ARCH=armv6-m
FPABI=softfp
	
ARCHFLAGS=-mcpu=$(CPU) -mthumb -march=$(ARCH) -mfloat-abi=$(FPABI) -mfpu=fpv4-sp-d16 --specs=nosys.specs

#Platform Specific Flags
LINKERFILE=MKL25Z128xxx4_flash.ld 

#Compile Defines
COMPILER=arm-none-eabi-gcc
	

#For Beagle Bone Black
else ifeq ($(PLATFORM),BBB)

#Platform Specific Flags
VERBOSEOUT=-DVERBOSE

#Compile Defines
COMPILER=arm-linux-gnueabi-gcc


#For host platform (linux computer), default case
else

#Platform Specific Flags
VERBOSEOUT=-DVERBOSE

#Compile Defines
COMPILER=gcc
endif


#Compile Defines
INCLUDES=-I../include/common

CC=$(COMPILER)
CFLAGS=$(GENFLAGS) $(ARCHFLAGS) $(INCLUDES)
CPPFLAGS=-DPROJECT1 $(VERBOSEOUT) $(INCLUDES)
LDFLAGS=-Wl,-Map=$(TARGET).map -T$(LINKERFILE) 

#Generate object variable from implementation .c and .S files 
OBJS:= $(SOURCES:.c=.o)
OBJS:= $(SOURCES:.S=.o)


.PHONY: build
build: 

.PHONY: compile-all
compile-all: 	


%.i : %.c
	$(CC) $(CPPFLAGS) -E $< -o $@

%.asm : %.c
	$(CC) $(CFLAGS) -S $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -M $< -o $*.d

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean: 
	rm -f *.o *.i *.elf *.asm *.map *.d
