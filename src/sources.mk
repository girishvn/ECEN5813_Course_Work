#Additional Source makefile to procide list of source files for Make

SOURCES = main.c \
	conversion.c \
	data.c \
	debug.c \
	project1.c \
	memory.c 

ifeq ($(PLATFORM),KL25Z)
SOURCES += arch_arm32.c \
	system_MKL25Z4.c \
	startup_MKL25Z4.S
endif
