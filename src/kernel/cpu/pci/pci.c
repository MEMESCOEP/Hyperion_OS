#include <cpu/pci/pci.h>

mcfg_t * mcfg_table;
pci_device_vec_t pci_devices;

void pci_enumerate_bus(uint64_t base_addr, uint64_t bus)
{
    uint64_t offset = bus << 20;

    uint64_t bus_addr = base_addr + offset;

    pci_header_t * pci_bus_hdr = (pci_header_t *)bus_addr;

    if (pci_bus_hdr->device_id == 0 || pci_bus_hdr->device_id == 0xFFFF) return;

    for (uint64_t device = 0; device < 32; device++)
    {
        pci_enumerate_device(bus_addr, device, bus);
    }
}
void pci_enumerate_device(uint64_t bus_addr, uint64_t device, uint64_t bus)
{
    uint64_t offset = device << 15;

    uint64_t device_addr = bus_addr + offset;

    pci_header_t* pci_device_hdr = (pci_header_t*)device_addr;

    if (pci_device_hdr->device_id == 0 || pci_device_hdr->device_id == 0xFFFF) return;

    for (uint64_t function = 0; function < 8; function++)
    {
        pci_enumerate_function(device_addr, function, device, bus);
    }
}
void pci_enumerate_function(uint64_t device_addr, uint64_t function, uint64_t device, uint64_t bus)
{
    uint64_t offset = function << 12;

    uint64_t func_addr = device_addr + offset;

    pci_header_t * pci_function_hdr = (pci_header_t*)func_addr;

    if (pci_function_hdr->device_id == 0 || pci_function_hdr->device_id == 0xFFFF) return;

    pci_device_t * pci_dev = kmalloc(sizeof(pci_device_t));

    pci_dev->header = pci_function_hdr;
    pci_dev->vendor = (char*)pci_get_vendor(pci_dev->header->vendor_id);
    pci_dev->class = (char*)pci_get_class(pci_dev->header->class_id);
    pci_dev->subclass = (char*)pci_get_subclass(pci_dev->header->class_id, pci_dev->header->subclass_id);
    pci_dev->prog_if = "NULL";

    pci_dev->bus = (uint8_t)bus;
    pci_dev->device = (uint8_t)device;
    pci_dev->function = (uint8_t)function;

    vec_push(&pci_devices, (void*)pci_dev);
}
void pci_init()
{
    /* Looks for the MCFG in the rsdt/xsdt table */
    mcfg_table = (mcfg_t *)(acpi_find_sdt("MCFG"));
    /* Checks if it even returned anything */
    if (mcfg_table == 0)
    {   
        panic("MCFG is not supported on this device. If you're running this operating system under QEMU, make sure the flag, '-M q35' is present!\n");
    }

    uint64_t entry_count = (mcfg_table->header.length - sizeof(mcfg_t)) / sizeof(mcfg_entry_t);
    for (uint64_t i = 0; i < entry_count; i++)
    {
        for (uint64_t bus = mcfg_table->entries[i].start_bus; bus < mcfg_table->entries[i].end_bus; bus++)
        {
            pci_enumerate_bus(mcfg_table->entries[i].base_addr, bus);
        }
    }

    nlog_info("[PCI] >> PCI Initialized\n");
}