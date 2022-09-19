#include <libc/string.h>
char* strcat(char* dest, const char* src)
{
    int i, k;
	for(i = strlen(dest), k = 0; k < strlen(src); i++, k++)
	{
		dest[i] = src[k];
	}
	dest[i] = '\0';
	return dest;
}