#ifndef MCFG_H
#define MCFG_H

#include <cpu/acpi/acpi.h>
#include <utils/vec.h>
#include <cpu/pci/pci_defs.h>

typedef struct mcfg_entry
{
    uint64_t base_addr;
    uint16_t seg_group;
    uint8_t start_bus;
    uint8_t end_bus;
    uint32_t reserved;
} __attribute__ ((packed)) mcfg_entry_t;

typedef struct mcfg
{
    sdt_header_t header;
    uint64_t reserved;
    mcfg_entry_t entries[];
    
} __attribute__ ((packed)) mcfg_t;

typedef struct pci_header
{
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t command;
    uint16_t status;
    uint8_t revision_id;
    uint8_t prog_if;
    uint8_t subclass_id;
    uint8_t class_id;
    uint8_t cache_line_size;
    uint8_t latency_timer;
    uint8_t header_type;
    uint8_t bist;
} __attribute__ ((packed)) pci_header_t;

typedef struct pci_device
{
    pci_header_t * header;
    char * vendor;
    char * class;
    char * subclass;
    char * prog_if;
    uint8_t bus;
    uint8_t device;
    uint8_t function;
} __attribute__ ((packed)) pci_device_t;

typedef vec_t(pci_device_t *) pci_device_vec_t;

extern pci_device_vec_t pci_devices;

void pci_init();

#endif