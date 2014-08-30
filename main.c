/*---------------------------------------------------------------------------
--                     ALOS - Álvaro's Operative System                    -- 
-----------------------------------------------------------------------------
--                                                                         --
--  A simple operative system I created in order to learn more             --
--  about computers                                                        --
--                                                                         --
--  author:   Álvaro García                                                --
--  website:  www.binarynonsense.com                                       --
--                                                                         --
--  file: main.c                                                           --
--                                                                         --
--                                                                         --
--  This project is based on the kernel tutorials by JamesM                --
--  http://www.jamesmolloy.co.uk/tutorial_html/index.html                  --
--  and Brandon F http://www.osdever.net/bkerndev/index.php                --
--  And the really helpful OSDev.org wiki and forums                       --
-----------------------------------------------------------------------------
--                      last update: 03 May 2009                           --
---------------------------------------------------------------------------*/

#include <drivers/console.h>
#include <kernel/descriptor_tables.h>
#include <kernel/timer.h>
#include <kernel/cli.h>

int main(struct multiboot *mboot_ptr)
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    console_clear();
    // Write out a sample string
//     console_write("Hello, world!\n");
// 
//     asm volatile("int $0x3");
//     asm volatile("int $0x4");
//     console_write("áñ\n");

    asm volatile("sti");
    //init_timer(50);
    init_keyboard();
    console_write("keyboard initialized\n\n");
    
//     init_mouse();
//     console_write("mouse initialized\n");

    
    init_cli();

    return 0;
}
