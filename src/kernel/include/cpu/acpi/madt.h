/**
 * @file madt.h
 * @author xyve
 * 
 * Credit to the following project(s):
 *      https://github.com/NSG650/Polaris
 *      https://github.com/managarm/lai
 *      https://github.com/vlang/vinix
 * 
 * Resources used:
 *      https://wiki.osdev.org/MADT
 * 
 */
#ifndef MADT_H
#define MADT_H

#include <cpu/acpi/acpi.h>
#include <utils/vec.h>

/* MADT Structure */
typedef struct madt
{
    sdt_header_t header;
    uint32_t lapic_addr;
    uint32_t flags;
    uint8_t madt_entries[];
} __attribute__ ((packed)) madt_t;

/* MADT Header */
typedef struct madt_header
{
    uint8_t entry_type;
    uint8_t record_length;
}__attribute__ ((packed)) madt_header_t;

/* Local APIC Structure */
typedef struct madt_lapic
{
    madt_header_t header;
    uint8_t acpi_processor_id;
    uint8_t apic_id;
    uint32_t flags;
} __attribute__ ((packed)) madt_lapic_t;

/* I/O APIC Structure */
typedef struct madt_ioapic
{
    madt_header_t header;
    uint8_t ioapic_id;
    uint8_t reserved;
    uint32_t ioapic_addr;
    uint32_t flags;
} __attribute__ ((packed)) madt_ioapic_t;

/* IO/APIC Interrupt Structure */
typedef struct madt_iso
{
    madt_header_t header;
    uint8_t bus;
    uint8_t irq;
    uint32_t gsi;
    uint32_t flags;
} __attribute__ ((packed)) madt_iso_t;

/* IO/APIC Non-Maskable Interrupt Structure */
typedef struct madt_ioapic_nmi
{
    madt_header_t header;
    uint8_t nmi;
    uint8_t reserved;
    uint16_t flags;
    uint32_t gsi;
} __attribute__ ((packed)) madt_ioapic_nmi_t;

typedef struct madt_lapic_nmi
{
    madt_header_t header;
    uint8_t processor;
    uint16_t flags;
    uint8_t lint;
}__attribute__ ((packed)) madt_lapic_nmi_t;

typedef vec_t(madt_lapic_t *) lapic_vec_t;
typedef vec_t(madt_ioapic_t *) ioapic_vec_t;
typedef vec_t(madt_iso_t *) iso_vec_t;
typedef vec_t(madt_lapic_nmi_t *) lapic_nmi_vec_t;

extern madt_t * madt_table;
extern lapic_vec_t madt_local_apics;
extern ioapic_vec_t madt_io_apics;
extern iso_vec_t madt_isos;
extern lapic_nmi_vec_t madt_lapic_nmis;

extern uint64_t lapic_addr;

void madt_init();

#endif