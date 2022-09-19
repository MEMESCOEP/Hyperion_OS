#include <rtc/rtc.h>

const char* rtc_days[7] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};
const char* rtc_months[12] = {
	"",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};
void rtc_init()
{
    cli();			            // disable interrupts
    outb(0x70, 0x8B);		    // select register B, and disable NMI
    int8_t prev = inb(0x71);	// read the current value of register B
    outb(0x70, 0x8B);		    // set the index again (a read will reset the index to register D)
    outb(0x71, prev | 0x40);	// write the previous value ORed with 0x40. This turns on bit 6 of register B
    sti();
    nlog_info("[RTC] >> RTC Initialized\n");
}

uint8_t rtc_get_seconds()
{
    outb(0x70, 0x00);
    return inb(0x71);
}
uint8_t rtc_get_minutes()
{
    outb(0x70, 0x02);
    return inb(0x71);
}
uint8_t rtc_get_hours()
{
    outb(0x70, 0x04);
    return inb(0x71);
}
uint8_t rtc_get_weekday()
{
    outb(0x70, 0x06);
    return inb(0x71);
}
char* rtc_get_weekday_str()
{
    return rtc_days[rtc_get_weekday()];
}
uint8_t rtc_get_day()
{
    outb(0x70, 0x07);
    return inb(0x71);
}
uint8_t rtc_get_month()
{
    outb(0x70, 0x08);
    return inb(0x71);
}
char* rtc_get_month_str()
{
    return rtc_months[rtc_get_month()];
}
uint8_t rtc_get_year()
{
    outb(0x70, 0x09);
    return inb(0x71);
}
uint8_t rtc_get_century()
{
    outb(0x70, 0x32);
    return inb(0x71);
}