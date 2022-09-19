/**
 * @file pic.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/ilobilo/kernelv2
 * 
 * Resources used:
 *      https://wiki.osdev.org/PIC
 * 
 */
#ifndef PIC_H
#define PIC_H

#include <stddef.h>
#include <stdint.h>
#include <cpu/cpu.h>
#include <utils/nlog.h>

#define PIC1		0x20        /* Master */
#define PIC2		0xA0        /* Slave */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI		0x20		/* End-of-interrupt command code */

#define PIC_READ_IRR 0x0a       /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR 0x0b       /* OCW3 irq service next CMD read */

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04    /* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08	/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C	/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */
 
void pic_send_eoi(uint8_t irq);
void pic_disable();
void pic_init();

#endif