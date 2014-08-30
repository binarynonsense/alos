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
--  file: mouse.c                                                          --
--                                                                         --
--                                                                         --
--  This project is based on the kernel tutorials by JamesM                --
--  http://www.jamesmolloy.co.uk/tutorial_html/index.html                  --
--  and Brandon F http://www.osdever.net/bkerndev/index.php                --
--  And the really helpful OSDev.org wiki and forums                       --
-----------------------------------------------------------------------------
--                      last update: 03 May 2009                           --
---------------------------------------------------------------------------*/

//reference http://forum.osdev.org/viewtopic.php?t=10247
#include <kernel/isr.h>
#include <drivers/mouse.h>
#include <sys/pio.h>
//#include <drivers/console.h>//only for tests - will delete it

unsigned char mouse_cycle=0;     //unsigned char
unsigned char mouse_byte[3];    //unsigned char
char g_mouse_delta_x=0;         //signed char
char g_mouse_delta_y=0;         //signed char

inline void mouse_wait(unsigned char a_type) //unsigned char
{
  unsigned int _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

inline void mouse_write(unsigned char a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  outb(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  outb(0x60, a_write);
}

unsigned char mouse_read()
{
  //Get's response from mouse
  mouse_wait(0);
  return inb(0x60);
}

///////////////////////

static void mouse_callback(registers_t regs)
{
    
    switch(mouse_cycle)
  {
    case 0:
      mouse_byte[0]=inb(0x60);
      mouse_cycle++;
      break;
    case 1:
      mouse_byte[1]=inb(0x60);
      mouse_cycle++;
      break;
    case 2:
      mouse_byte[2]=inb(0x60);
      g_mouse_delta_x=mouse_byte[1];
      g_mouse_delta_y=mouse_byte[2];
      mouse_cycle=0;
      //console_write_hex((int)g_mouse_delta_x);
      //console_write_hex((int)g_mouse_delta_y);
      break;
  }

}

void init_mouse()
{
    unsigned char _status;  //unsigned char

    //Enable the auxiliary mouse device
    mouse_wait(1);
    outb(0x64, 0xA8);
    
    //Enable the interrupts
    mouse_wait(1);
    outb(0x64, 0x20);
    mouse_wait(0);
    _status=(inb(0x60) | 2);
    mouse_wait(1);
    outb(0x64, 0x60);
    mouse_wait(1);
    outb(0x60, _status);
    
    //Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read();  //Acknowledge
    
    //Enable the mouse
    mouse_write(0xF4);
    mouse_read();  //Acknowledge
    
    //Setup the mouse handler
    //irq_install_handler(12, mouse_handler);
    // Firstly, register our keyboard callback.
    register_interrupt_handler(IRQ12, &mouse_callback);

}

