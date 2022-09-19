/**
 * @file isr.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/cfenollosa/os-tutorial
 * Resources used:
 *      https://wiki.osdev.org/Interrupt_Descriptor_Table
 *      https://wiki.osdev.org/Interrupts_tutorial
 * 
 */
#ifndef ISR_H
#define ISR_H

#include <libc/string.h>
#include <term/term.h>
#include <libc/stdio.h>
#include <neptunium/neptunium.h>
#include <cpu/mm/vmm.h>
#include <cpu/cpu.h>

/* ISRs reserved for CPU exceptions */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr128();

/* Register Structure */
typedef struct registers {
    uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;
	uint64_t int_no;
	uint64_t error;
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
} __attribute__((packed)) registers_t;

void isr_init();
void isr_handler(struct registers *r);
void isr_install_handler(uint8_t num, void (*handler)(struct registers *));

/* Special Exceptions */
void divide_by_zero(struct registers *r);
void debug(struct registers *r);
void breakpoint(struct registers *r);
void page_fault(struct registers *r);

#endif
