//KEYBOARD by AL

#ifndef KEYBOARD_H
#define KEYBOARD_H


extern unsigned char g_kbd_key;

unsigned char keyboard_scancode_to_ascii(unsigned char scancode);

void init_keyboard();

#endif
