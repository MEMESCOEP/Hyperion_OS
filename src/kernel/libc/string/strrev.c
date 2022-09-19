#include <libc/string.h>
char* strrev(char* str)
{
	char temp;
	int i, j, n;
	n = strlen(str);

	for (i = 0, j = n - 1; i < j; ++i, --j) {
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
	}
	return str;
}