/**
 * @file elf.h
 * @author xyve
 * 
 * ELF file.
 * 
 */

#ifndef ELF_H
#define ELF_H

#include <stdint.h>
#include <libc/string.h>

typedef struct elf_header
{
    uint8_t magic;
    uint8_t ascii[3];
    uint8_t class_;
    uint8_t endian;
    uint8_t elf_version;
    uint8_t abi;
    uint8_t abi_version;
    uint8_t padding[7];
    uint16_t type;
    uint16_t machine; 
    uint32_t version; 
    uint64_t entry; 
    uint64_t phoffset; 
    uint64_t shoffset;
    uint32_t flags; 
    uint16_t ehsize;
    uint16_t phentsize; 
    uint16_t phnum; 
    uint16_t shentsize; 
    uint16_t shnum; 
    uint16_t shstrndx;
} __attribute__ ((packed)) elf_header_t;

typedef struct elf_section_header
{
    uint32_t name;
	uint32_t type;
	uint64_t flags;
	uint64_t addr;
	uint64_t offset;
	uint64_t size;
	uint32_t link;
	uint32_t info;
	uint64_t addralign;
	uint64_t entsize;
} __attribute__ ((packed)) elf_section_header_t;

typedef struct elf_symbol_table
{
	uint32_t name;
	uint8_t info;
	uint8_t other;
	uint16_t shndx;
	uint64_t value;
	uint64_t size;
} __attribute__ ((packed)) elf_symbol_table_t;

elf_section_header_t * elf_find_section_header(void * address, const char * name);

#endif