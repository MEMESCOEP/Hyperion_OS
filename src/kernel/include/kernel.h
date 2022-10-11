/**
 * @file kernel.h
 * @author xyve
 * 
 * Yes, this is about the extent of code I was able to write myself without anyone's help (joke)
 * 
 */
#ifndef KERNEL_H
#define KERNEL_H

#include <cpu/mm/vmm.h>

/* All of these are defined in 'kernel.c' */
extern volatile struct limine_kernel_address_request kernel_address_request;
extern volatile struct limine_hhdm_request hhdm_request;
extern volatile struct limine_memmap_request memmap_request;
extern volatile struct limine_terminal_request terminal_request;
extern volatile struct limine_rsdp_request rsdp_request;
extern volatile struct limine_smp_request smp_request;
extern volatile struct limine_module_request module_request;
extern volatile struct limine_stack_size_request stack_size_request;
extern volatile struct limine_framebuffer_request framebuffer_request;
extern volatile struct limine_kernel_file_request kernel_file_request;

#endif
