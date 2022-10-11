/**
 * @file neptunium.h
 * @author xyve
 * 
 * Just some random stuff to make my life easier
 * 
 */
#ifndef NEPTUNIUM_H
#define NEPTUNIUM_H

#include <libc/string.h>
#include <libc/stdio.h>
#include <dev/serial.h>
#include <stdarg.h>
#include <limine.h>

#define cli() __asm__ __volatile__("cli");
#define sti() __asm__ __volatile__("sti");
#define hlt() __asm__ __volatile__("hlt");

#define panic(format, ...) kernel_panic(format, __FILE__, __func__, __LINE__, ##__VA_ARGS__);
#define assert(condition) if(!(condition)) { kernel_panic("Assertion failure", __FILE__, __func__, __LINE__, 0); }

/* Major.Minor.Patch */
#define VERSION "6.9.420"
/*
    Development Status:
        prototype - Literally broken 💀
        alpha - Probably doesn't work very well
        beta - Has a lot of bugs, but works most of the time
        release_candidate - Mostly stable
        release - Extremely stable
*/
#define STATUS "PROTOTYPE"

/* Month + Day + Year */
#define BUILD "10_07_22"

void kernel_panic(const char* format, const char* file, const char* function, uint32_t line, ...);
extern void reset();
extern void interrupt_test();

#endif
