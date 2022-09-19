#ifndef SMP_H
#define SMP_H

#include <kernel.h>
#include <neptunium/neptunium.h>
#include <utils/nlog.h>
#include <cpu/cpu.h>
#include <stddef.h>

void smp_init();

#define read_gs(offset) \
({ \
    uint64_t value; \
    __asm__ __volatile__("movq %%gs:[" #offset "], %0" : "=r"(value) : : "memory"); \
    value; \
})

#endif