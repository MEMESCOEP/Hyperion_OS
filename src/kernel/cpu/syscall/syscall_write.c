#include <cpu/syscall/syscall.h>

void syscall_write(struct registers *r)
{
    term_write_str((const char*)(r->rsi + module_request.response->modules[0]->address), (size_t)r->rdx);
}
void syscall_write_test(const char* str)
{
	vmm_switch_pagemap(&kernel_pagemap);
    term_write_str(str, strlen(str));
	vmm_switch_pagemap(current_process.pagemap);
}