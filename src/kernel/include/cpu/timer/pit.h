/**
 * @file pit.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/0Nera/SynapseOS
 * 
 * Resources used:
 *      https://wiki.osdev.org/Programmable_Interval_Timer
 *      http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html
 * 
 */
#ifndef PIT_H
#define PIT_H

#include <stddef.h>
#include <stdint.h>
#include <cpu/isr/isr.h>
#include <utils/nlog.h>

#define INPUT_CLOCK_FREQUENCY 1193180

#define TIMER_COMMAND 0x43
#define TIMER_DATA    0x40
#define TIMER_OCW     0x36 

#define TICKS_PER_SECOND 20

void pit_init(int32_t hz);
void pit_handler(struct registers* regs);
uint64_t pit_get_ticks();

#endif