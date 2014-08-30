# Makefile for AL-OS

SOURCES=kernel/boot.o kernel/interrupt.o kernel/gdt.o main.o console.o descriptor_tables.o isr.o timer.o keyboard.o mouse.o pio.o string.o stdio.o cli.o vgacore.o testvga.o testsleep.o testspeaker.o

CC=gcc
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -Iinclude
LDFLAGS=-Tkernel/link.ld
ASFLAGS=-felf
VPATH = kernel:drivers:drivers/vga:drivers/mouse:drivers/keyboard:drivers/console:libc

all: $(SOURCES) link

clean:
	-rm *.o oskernel kernel/*.o

link:
	ld $(LDFLAGS) -o oskernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
