#ifndef CONSOLE_H
#define CONSOLE_H

#include <sys/pio.h>
#include <sys/types.h>

// Write a single character out to the screen.
void console_put(char c);

// Clear the screen to all black.
void console_clear();

void console_move_cursor();

// Output a null-terminated ASCII string to the console.
void console_write(char *c);

#endif // CONSOLE_H
