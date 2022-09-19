#include <fs/ustar.h>

size_t ustar_octal_to_int(const unsigned char* octal_str, uint8_t size)
{
	size_t ret = 0;
	while (size-- > 0)
	{
		ret *= 8;
		ret += *octal_str - '0';
		octal_str++;
	}
	return ret;
}