#include <cpu/syscall/syscall.h>

void * syscall_table[] = 
{
    NULL,
    &syscall_write
};

void syscall_init()
{
    nlog_info("[SYSCALL] >> Initializing SYSCALL...\n");
    isr_install_handler(128, &syscall_handler);
    nlog_info("[SYSCALL] >> SYSCALL Initialized\n");
}

void syscall_handler(struct registers *r)
{
	//vmm_switch_pagemap(&kernel_pagemap);
    void (*handler)(struct registers* r);
    handler = syscall_table[r->rax];

    if(handler != NULL)
    {
        handler(r);
    }
    else 
    {
        printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[91mEXCEPTION\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), __FILE__, __func__, __LINE__);
        printf("Unhandled Syscall: %lu\n", r->rax);
        printf("R15 = 0x%016lX\n", r->r15);
        printf("R14 = 0x%016lX\n", r->r14);
        printf("R13 = 0x%016lX\n", r->r13);
        printf("R12 = 0x%016lX\n", r->r12);
        printf("R11 = 0x%016lX\n", r->r11);
        printf("R10 = 0x%016lX\n", r->r10);
        printf("R9  = 0x%016lX\n", r->r9);
        printf("R8  = 0x%016lX\n", r->r8);
        printf("RBP = 0x%016lX\n", r->rbp);
        printf("RDI = 0x%016lX\n", r->rdi);
        printf("RSI = 0x%016lX\n", r->rsi);
        printf("RDX = 0x%016lX\n", r->rdx);
        printf("RCX = 0x%016lX\n", r->rcx);
        printf("RBX = 0x%016lX\n", r->rbx);
        printf("RAX = 0x%016lX\n", r->rax);
        printf("RIP = 0x%016lX\n", r->rip);
        printf("CS  = 0x%016lX\n", r->cs);
        printf("RFLAGS = 0x%016lX\n", r->rflags);
        printf("RSP = 0x%016lX\n", r->rsp);
        printf("SS  = 0x%016lX\n", r->ss);
    }
	//vmm_switch_pagemap(other_pagemap);
}