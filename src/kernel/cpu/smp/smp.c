#include <cpu/smp/smp.h>

cpu_t cpus[8];
uint64_t cpu_num;

void cpu_init()
{
    gdt_reload();
    idt_reload();
    cpus[cpu_num].initialized = true;
}

void smp_init()
{
    uint32_t bsp_lapic_id = smp_request.response->bsp_lapic_id;
    uint64_t cpu_count = smp_request.response->cpu_count;

    for (uint64_t i = 0; i < cpu_count; i++)
    {
        if(smp_request.response->cpus[i]->lapic_id != bsp_lapic_id)
        {
            cpu_num = i;
            smp_request.response->cpus[i]->goto_address = cpu_init;
            while(cpus[i].initialized != true);
        }
    }
    
    nlog_info("[SMP] >> SMP Initialized\n");
}