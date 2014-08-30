/*---------------------------------------------------------------------------
--                           ALOS Operative System                         -- 
-----------------------------------------------------------------------------
--                                                                         --
--  A simple operative system created in order to learn more               --
--  about computers                                                        --
--                                                                         --
--  author:   Álvaro García                                                --
--  email:    alvaro@binarynonsense.com                                    --
--  website:  www.binarynonsense.com                                       --
--                                                                         --
--  file: keyboard.c                                                       --
--                                                                         --
--                                                                         --
--  This project is based on the kernel tutorials by JamesM                --
--  http://www.jamesmolloy.co.uk/tutorial_html/index.html                  --
--  and Brandon F http://www.osdever.net/bkerndev/index.php                --
--  And the really helpful OSDev.org wiki and forums                       --
-----------------------------------------------------------------------------
--                      last update: 03 May 2009                           --
---------------------------------------------------------------------------*/

//KEYBOARD by AL

#include <drivers/keyboard.h>
#include <drivers/console.h>
#include <kernel/isr.h>
#include <sys/pio.h>

unsigned char g_kbd_key=0;

/* US Keyboard Layout */
//http://osdever.net/bkerndev/
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};


static void keyboard_callback(registers_t regs)
{
    
    unsigned char scancode = inb(0x60);
    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        //console_write("key pressed:");
        //console_write_hex((int)scancode);
        
        //console_put(kbdus[scancode]);
        //g_kbd_key=kbdus[scancode];
        g_kbd_key=scancode;
    }    

   /* Do something with the scancode.
    * Remember you only get one byte of the scancode each time the ISR is invoked.
    * (Though most of the times the scancode is only one byte.) 
    */

   /* Acknowledge the IRQ, pretty much tells the PIC that we can accept >=priority IRQs now. */
   //outportb(0x20,0x20); //this is done by irq main handler

}

unsigned char keyboard_scancode_to_ascii(unsigned char scancode){
    return kbdus[scancode];
}

void init_keyboard()
{
    // Firstly, register our keyboard callback.
    register_interrupt_handler(IRQ1, &keyboard_callback);

}

