/**
 * @file idt.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/cfenollosa/os-tutorial
 * Resources used:
 *      https://wiki.osdev.org/Interrupt_Descriptor_Table
 *      https://wiki.osdev.org/Interrupts_tutorial
 * 
 */
#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <cpu/isr/isr.h>
#include <cpu/irq/irq.h>
#include <neptunium/neptunium.h>
#include <utils/nlog.h>

typedef struct idt_entry
{
    uint16_t base0;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags; 
    uint16_t base1;
    uint32_t base2;
    uint32_t zero;

} __attribute__((packed)) idt_entry_t;

typedef struct idt_desc
{
    uint16_t limit;
    uint64_t base;

} __attribute__((packed)) idt_desc_t;

idt_entry_t idt_table[256];

extern void idt_load(idt_desc_t * idt_ptr);

void idt_reload();
void idt_set_gate(uint16_t num, uint64_t base, uint16_t selector, uint8_t flags);
void idt_init();

#endif