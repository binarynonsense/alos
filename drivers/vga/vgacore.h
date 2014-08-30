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
--  file: vgacore.h                                                        --
--                                                                         --
--                                                                         --
--  This project is based on the kernel tutorials by JamesM                --
--  http://www.jamesmolloy.co.uk/tutorial_html/index.html                  --
--  and Brandon F http://www.osdever.net/bkerndev/index.php                --
--  And the really helpful OSDev.org wiki and forums                       --
-----------------------------------------------------------------------------
--                      last update: 03 May 2009                           --
---------------------------------------------------------------------------*/

#define   VGA_AC_INDEX          0x3C0
#define   VGA_AC_WRITE          0x3C0
#define   VGA_AC_READ           0x3C1
#define   VGA_MISC_WRITE        0x3C2
#define   VGA_SEQ_INDEX         0x3C4
#define   VGA_SEQ_DATA          0x3C5
#define   VGA_DAC_READ_INDEX    0x3C7
#define   VGA_DAC_WRITE_INDEX   0x3C8
#define   VGA_DAC_DATA          0x3C9
#define   VGA_MISC_READ         0x3CC
#define   VGA_GC_INDEX          0x3CE
#define   VGA_GC_DATA           0x3CF
#define   VGA_CRTC_INDEX        0x3D4      /* 0x3B4 monochrome? */
#define   VGA_CRTC_DATA         0x3D5      /* 0x3B5 monochrome? */
#define   VGA_INSTAT_READ       0x3DA
#define   VGA_NUM_SEQ_REGS      5
#define   VGA_NUM_CRTC_REGS     25
#define   VGA_NUM_GC_REGS       9
#define   VGA_NUM_AC_REGS       21
#define   VGA_NUM_REGS          (1+VGA_NUM_SEQ_REGS+VGA_NUM_CRTC_REGS+VGA_NUM_GC_REGS+VGA_NUM_AC_REGS)

//for mode x registers

/* CRT controller registers */
#define H_TOTAL             0x00
#define H_DISPLAY_END       0x01
#define H_BLANK_START       0x02
#define H_BLANK_END         0x03
#define H_RETRACE_START     0x04
#define H_RETRACE_END       0x05
#define V_TOTAL             0x06
#define OVERFLOW            0x07
#define MAX_SCAN_LINE       0x09
#define V_RETRACE_START     0x10
#define V_RETRACE_END       0x11
#define V_DISPLAY_END       0x12
#define OFFSET              0x13
#define UNDERLINE_LOCATION  0x14
#define V_BLANK_START       0x15
#define V_BLANK_END         0x16
#define MODE_CONTROL        0x17


#define MAP_MASK            0x02      /* Sequence controller registers */
#define MEMORY_MODE         0x04

//MODES

#define TEXT_MODE 0
#define G320x200x256 1
#define G320x240x256 2  // mode x

/* macro to write a word to a port */
#define word_out(port,register,value) \
  outw(port,(((word)value<<8) + register))

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;
