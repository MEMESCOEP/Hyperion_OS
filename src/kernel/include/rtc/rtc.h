/**
 * @file rtc.h
 * @author xyve
 * 
 * Resources used:
 *      https://wiki.osdev.org/CMOS
 *      github copilot :skull:
 * 
 */
#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <stddef.h>
#include <cpu/cpu.h>
#include <cpu/irq/irq.h>
#include <neptunium/neptunium.h>
#include <cpu/pic/pic.h>
#include <utils/nlog.h>

char * weekday;
char * month_str;
const char* rtc_months[14];

void rtc_init();
uint8_t rtc_get_seconds();
uint8_t rtc_get_minutes();
uint8_t rtc_get_hours();
uint8_t rtc_get_weekday();
uint8_t rtc_get_day();
uint8_t rtc_get_month();
uint8_t rtc_get_year();
uint8_t rtc_get_century();
char* rtc_get_month_str();
char* rtc_get_weekday_str();

#endif