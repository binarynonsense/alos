// timer.c -- Initialises the PIT, and handles clock updates.
//            Written for JamesM's kernel development tutorials.

// The programmable interval timer is a chip connected to IRQ0. It can interrupt the CPU at a user-defined rate (between 18.2Hz and 1.1931 MHz). The PIT is the primary method used for implementing a system clock and the only method available for implementing multitasking (switch processes on interrupt).
// 
//         The PIT has an internal clock which oscillates at approximately 1.1931MHz. This clock signal is fed through a frequency divider, to modulate the final output frequency. It has 3 channels, each with it's own frequency divider.
// 
//         * Channel 0 is the most useful. It's output is connected to IRQ0.
//                 * Channel 1 is very un-useful and on modern hardware is no longer implemented. It used to control refresh rates for DRAM.
//                 * Channel 2 controls the PC speaker.
// 
//                 Channel 0 is the only one of use to us at the moment. 

//PIT has 4 registers in I/O space - 0x40-0x42 are the data ports for channels 0-2 respectively, and 0x43 is the command port. 

#include <kernel/timer.h>
#include <kernel/isr.h>
#include <drivers/console.h>

uint32_t ticks = 0;

static void timer_callback(registers_t regs)
{
//     tick++;
//     console_write("Tick: ");
//     console_write_dec(tick);
//     console_write("\n");
    if(ticks!=0){
        ticks--;
    }
}

uint32_t timer_get_ticks(){
    return ticks;
}

void timer_set_ticks(uint32_t init_ticks){
    ticks=init_ticks;
}


void init_timer(uint32_t frequency)
{
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide its input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);//0x36 sets the pit to repeating mode

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}

void sleep(uint32_t secs){
    //init_timer(1000);//1000 Hz
    timer_set_ticks(secs*1000);
    while(1){
        if(timer_get_ticks()==0){
            break;
        }
    }
    
}
