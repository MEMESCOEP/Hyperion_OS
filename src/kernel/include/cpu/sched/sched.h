/**
 * @file sched.h
 * @author xyve
 * 
 * Scheduler, tasking, processes or whatever.
 * 
 */
#ifndef SCHED_H
#define SCHED_H

#include <utils/vec.h>
#include <cpu/mm/vmm.h>
#include <cpu/spinlock/spinlock.h>

typedef struct task
{
    registers_t regs;
    pagemap_t * pagemap;
} task_t;

typedef vec_t(task_t *) task_vec_t;

extern task_t current_process;

void sched_init();
void sched_yield();
task_t * sched_next_task();
void sched_create_task(void (*main)());
void sched_save(registers_t * regs);
extern sched_context_switch(registers_t * regs);

#endif