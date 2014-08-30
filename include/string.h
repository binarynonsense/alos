#ifndef STRING_H
#define STRING_H

#include <sys/types.h>

#if !defined(NULL)
#define NULL ((void*)0)
#endif


// Copy len bytes from src to dest.
void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len);

// Write len copies of val into dest.
void memset(uint8_t *dest, uint8_t val, uint32_t len);

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2);

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src);

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src);

#endif
