#ifndef PCI_DEFS_H
#define PCI_DEFS_H

#include <stdint.h>

const char* pci_get_vendor(uint16_t vendor_id);
const char* pci_get_class(uint8_t class);
const char* pci_get_subclass(uint8_t class, uint8_t subclass);

#endif