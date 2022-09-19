#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <stdbool.h>
#include <libc/liballoc.h>

char * itoa(int in, char* buffer, int base);
int atoi(const char * str);

#endif