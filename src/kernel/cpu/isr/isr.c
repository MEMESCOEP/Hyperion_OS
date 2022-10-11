#include <cpu/isr/isr.h>
#include <elf/elf.h>

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void* isr_handler_table[256] = { NULL };

void isr_init()
{
    nlog_info("[ISR] >> Initializing ISR...\n");
    isr_install_handler(14, &page_fault);
    nlog_info("[ISR] >> ISR Initialized\n");
}
void page_fault(struct registers *r)
{
	uint64_t faulting_address = 0;
	__asm__ __volatile__("mov %%cr2, %0" : "=r"(faulting_address));
	int present = !(r->error & 0x1);
	int read_write = r->error & 0x2;
	int user_supervisor = r->error & 0x4;
	int reserved = r->error & 0x8;

    printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[91mPANIC\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), __FILE__, __func__, __LINE__);
    printf("Page Fault\n");
    printf("Address: 0x%016lX\nPresent: %s\nRead/Write: %s\nUser/Supervisor: %s\nReserved: %s\n",
    		faulting_address, present ? "P" : "NP", read_write ? "R" : "RW",
			user_supervisor ? "U" : "S", reserved ? "R" : "NR");

    printf("Faulting Address (RIP) = 0x%016lX\n", r->rip);
    printf("R15 = 0x%016lX R14 = 0x%016lX\n", r->r15, r->r14);
    printf("R13 = 0x%016lX R12 = 0x%016lX\n", r->r13, r->r12);
    printf("R11 = 0x%016lX R10 = 0x%016lX\n", r->r11, r->r10);
    printf("R9  = 0x%016lX R8  = 0x%016lX\n", r->r9 , r->r8 );
    printf("RBP = 0x%016lX RSP = 0x%016lX\n", r->rbp, r->rsp);
    printf("RSI = 0x%016lX RDI = 0x%016lX\n", r->rsi, r->rdi);
    printf("RDX = 0x%016lX RCX = 0x%016lX\n", r->rdx, r->rcx);
    printf("RBX = 0x%016lX RAX = 0x%016lX\n", r->rbx, r->rax);
    printf("CS  = 0x%016lX SS  = 0x%016lX\n", r->cs , r->ss );
    printf("CR4 = 0x%016lX CR3 = 0x%016lX\n", read_cr4(), read_cr3());
    printf("CR2 = 0x%016lX CR0 = 0x%016lX\n", read_cr2(), read_cr0());
    printf("RFLAGS = 0x%016lX\n", r->rflags);

    int symbol_num;
	elf_section_header_t * symtab_sh;
	elf_section_header_t * strtab_sh;
	elf_symbol_table_t * symtab;
	const char * strtab;

	symtab_sh = elf_find_section_header(kernel_file_request.response->kernel_file->address, ".symtab");
	strtab_sh = elf_find_section_header(kernel_file_request.response->kernel_file->address, ".strtab");

	symbol_num = symtab_sh->size / symtab_sh->entsize;
	symtab = (void *) (kernel_file_request.response->kernel_file->address + symtab_sh->offset);
	strtab = (void *) (kernel_file_request.response->kernel_file->address + strtab_sh->offset);

	printf("Traceback:\n");
	for (size_t i = 0; i < symbol_num; i++)
	{
		if (symtab[i].name && r->rip > symtab[i].value && r->rip < symtab[i].value + symtab[i].size && ((symtab[i].info) &0xf) == 2)
		{
			printf("\t%s at %016lX\n", strtab + symtab[i].name, r->rip);
		}
	}

    serial_printf("[ISRERR]\n");
    serial_printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[91mPANIC\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), __FILE__, __func__, __LINE__);
    serial_printf("Page Fault\r\n");
    serial_printf("Address: 0x%016lX\r\nPresent: %s\r\nRead/Write: %s\r\nUser/Supervisor: %s\r\nReserved: %s\r\n",
    		faulting_address, present ? "P" : "NP", read_write ? "R" : "RW",
			user_supervisor ? "U" : "S", reserved ? "R" : "NR");

    serial_printf("Faulting Address (RIP) = 0x%016lX\n", r->rip);
    serial_printf("R15 = 0x%016lX R14 = 0x%016lX\n", r->r15, r->r14);
    serial_printf("R13 = 0x%016lX R12 = 0x%016lX\n", r->r13, r->r12);
    serial_printf("R11 = 0x%016lX R10 = 0x%016lX\n", r->r11, r->r10);
    serial_printf("R9  = 0x%016lX R8  = 0x%016lX\n", r->r9 , r->r8 );
    serial_printf("RBP = 0x%016lX RSP = 0x%016lX\n", r->rbp, r->rsp);
    serial_printf("RSI = 0x%016lX RDI = 0x%016lX\n", r->rsi, r->rdi);
    serial_printf("RDX = 0x%016lX RCX = 0x%016lX\n", r->rdx, r->rcx);
    serial_printf("RBX = 0x%016lX RAX = 0x%016lX\n", r->rbx, r->rax);
    serial_printf("CS  = 0x%016lX SS  = 0x%016lX\n", r->cs , r->ss );
    serial_printf("CR4 = 0x%016lX CR3 = 0x%016lX\n", read_cr4(), read_cr3());
    serial_printf("CR2 = 0x%016lX CR0 = 0x%016lX\n", read_cr2(), read_cr0());
    serial_printf("RFLAGS = 0x%016lX\n", r->rflags);

    hlt();
}

