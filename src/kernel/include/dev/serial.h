/**
 * @file serial.h
 * @author xyve
 * 
 * Resources used:
 *      https://wiki.osdev.org/Serial_Ports
 * 
 */
#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <cpu/cpu.h>
#include <utils/nlog.h>
#include <cpu/spinlock/spinlock.h>

#define PORT 0x3F8

int32_t serial_init();
int32_t serial_received();
char serial_read();
int32_t is_transmit_empty();
int serial_puts(const char * str);
int serial_putchar(const char ch);
int serial_printf(const char* format, ...);


#endif