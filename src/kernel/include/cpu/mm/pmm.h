/**
 * @file pmm.h
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
#ifndef PMM_H
#define PMM_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <libc/math.h>
#include <utils/nlog.h>
#include <kernel.h>

#define PAGE_SIZE 4096

void pmm_init();
void* pmm_alloc(uint64_t size);
void* pmm_allocz(uint64_t size);
void pmm_free(void * ptr, uint64_t size);
void* pmm_realloc(void * ptr, uint64_t old_size, uint64_t new_size);
void pmm_info();

uint64_t pmm_free_pages();

#endif