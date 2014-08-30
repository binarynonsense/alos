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
--  file: cli.c                                                            --
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
#include <stdio.h>
#include <string.h>

#include "../testvga.h"
#include "../testsleep.h"
#include "../testspeaker.h"

//main reference:http://www.brokenthorn.com/Resources/OSDev19.html

//command line interface

void cli_print_prompt () {
    console_write("root@ALOS:# ");
}

extern uint8_t cursor_x;
extern uint8_t cursor_y;
void cli_get_cmd (char* buf, int n) {

    cli_print_prompt ();

    char key = 0;
    int bufChar;

    // get command string
    int i=0;
    while ( i < n ) {

        // buffer the next char
        bufChar = 1;

        // grab next char
        key = getchar ();

        // end of command if enter is pressed
        if (key==0x1c)//enter
            break;

        if (key==0xe) {// backspace

            // dont buffer this char
            bufChar = 0;

            if (i > 0) {

                // go back one char
                int x,y;
                if (cursor_x>0){
                    cursor_x--;
                    console_move_cursor();
                    
                }else {//go one line up
                    cursor_y--;
                    cursor_x=79;
                    console_move_cursor();
                    
                }
                //erase the character from screen
                x=cursor_x;
                y=cursor_y;
                console_put (' ');
                cursor_x=x;
                cursor_y=y;
                console_move_cursor();
                
                // go back one char in cmd buf
                i--;
            }
        }

        // only add the char if it is to be buffered
        if (bufChar) {

            // convert key to an ascii char and put it in buffer
            //console_write_hex (key);
            char c = keyboard_scancode_to_ascii(key);
            if (c != 0) { //insure its an ascii char
                console_put (c);
                buf [i++] = c;
            }
        }

        // wait for next key
        //sleep (10);
    }

    // null terminate the string
    buf [i] = '\0';
}

//command parser
int cli_run_cmd (char* cmd_buf) {

    //! exit command
    if (strcmp (cmd_buf, "exit") == 0) {
        return 1;
    }

    //! clear screen
    else if (strcmp (cmd_buf, "cls") == 0) {
        console_clear();
    }

    //! help
    else if (strcmp (cmd_buf, "help") == 0) {

        console_write("\n\navailable commands:\n\n");
        console_write("cls -> clean screen\n");
        console_write("sleep -> run a test for the sleep function\n");
        console_write("startx -> init graphical gui\n\n");
    }
    
    //start vga mode
    else if (strcmp (cmd_buf, "startx") == 0) {

        testvga();
    }
    
    //start sleep test
    else if (strcmp (cmd_buf, "sleep") == 0) {

        testsleep();
    }

    //start pc speaker test
    else if (strcmp (cmd_buf, "speaker") == 0) {

        testspeaker();
    }

    //! invalid command
    else {
        console_write("\n\ncomando no valido\n\n");
    }

    return 0;
}

void init_cli () {
    
    console_write("                  ****************************************\n");
    console_write("                  ***                                  ***\n");
    console_write("                  ***         Welcome to ALOS          ***\n");
    console_write("                  ***                                  ***\n");
    console_write("                  ****************************************\n");
    console_write("\n\n\n");

    //! command buffer
    char    cmd_buf [100];

    while (1) {

        //! get command
        cli_get_cmd (cmd_buf, 98);
        //! run command
        if (cli_run_cmd (cmd_buf) == 1)
            break;
    }
}
