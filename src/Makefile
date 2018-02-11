#Make file by Girish Narayanswamy and Karros Huang

#Additional makefile with a list of all source code files 
include sources.mk

TARGET = project1
GENFLAGS = -Wall -Werror -g -O0 -std=c99

#Various platforms to build for: KL25Z, BBB, HOST (default)
#For KL25Z mcu
ifeq ($(PLATFORM),KL25Z)

#Architecture Specific Flags
CPU = cortex-m0plus
ARCH = armv6-m
FPABI = soft
ARCHFLAGS = -mcpu=$(CPU) -mthumb -march=$(ARCH) -mfloat-abi=$(FPABI) -mfpu=fpv4-sp-d16 --specs=nosys.specs


LINKERFILE = ../platform/MKL25Z128xxx4_flash.ld 
COMPILER = arm-none-eabi-gcc
INCLUDES = -I../include/CMSIS -I../include/kl25z -I../platform	
LDFLAGS = -T$(LINKERFILE)

#For Beagle Bone Black
else ifeq ($(PLATFORM),BBB)

VERBOSEOUT = -DVERBOSE
COMPILER = arm-linux-gnueabi-gcc
INCLUDES = -I../include/CMSIS

#For host platform (linux computer), default case
else

#Platform Specific Flags
VERBOSEOUT = -DVERBOSE
COMPILER = gcc

endif

#Compile Defines
INCLUDES +=-I../include/common
CC = $(COMPILER)
CFLAGS = $(GENFLAGS) $(ARCHFLAGS) $(INCLUDES)
CPPFLAGS = -DPROJECT1 $(VERBOSEOUT) $(INCLUDES)
LDFLAGS += -Wl,-Map=$(TARGET).map 

#Generate object variable from implementation .c and .S files 
OBJS := $(SOURCES:.c=.o)
OBJS := $(OBJS:.S=.o)

.PHONY: build
build: $(TARGET).elf

.PHONY: compile-all
compile-all: $(OBJS)

$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@


%.i : %.c
	$(CC) $(CPPFLAGS) -E $< -o $@

%.asm : %.c
	$(CC) $(CFLAGS) -S $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -M $< -o $*.d

%.o : %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o *.i *.elf *.asm *.map *.d
