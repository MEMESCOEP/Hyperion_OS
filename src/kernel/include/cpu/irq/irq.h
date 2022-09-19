/**
 * @file irq.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/cfenollosa/os-tutorial
 * Resources used:
 *      https://wiki.osdev.org/Interrupt_Descriptor_Table
 *      https://wiki.osdev.org/Interrupts_tutorial
 *      http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html
 * 
 */
#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>
#include <stddef.h>
#include <cpu/isr/isr.h>
#include <cpu/timer/pit.h>
#include <cpu/pic/pic.h>
#include <dev/keyboard.h>
#include <neptunium/neptunium.h>
#include <utils/nlog.h>
#include <dev/mouse.h>

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_init();
void irq_install_handler(uint8_t num, void (*handler)(struct registers *));
void irq_uninstall_handler(uint8_t num);
void irq_handler(struct registers *r);

#endif