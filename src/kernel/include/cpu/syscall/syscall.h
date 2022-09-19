/**
 * @file syscall.h
 * @author xyve
 * 
 * Syscall implementation file.
 * 
 */

#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>
#include <cpu/isr/isr.h>
#include <term/term.h>
#include <cpu/cpu.h>
#include <kernel.h>
#include <cpu/sched/sched.h>

extern void syscall_entry();

void syscall_init();
void syscall_handler(struct registers *r);

// RAX 1
void syscall_write(struct registers *r);
void syscall_write_test(const char* str);

#endif