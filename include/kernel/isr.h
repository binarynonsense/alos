#ifndef ISR_H
#define ISR_H
//isr.h -- Interface and structures for high level interrupt service routines.
//based on JamesM's kernel development tutorials.
#include <sys/types.h>

// A few defines to make life a little easier
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct registers
{
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
typedef void (*isr_t)(registers_t);
void register_interrupt_handler(uint8_t n, isr_t handler);
#endif

// CPU-dedicated interrupts:
// 
// * 0 - Division by zero exception
// * 1 - Debug exception
// * 2 - Non maskable interrupt
// * 3 - Breakpoint exception
// * 4 - 'Into detected overflow'
// * 5 - Out of bounds exception
// * 6 - Invalid opcode exception
// * 7 - No coprocessor exception
// * 8 - Double fault (pushes an error code)
// * 9 - Coprocessor segment overrun
// * 10 - Bad TSS (pushes an error code)
// * 11 - Segment not present (pushes an error code)
// * 12 - Stack fault (pushes an error code)
// * 13 - General protection fault (pushes an error code)
// * 14 - Page fault (pushes an error code)
// * 15 - Unknown interrupt exception
// * 16 - Coprocessor fault
// * 17 - Alignment check exception
// * 18 - Machine check exception
// * 19-31 - Reserved

              
