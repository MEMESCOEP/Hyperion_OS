/**
 * @file nlog.h
 * @author xyve
 * 
 * Neptunium logging library
 * 
 */
#ifndef NLOG_H
#define NLOG_H

#include <libc/stdio.h>
#include <rtc/rtc.h>

#define nlog_debug(format, ...) nlog(0, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define nlog_warn(format, ...) nlog(1, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define nlog_error(format, ...) nlog(2, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)
#define nlog_info(format, ...) nlog(3, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

void nlog(unsigned char type, const char* file, const char* function, unsigned int line, const char* restrict format, ...);

#endif