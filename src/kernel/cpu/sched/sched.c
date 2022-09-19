#include <cpu/sched/sched.h>

task_vec_t tasks;
lock_t tasking_lock;
uint64_t cur_task = 0;
task_t current_process;

void sched_init()
{
	vec_init(&tasks);
	nlog_info("[SCHEDULER] >> Scheduler Initialized\n");
}
void sched_yield()
{
	spinlock_lock(tasking_lock);

	task_t * tsk = sched_next_task();
	current_process = *tsk;
	vmm_switch_pagemap(tsk->pagemap);
	sched_context_switch(&tsk->regs);

	spinlock_unlock(tasking_lock);
}
void sched_save(registers_t * regs)
{
	spinlock_lock(tasking_lock);
	
	task_t * tsk = tasks.data[cur_task];
	tsk->regs.rax = regs->rax;
	tsk->regs.rbx = regs->rbx;
	tsk->regs.rcx = regs->rcx;
	tsk->regs.rdx = regs->rdx;
	tsk->regs.rsi = regs->rsi;
	tsk->regs.rdi = regs->rdi;
	tsk->regs.rbp = regs->rbp;
	tsk->regs.rsp = regs->rsp;
	tsk->regs.r8  = regs->r8 ;
	tsk->regs.r9  = regs->r9 ;
	tsk->regs.r10 = regs->r10;
	tsk->regs.r11 = regs->r11;
	tsk->regs.r12 = regs->r12;
	tsk->regs.r13 = regs->r13;
	tsk->regs.r14 = regs->r14;
	tsk->regs.r15 = regs->r15;
	tsk->regs.rip = regs->rip;
	
	spinlock_unlock(tasking_lock);
}
task_t * sched_next_task()
{
	spinlock_lock(tasking_lock);

	if(cur_task >= tasks.length || cur_task == 0)
		cur_task = 0;
	else
		cur_task++;

	spinlock_unlock(tasking_lock);
	return tasks.data[cur_task];
}
void sched_create_task(void (*main)())
{
	spinlock_lock(tasking_lock);
	task_t * tsk = kmalloc(sizeof(task_t));

	tsk->regs.rax = 0;
	tsk->regs.rbx = 0;
	tsk->regs.rcx = 0;
	tsk->regs.rdx = 0;
	tsk->regs.rsi = 0;
	tsk->regs.rdi = 0;
	tsk->regs.rbp = 0;
	tsk->regs.rsp = pmm_allocz(1);
	tsk->regs.r8 = 0;
	tsk->regs.r9 = 0;
	tsk->regs.r10 = 0;
	tsk->regs.r11 = 0;
	tsk->regs.r12 = 0;
	tsk->regs.r13 = 0;
	tsk->regs.r14 = 0;
	tsk->regs.r15 = 0;

	tsk->regs.rip = (uint64_t) main;
	tsk->pagemap = vmm_new_pagemap();

	vec_push(&tasks, tsk);

	spinlock_unlock(tasking_lock);
}