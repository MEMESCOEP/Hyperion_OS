#ifndef STRING_H
#define STRING_H

#include <stddef.h>

char* strcat(char* dest, const char* src);

int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t len);

char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t len);

size_t strlen(const char* str);

char* strrev(char* str);

extern void* memset(void* dest, int val, size_t len);
extern void* memcpy(void* dest, const void* src, size_t len);
extern void* memmove(void* dest, const void* src, size_t len);
extern int memcmp(const void* dest, const void* src, size_t len);

#endif