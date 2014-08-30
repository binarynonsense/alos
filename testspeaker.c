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
--  file: testspeaker.c                                                    --
--                                                                         --
--                                                                         --
--  This project is based on the kernel tutorials by JamesM                --
--  http://www.jamesmolloy.co.uk/tutorial_html/index.html                  --
--  and Brandon F http://www.osdever.net/bkerndev/index.php                --
--  And the really helpful OSDev.org wiki and forums                       --
-----------------------------------------------------------------------------
--                      last update: 30 Aug 2014                           --
---------------------------------------------------------------------------*/

//ref http://www.gamedev.net/reference/articles/article442.asp

#define SPEAKER_PORT 0x61;
#define PIT_CONTROL = 0x43;
#define PIT_CHANNEL_2 = 0x42;

#include <sys/types.h>
#include <kernel/timer.h>
#include <drivers/console.h>

void sound(uint32_t frequency){

    uint32_t divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0xB6);//

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x42, l);
    outb(0x42, h);

//Connect the speaker to the PIT
//Port[SPEAKER_PORT] := Port[SPEAKER_PORT] or 3;
uint8_t speakerport = inb(0x61);
speakerport = speakerport | 3;
outb(0x61,speakerport);
}

void stop_sound(){
uint8_t speakerport = inb(0x61);
speakerport = speakerport & 0xFC;
outb(0x61,speakerport);
}

void testspeaker(){
console_write("\n\ntesting pc speaker");
init_timer(1000);
sound(100);
sleep(1);
stop_sound();
sound(50);
sleep(1);
stop_sound();
console_write("\nend\n\n");
}

