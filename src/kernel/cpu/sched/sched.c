#include <cpu/sched/sched.h>

bool schedule;

task_vec_t tasks;
lock_t tasking_lock;
uint64_t cur_task = 0;
task_t current_process;

#define STACK_SIZE 0x40000
void sched_init()
{
	nlog_info("[SCHEDULER] >> Initializing SCHEDULER...\n");
	vec_init(&tasks);
	nlog_info("[SCHEDULER] >> Scheduler Initialized\n");
}
void sched_start()
{
	schedule = true;
}
void sched_yield(struct registers * state)
{
	spinlock_lock(tasking_lock);
	cli();

	task_t * switch_task;
	if(cur_task > 0)
		sched_save(state);

	switch_task = sched_next_task();

	state->rax = switch_task->state.rax;
	state->rbx = switch_task->state.rbx;
	state->rcx = switch_task->state.rcx;
	state->rdx = switch_task->state.rdx;
	state->rsi = switch_task->state.rsi;
	state->rdi = switch_task->state.rdi;
	state->rbp = switch_task->state.rbp;
	state->rsp = switch_task->state.rsp;
	state->r8 = switch_task->state.r8;
	state->r9 = switch_task->state.r9;
	state->r10 = switch_task->state.r10;
	state->r11 = switch_task->state.r11;
	state->r12 = switch_task->state.r12;
	state->r13 = switch_task->state.r13;
	state->r14 = switch_task->state.r14;
	state->r15 = switch_task->state.r15;
	state->rip = switch_task->state.rip;

	sti();
	spinlock_unlock(tasking_lock);
}
void sched_save(struct registers * state)
{
	spinlock_lock(tasking_lock);
	task_t * tsk = tasks.data[cur_task];
	cli();


	tsk->state.rax = state->rax;
	tsk->state.rbx = state->rbx;
	tsk->state.rcx = state->rcx;
	tsk->state.rdx = state->rdx;
	tsk->state.rsi = state->rsi;
	tsk->state.rdi = state->rdi;
	tsk->state.rbp = state->rbp;
	tsk->state.rsp = state->rsp;
	tsk->state.r8 = state->r8;
	tsk->state.r9 = state->r9;
	tsk->state.r10 = state->r10;
	tsk->state.r11 = state->r11;
	tsk->state.r12 = state->r12;
	tsk->state.r13 = state->r13;
	tsk->state.r14 = state->r14;
	tsk->state.r15 = state->r15;
	tsk->state.rip = state->rip;


	sti();
	spinlock_unlock(tasking_lock);
}
task_t * sched_next_task()
{
	spinlock_lock(tasking_lock);
	cli();

	if(cur_task == (tasks.length - 1))
		cur_task = 0;
	else
		cur_task++;
	
	sti();
	spinlock_unlock(tasking_lock);
	return tasks.data[cur_task];
}
void sched_create_task(void (*main)())
{
	spinlock_lock(tasking_lock);
	cli();

	task_t * tsk = kmalloc(sizeof(task_t));

	void * stack_phys = pmm_allocz(STACK_SIZE / PAGE_SIZE);
	void * stack = stack_phys + STACK_SIZE + hhdm_request.response->offset;

	tsk->state.rax = 0;
	tsk->state.rbx = 0;
	tsk->state.rcx = 0;
	tsk->state.rdx = 0;
	tsk->state.rsi = 0;
	tsk->state.rdi = 0;
	tsk->state.rsp = (uint64_t)stack;
	tsk->state.r8 = 0;
	tsk->state.r9 = 0;
	tsk->state.r10 = 0;
	tsk->state.r11 = 0;
	tsk->state.r12 = 0;
	tsk->state.r13 = 0;
	tsk->state.r14 = 0;
	tsk->state.r15 = 0;

	tsk->state.rip = (uint64_t) main;
	tsk->pmap = vmm_new_pagemap();

	vec_push(&tasks, tsk);

	sti();
	spinlock_unlock(tasking_lock);
}