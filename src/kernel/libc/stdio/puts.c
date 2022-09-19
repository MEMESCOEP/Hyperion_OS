#include <libc/stdio.h>

/**
 * Prints string to screen
 *
 * @param str String to print
 */
int puts(const char * str)
{
    term_write_str(str, strlen(str));
}