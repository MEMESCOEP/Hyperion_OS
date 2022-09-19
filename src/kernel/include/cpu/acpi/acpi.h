/**
 * @file acpi.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/NSG650/Polaris
 *      https://github.com/vlang/vinix
 * 
 * Resources used:
 *      https://wiki.osdev.org/ACPI
 * 
 */
#ifndef ACPI_H
#define ACPI_H

#include <stdint.h>
#include <kernel.h>
#include <neptunium/neptunium.h>
#include <libc/string.h>

/* SDT Header */
typedef struct sdt_header {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oem_id[6];
    char oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
} __attribute__ ((packed)) sdt_header_t;

/* RSDP Header */
typedef struct rsdp {
    char signature[8];
    uint8_t checksum;
    char oem_id[6];
    uint8_t revision;
    uint32_t rsdt_addr;
    uint32_t length;
    uint64_t xsdt_addr;
    uint8_t ext_checksum;
    uint8_t reserved[3];
} __attribute__ ((packed)) rsdp_t;

/* RSDT, also used for the XSDT */
typedef struct rsdt {
    sdt_header_t header;
    uint8_t sdt_ptr[];
} __attribute__ ((packed)) rsdt_t;

void acpi_init();
void * acpi_find_sdt(const char * signature);
void acpiPowerOff(struct limine_rsdp_request limine_rsdp);

#endif