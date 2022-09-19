#include <utils/nlog.h>

void nlog
(
    unsigned char type,
    const char* file,
    const char* function,
    unsigned int line,
    const char* restrict format,
    ...
)
{
	va_list list;
	va_start(list, format);
	switch (type)
	{
    case 0:
		printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[32m[DEBUG]\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), file, function, line);
		vprintf(format, list);
		break;
	case 1:
		printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[95m[WARN]\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), file, function, line);
		vprintf(format, list);
		break;
	case 2:
		printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[91m[ERROR]\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), file, function, line);
		vprintf(format, list);
		break;
	case 3:
		printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[36m[INFO]\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), file, function, line);
		vprintf(format, list);
		break;
	default:
		break;
	}
	va_end(list);
}