void isr_install_handler(uint8_t num, void (*handler)(struct registers *))
{
    isr_handler_table[num] = handler;
}

void isr_uninstall_handler(uint8_t num)
{
    isr_handler_table[num] = 0;
}

void isr_handler(struct registers *r)
{
	void (*handler)(struct registers* r);
    handler = isr_handler_table[r->int_no];

    if(handler != NULL)
    {
        handler(r);
    }
    else 
    {
        printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[91mPANIC\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), __FILE__, __func__, __LINE__);
        printf("%s [%lu]\n", exception_messages[r->int_no], r->error);

        printf("Faulting Address (RIP) = 0x%016lX\n", r->rip);
        printf("R15 = 0x%016lX R14 = 0x%016lX\n", r->r15, r->r14);
        printf("R13 = 0x%016lX R12 = 0x%016lX\n", r->r13, r->r12);
        printf("R11 = 0x%016lX R10 = 0x%016lX\n", r->r11, r->r10);
        printf("R9  = 0x%016lX R8  = 0x%016lX\n", r->r9 , r->r8 );
        printf("RBP = 0x%016lX RSP = 0x%016lX\n", r->rbp, r->rsp);
        printf("RSI = 0x%016lX RDI = 0x%016lX\n", r->rsi, r->rdi);
        printf("RDX = 0x%016lX RCX = 0x%016lX\n", r->rdx, r->rcx);
        printf("RBX = 0x%016lX RAX = 0x%016lX\n", r->rbx, r->rax);
        printf("CS  = 0x%016lX SS  = 0x%016lX\n", r->cs , r->ss );
        printf("CR4 = 0x%016lX CR3 = 0x%016lX\n", read_cr4(), read_cr3());
        printf("CR2 = 0x%016lX CR0 = 0x%016lX\n", read_cr2(), read_cr0());
        printf("RFLAGS = 0x%016lX\n", r->rflags);

        serial_printf("[ISRERR]\n");
        serial_printf("\x1b[90m%02x:%02x:%02x\x1b[0m \x1b[91mPANIC\x1b[0m \x1b[90m%s:%s:%u\x1b[0m ", rtc_get_hours(), rtc_get_minutes(), rtc_get_seconds(), __FILE__, __func__, __LINE__);
        serial_printf("%s [%lu]\n", exception_messages[r->int_no], r->error);

        serial_printf("Faulting Address (RIP) = 0x%016lX\n", r->rip);
        serial_printf("R15 = 0x%016lX R14 = 0x%016lX\n", r->r15, r->r14);
        serial_printf("R13 = 0x%016lX R12 = 0x%016lX\n", r->r13, r->r12);
        serial_printf("R11 = 0x%016lX R10 = 0x%016lX\n", r->r11, r->r10);
        serial_printf("R9  = 0x%016lX R8  = 0x%016lX\n", r->r9 , r->r8 );
        serial_printf("RBP = 0x%016lX RSP = 0x%016lX\n", r->rbp, r->rsp);
        serial_printf("RSI = 0x%016lX RDI = 0x%016lX\n", r->rsi, r->rdi);
        serial_printf("RDX = 0x%016lX RCX = 0x%016lX\n", r->rdx, r->rcx);
        serial_printf("RBX = 0x%016lX RAX = 0x%016lX\n", r->rbx, r->rax);
        serial_printf("CS  = 0x%016lX SS  = 0x%016lX\n", r->cs , r->ss );
        serial_printf("CR4 = 0x%016lX CR3 = 0x%016lX\n", read_cr4(), read_cr3());
        serial_printf("CR2 = 0x%016lX CR0 = 0x%016lX\n", read_cr2(), read_cr0());
        serial_printf("RFLAGS = 0x%016lX\n", r->rflags);

        hlt();
    }
}
