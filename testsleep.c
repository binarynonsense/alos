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
--  file: testsleep.c                                                      --
--                                                                         --
--                                                                         --
--  This project is based on the kernel tutorials by JamesM                --
--  http://www.jamesmolloy.co.uk/tutorial_html/index.html                  --
--  and Brandon F http://www.osdever.net/bkerndev/index.php                --
--  And the really helpful OSDev.org wiki and forums                       --
-----------------------------------------------------------------------------
--                      last update: 03 May 2009                           --
---------------------------------------------------------------------------*/

#include <kernel/timer.h>
#include <drivers/console.h>

#include "testsleep.h"


void testsleep(){
    
    console_write("\n\ntesting sleep() function");
    console_write("\n10 sleeps of 1 sec\n\n");
    init_timer(1000);
    int i;
    for(i=1;i<=10;i++){
        sleep(1);
        console_write("second number: ");
        console_write_dec(i);
        console_write("\n");
    }
    console_write("\n");
    
}
