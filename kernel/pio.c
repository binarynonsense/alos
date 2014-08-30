#include <sys/types.h>

// Write a byte out to the specified port.
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void outw(uint16_t port, uint16_t value){//modified from marteos version
    
    asm volatile(".byte 0x66; outl %0, %%dx" : : "a" (value) , "d" (port));
}

/*
#define outw(port, val) \
({asm volatile(".byte 0x66; outl %0, %%dx" : : "a" ((unsigned short)(val)) , "d" ((unsigned short)(port))); })*/

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}
