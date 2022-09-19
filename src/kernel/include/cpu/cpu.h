/**
 * @file cpu.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/ilobilo/kernel
 *      https://github.com/vlang/vinix
 * Resources used:
 *      https://en.wikipedia.org/wiki/CPUID
 * 
 */
#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

// Set code into the code variable which just sets the eax register to whatever the code is depending on what you wanna get
// Setting it to 0 will get the vendor string (why the hell does this works I have no clue, welcome to programming)

typedef struct cpu
{
    uint64_t id;
    volatile bool initialized;
} __attribute__((packed)) cpu_t;


inline bool cpuid(uint32_t leaf, uint32_t subleaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    uint32_t cpuid_max;
    __asm__ __volatile__ ("cpuid"
                          : "=a" (cpuid_max)
                          : "a" (leaf & 0x80000000)
                          : "ebx", "ecx", "edx");
    if (leaf > cpuid_max)
        return false;
    __asm__ __volatile__ ("cpuid"
                          : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
                          : "a" (leaf), "c" (subleaf));
    return true;
}

inline void outb(uint16_t port, uint8_t value) {
    __asm__ __volatile__ ("outb %%al, %1"  : : "a" (value), "Nd" (port) : "memory");
}

inline void outw(uint16_t port, uint16_t value) {
    __asm__ __volatile__ ("outw %%ax, %1"  : : "a" (value), "Nd" (port) : "memory");
}

inline void outd(uint16_t port, uint32_t value) {
    __asm__ __volatile__ ("outl %%eax, %1" : : "a" (value), "Nd" (port) : "memory");
}

inline uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ __volatile__ ("inb %1, %%al"  : "=a" (value) : "Nd" (port) : "memory");
    return value;
}

inline uint16_t inw(uint16_t port) {
    uint16_t value;
    __asm__ __volatile__ ("inw %1, %%ax"  : "=a" (value) : "Nd" (port) : "memory");
    return value;
}

inline uint32_t ind(uint16_t port) {
    uint32_t value;
    __asm__ __volatile__ ("inl %1, %%eax" : "=a" (value) : "Nd" (port) : "memory");
    return value;
}

inline void mmoutb(uintptr_t addr, uint8_t value) {
    __asm__ __volatile__ (
        "movb %1, (%0)"
        :
        : "r" (addr), "ir" (value)
        : "memory"
    );
}

inline void mmoutw(uintptr_t addr, uint16_t value) {
    __asm__ __volatile__ (
        "movw %1, (%0)"
        :
        : "r" (addr), "ir" (value)
        : "memory"
    );
}

inline void mmoutd(uintptr_t addr, uint32_t value) {
    __asm__ __volatile__ (
        "movl %1, (%0)"
        :
        : "r" (addr), "ir" (value)
        : "memory"
    );
}

inline void mmoutq(uintptr_t addr, uint64_t value) {
    __asm__ __volatile__ (
        "movq %1, (%0)"
        :
        : "r" (addr), "r" (value)
        : "memory"
    );
}

inline uint8_t mminb(uintptr_t addr) {
    uint8_t ret;
    __asm__ __volatile__ (
        "movb (%1), %0"
        : "=r" (ret)
        : "r"  (addr)
        : "memory"
    );
    return ret;
}

inline uint16_t mminw(uintptr_t addr) {
    uint16_t ret;
    __asm__ __volatile__ (
        "movw (%1), %0"
        : "=r" (ret)
        : "r"  (addr)
        : "memory"
    );
    return ret;
}

inline uint32_t mmind(uintptr_t addr) {
    uint32_t ret;
    __asm__ __volatile__ (
        "movl (%1), %0"
        : "=r" (ret)
        : "r"  (addr)
        : "memory"
    );
    return ret;
}

inline uint64_t mminq(uintptr_t addr) {
    uint64_t ret;
    __asm__ __volatile__ (
        "movq (%1), %0"
        : "=r" (ret)
        : "r"  (addr)
        : "memory"
    );
    return ret;
}

inline uint64_t rdmsr(uint32_t msr) {
    uint32_t edx, eax;
    __asm__ __volatile__ ("rdmsr"
                  : "=a" (eax), "=d" (edx)
                  : "c" (msr)
                  : "memory");
    return ((uint64_t)edx << 32) | eax;
}

inline void wrmsr(uint32_t msr, uint64_t value) {
    uint32_t edx = value >> 32;
    uint32_t eax = (uint32_t)value;
    __asm__ __volatile__ ("wrmsr"
                  :
                  : "a" (eax), "d" (edx), "c" (msr)
                  : "memory");
}

inline uint64_t rdtsc(void) {
    uint32_t edx, eax;
    __asm__ __volatile__ ("rdtsc" : "=a" (eax), "=d" (edx));
    return ((uint64_t)edx << 32) | eax;
}

inline uint64_t read_cr0()
{
    uint64_t cr;
    __asm__ __volatile__ ( "mov %%cr0, %0" : "=r"(cr) );
    return cr;
}

inline uint64_t read_cr2()
{
    uint64_t cr;
    __asm__ __volatile__ ( "mov %%cr2, %0" : "=r"(cr) );
    return cr;
}

inline uint64_t read_cr3()
{
    uint64_t cr;
    __asm__ __volatile__ ( "mov %%cr3, %0" : "=r"(cr) );
    return cr;
}

inline uint64_t read_cr4()
{
    uint64_t cr;
    __asm__ __volatile__ ( "mov %%cr4, %0" : "=r"(cr) );
    return cr;
}

#endif