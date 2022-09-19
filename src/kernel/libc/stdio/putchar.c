#include <libc/stdio.h>

/**
 * Prints character to screen
 *
 * @param ch Character to print
 */
int putchar(const char ch)
{
    term_write_char(ch);
}
/**
 * Used by the printf implementation
 * 
 * @param ch Character to print
 */
void putchar_(const char ch)
{
    term_write_char(ch);
}