#include <cpu/gdt/gdt.h>

/**
 * Initializes GDT
 */
void gdt_init()
{
    nlog_info("[GDT] >> Initializing GDT / TSS...\n");
    tss_t tss_table;
    gdt_table = (gdt_t){

        /* Null */
        {
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b00000000,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        /* 16-Bit Code */
        {
            .limit = 0xFFFF,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10011010,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        /* 16-Bit Data */
        {
            .limit = 0xFFFF,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10010010,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        /* 32-Bit Code */
        {
            .limit = 0xFFFF,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10011010,
            .granularity = 0b11001111,
            .base2 = 0x00
        },
        /* 32-Bit Data */
        {
            .limit = 0xFFFF,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10010010,
            .granularity = 0b11001111,
            .base2 = 0x00
        },
        /* 64-Bit Code */
        {
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10011010,
            .granularity = 0b00100000,
            .base2 = 0x00
        },
        /* 64-Bit Data */
        {
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10010010,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        /* 64-Bit User Code */
        {
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b11110010,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        /* 64-Bit User Data */
        {
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b11111010,
            .granularity = 0b00100000,
            .base2 = 0x00
        },
        /* TSS */
        {
            .limit = ((uint64_t)&tss_table) + sizeof(tss_table),
            .base0 = ((uint64_t)&tss_table),
            .base1 = ((uint64_t)&tss_table) >> 16,
            .access = 0x89,
            .flags = 0x00,
            .base2 = ((uint64_t)&tss_table) >> 24,
            .base3 = ((uint64_t)&tss_table) >> 32,
            .reserved = 0x00
        }

    }; 

    gdt_reload();
    tss_reload();

    nlog_info("[GDT] >> GDT Initialized\n");
    nlog_info("[GDT] >> TSS Initialized\n");
}

void gdt_reload()
{
    gdt_desc_t gdt_descriptor;

    gdt_descriptor.limit = sizeof(gdt_t) - 1;
    gdt_descriptor.base = (uint64_t)&gdt_table;

    __asm__ __volatile__ ("lgdt %0" : : "m"(gdt_descriptor) : "memory");
}
void tss_reload()
{
    __asm__ __volatile__ ("ltr %0" : : "r" ((uint16_t)0x48));
}
