PS3_KERNEL_PREFIX ?= $(PS3DEV)/ppu-kernel
CROSS_COMPILE := $(PS3_KERNEL_PREFIX)/bin/powerpc64-ps3-kernel-elf-
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
AR := $(CROSS_COMPILE)ar
STRIP := $(CROSS_COMPILE)strip
INCLUDE		= ../common ../../ps2emu/include ../../lv1/include ../../debug/include
LIBSDIR         =
LIBS            =
BUILD_TYPE      = release

CFLAGS = -ffunction-sections -fdata-sections -Os -m64 -fno-builtin -fno-exceptions \
			   -Os -Wall -Wno-strict-aliasing $(foreach dir,$(INCLUDE),-I$(dir)) \
			   -DPS2EMU -DPS2GXEMU -DFIRMWARE_4_78 -ffreestanding 
CFLAGS += --std=gnu99

ifeq ($(BUILD_TYPE), debug)
CFLAGS += -DDEBUG
endif

ifeq ($(BUILD_TYPE), release)
endif

LDFLAGS= -T ldscript.ld -nostartfiles -nostdlib -nodefaultlibs -Wl,-static -Wl,-s -L. $(foreach dir,$(LIBSDIR),-L$(dir)) $(LIBS) \
	-Wl,--gc-sections -Wl,-Map=ps2gxemu_stage2.map

OBJS = start.o crt0.o main.o ../../ps2emu/src/libc.o ../../ps2emu/src/libc_c.o ../../ps2emu/src/memory.o ../../ps2emu/src/io.o \
	../../ps2emu/src/vuart.o ../../ps2emu/src/patch.o 

ifeq ($(BUILD_TYPE), debug)
OBJS += ../../lv1/src/hvcall.o ../../lv1/src/device.o ../../debug/src/debug.o ../../debug/src/printf.o 
endif

all: ps2gxemu_stage2.bin

objdump: ps2gxemu_stage2.bin
	$(OBJDUMP) -D -EB -b binary -m powerpc:common64 ps2gxemu_stage2.bin

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
	
ps2gxemu_stage2.elf: $(OBJS) ldscript.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.elf *.bin *.map ../../ps2emu/src/*.o ../../lv1/src/*.o ../../debug/src/*.o
