#include <libc/stdio.h>

void puts(const char * str)
{
    size_t len = strlen(str);
    asm volatile (
        "mov  %1, %%rax\n"
        "mov  %1, %%rdi\n"
        "mov  $0x1, %%ebx\n"
        "mov  $0x4, %%eax\n"
        "int  $0x48\n"
        "mov  $0x1, %%eax\n"
        "int  $0x48\n"
        : "=r"(len)
        : "r"(str)
        : "edx", "ebx", "eax" , "ecx", "memory"
    );
}
