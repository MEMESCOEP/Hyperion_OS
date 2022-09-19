#include <neptunium/neptunium.h>

void kernel_panic(const char* format, const char* file, const char* function, uint32_t line, ...)
{
    printf("\x1b[2J\x1b[H");
    printf("[========== \x1b[91mKERNEL PANIC\x1b[0m ==========]\n");
    va_list list;
	va_start(list, format);
    printf("PANIC TIME: %02x:%02x:%02x\n", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds());
    printf("FUNCTION: %s:%s:%u\n", file, function, line);
    printf("MSG: %s", format);
    //printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[91mPANIC\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), file, function, line);
    serial_printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[91mPANIC\x1b[0m \x1b[90m%s:%s:%u\x1b[0m %s\n", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), file, function, line, format);
    //vprintf(format, list);
    va_end(list);
    for(;;);
}