#include <libc/string.h>
int strncmp(const char* s1, const char* s2, size_t len)
{    
    do
    {
        if(*s1 != *s2++)
            return (*(unsigned char *)s1 - *(unsigned char *)--s2);
        if (*s1++ == '\0')
            break;

    } 
    while (--len != 0);
    return 0;
}