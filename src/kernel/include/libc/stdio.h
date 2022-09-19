#ifndef STDIO_H
#define STDIO_H

#include <term/term.h>
#include <stdbool.h>

#include <libc/printf.h>
#include <cpu/spinlock/spinlock.h>

//#include <libc/string.h>

int puts(const char * str);
int putchar(const char ch);
void putchar_(const char ch);


#endif