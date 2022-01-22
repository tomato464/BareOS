ARCH=x86_64-w64-mingw32
CC=$(ARCH)-gcc
CFLAGS=-Wall -Wextra -e EfiMain -nostdinc -nostdlib -fno-builtin -Wl,--subsystem,10
LDFLAGS = -lgcc

TARGET=main.efi

OBJS=main.o lib.o efi.o shell.o graphics.o gui.o file.o

BOOT_PATH=../fs/EFI/BOOT/

.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET) : Makefile $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

run : $(TARGET) Makefile run_qemu.sh $(BOOT_PATH)
	cp $(TARGET) $(BOOT_PATH)BOOTX64.EFI
	./run_qemu.sh

clean : 
	rm $(TARGET) $(OBJS)

.c.o : $<
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

.PHONY : run clean
