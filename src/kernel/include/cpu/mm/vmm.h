/**
 * @file vmm.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/NSG650/Polaris
 *      https://github.com/vlang/vinix
 * 
 * Resources used:
 *      https://wiki.osdev.org/Memory_management
 * 
 */
#ifndef VMM_H
#define VMM_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <libc/math.h>
#include <utils/nlog.h>
#include <cpu/mm/pmm.h>
#include <cpu/isr/isr.h>

#define PAGE_SIZE 4096
#define HIGHER_HALF_ADDR 0xffff800000000000
#define KERNEL_OFFS_ADDR 0xffffffff80000000

typedef struct pagemap
{
    uint64_t * top_level;
} pagemap_t;

extern pagemap_t kernel_pagemap;

void vmm_init();
void vmm_switch_pagemap(pagemap_t * pagemap);
void vmm_map_page(pagemap_t * pagemap, uint64_t virtual_address, uint64_t physical_address, uint64_t flags);
pagemap_t * vmm_new_pagemap();

#endif