#include <cpu/pci/pci_defs.h>

const char* pci_get_vendor(uint16_t vendor_id)
{
    switch(vendor_id)
    {
        case 0x1234:
            return "QEMU";
        case 0x18E4:
            return "Acer Inc.";
        case 0x1022:
            return "Advanced Micro Devices";
        case 0x1DED:
            return "Alibaba (China) Co., Ltd.";
        case 0x1D0F:
            return "Amazon";
        case 0x101E:
            return "American Megatrends Inc.";
        case 0x106B:
            return "Apple Computer";
        case 0x13B5:
            return "ARM Ltd.";
        case 0x1043:
            return "Asustek Computer Inc.";
        case 0x11AC:
            return "Canon Inc.";
        case 0x1137:
            return "Cisco Systems Inc.";
        case 0x1CFA:
            return "Corsair Memory Inc.";
        case 0x1D9B:
            return "Facebook";
        case 0x10CF:
            return "Fujitsu Limited";
        case 0x1458:
            return "Giga-Byte Technology Co., Ltd.";
        case 0x1AE0:
            return "Google Inc.";
        case 0x103C:
            return "Hewlett Packard";
        case 0x1590:
            return "Hewlett Packard Enterprise";
        case 0x1014:
            return "IBM";
        case 0x1BC0:
            return "InnoDisk Corporation";
        case 0x8086:
            return "Intel Corporation";
        case 0x17AA:
            return "Lenovo";
        case 0x1344:
            return "Micron Technology Inc.";
        case 0x1414:
            return "Microsoft";
        case 0x10DE:
            return "NVIDIA Corporation";
        case 0x10EC:
            return "Realtek";
        case 0x5143:
            return "Qualcomm Inc.";
        case 0x144D:
            return "Samsung Electronics Co., Ltd.";
        case 0x1BB1:
            return "Seagate Technology LLC";
        case 0x1C5C:
            return "SK Hynix";
        case 0x104D:
            return "Sony Group Corporation";
        case 0x104C:
            return "Texas Instruments";
        case 0x1D19:
            return "VAIO Corporation";
        case 0x15AD:
            return "Vmware, Inc.";
        case 0x1D72:
            return "Xiaomi Communications Co., Ltd.";
        default:
            return "Unknown Vendor";
    }
}
const char* pci_get_class(uint8_t class)
{
    switch(class)
    {
        case 0x0:
            return "Unclassified";
        case 0x1:
            return "Mass Storage Controller";
        case 0x2:
            return "Network Controller";
        case 0x3:
            return "Display Controller";
        case 0x4:
            return "Multimedia Controller";
        case 0x5:
            return "Memory Controller";
        case 0x6:
            return "Bridge";
        case 0x7:
            return "Simple Communication Controller";
        case 0x8:
            return "Base System Peripheral";
        case 0x9:
            return "Input Device Controller";
        case 0xA:
            return "Docking Station";
        case 0xB:
            return "Processor";
        case 0xC:
            return "Serial Bus Controller";
        case 0xD:
            return "Wireless Controller";
        case 0xE:
            return "Intelligent Controller";
        case 0xF:
            return "Satellite Communication Controller";
        case 0x10:
            return "Encryption Controller";
        case 0x11:
            return "Signal Processing Controller";
        case 0x12:
            return "Processing Accelerator";
        case 0x13:
            return "Non-Essential Instrumentation";
        case 0x40:
            return "Co-Processor";
        case 0xFF:
            return "Unassigned Class (Vendor specific)";
        default:
            return "Reserved";
    };
}
const char* pci_get_subclass(uint8_t class, uint8_t subclass)
{
    switch (class)
    {
    case 0x0:
        switch (subclass)
        {
        case 0x0:
            return "Non-VGA-Compatible Unclassified Device";
        default:
            return "Unknown Subclass";
        }
    case 0x1:
        switch (subclass)
        {
        case 0x0:
            return "SCSI Bus Controller";
        case 0x1:
            return "IDE Controller";
        case 0x2:
            return "Floppy Disk Controller";
        case 0x3:
            return "IPI Bus Controller";
        case 0x4:
            return "RAID Controller";
        case 0x5:
            return "ATA Controller";
        case 0x6:
            return "Serial ATA Controller";
        case 0x7:
            return "Serial Attached SCSI Controller";
        case 0x8:
            return "Non-Volatile Memory Controller";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x2:
        switch (subclass)
        {
        case 0x0:
            return "Ethernet Controller";
        case 0x1:
            return "Token Ring Controller";
        case 0x2:
            return "FDDI Controller";
        case 0x3:
            return "ATM Controller";
        case 0x4:
            return "ISDN Controller";
        case 0x5:
            return "WorldFip Controller";
        case 0x6:
            return "PICMG 2.14 Multi Computing Controller";
        case 0x7:
            return "Infiniband Controller";
        case 0x8:
            return "Fabric Controller";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x3:
        switch (subclass)
        {
        case 0x0:
            return "VGA Compatible Graphics Controller";
        case 0x1:
            return "XGA Graphics Controller";
        case 0x2:
            return "3D Graphics Controller (Not VGA-Compatible)";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x4:
        switch (subclass)
        {
        case 0x0:
            return "Multimedia Video Controller";
        case 0x1:
            return "Multimedia Audio Controller";
        case 0x2:
            return "Computer Telephony Device";
        case 0x3:
            return "Audio Device";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x5:
        switch (subclass)
        {
        case 0x0:
            return "RAM Controller";
        case 0x1:
            return "Flash Controller";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x6:
        switch (subclass)
        {
        case 0x0:
            return "Host Bridge";
        case 0x1:
            return "ISA Bridge";
        case 0x2:
            return "EISA Bridge";
        case 0x3:
            return "MCA Bridge";
        case 0x4:
            return "PCI-to-PCI Bridge";
        case 0x5:
            return "PCMCIA Bridge";
        case 0x6:
            return "NuBus Bridge";
        case 0x7:
            return "CardBus Bridge";
        case 0x8:
            return "RACEway Bridge";
        case 0x9:
            return "PCI-to-PCI Bridge";
        case 0xA:
            return "InfiniBand-to-PCI Host Bridge";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x7:
        switch (subclass)
        {
        case 0x0:
            return "Serial Controller";
        case 0x1:
            return "Parallel Controller";
        case 0x2:
            return "Multiport Serial Controller";
        case 0x3:
            return "Modem";
        case 0x4:
            return "IEEE 488.1/2 (GPIB) Controller";
        case 0x5:
            return "Smart Card Controller";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x8:
        switch (subclass)
        {
        case 0x0:
            return "PIC";
        case 0x1:
            return "DMA Controller";
        case 0x2:
            return "Timer";
        case 0x3:
            return "RTC Controller";
        case 0x4:
            return "PCI Hot-Plug Controller";
        case 0x5:
            return "SD Host controller";
        case 0x6:
            return "IOMMU";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x9:
        switch (subclass)
        {
        case 0x0:
            return "Keyboard Controller";
        case 0x1:
            return "Digitizer Pen";
        case 0x2:
            return "Mouse Controller";
        case 0x3:
            return "Scanner Controller";
        case 0x4:
            return "Gameport Controller";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0xA:
        switch (subclass)
        {
        case 0x0:
            return "Generic";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0xB:
        switch (subclass)
        {
        case 0x0:
            return "386";
        case 0x1:
            return "486";
        case 0x2:
            return "Pentium";
        case 0x3:
            return "Pentium Pro";
        case 0x10:
            return "Alpha";
        case 0x20:
            return "PowerPC";
        case 0x30:
            return "MIPS";
        case 0x40:
            return "Co-Processor";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0xC:
        switch (subclass)
        {
        case 0x0:
            return "FireWire (IEEE 1394) Controller";
        case 0x1:
            return "ACCESS Bus Controller";
        case 0x2:
            return "SSA";
        case 0x3:
            return "USB Controller";
        case 0x4:
            return "Fibre Channel";
        case 0x5:
            return "SMBus Controller";
        case 0x6:
            return "InfiniBand Controller";
        case 0x7:
            return "IPMI Interface";
        case 0x8:
            return "SERCOS Interface (IEC 61491)";
        case 0x9:
            return "CANbus Controller";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0xD:
        switch (subclass)
        {
        case 0x0:
            return "iRDA Compatible Controller";
        case 0x1:
            return "Consumer IR Controller";
        case 0x10:
            return "RF Controller";
        case 0x11:
            return "Bluetooth Controller";
        case 0x12:
            return "Broadband Controller";
        case 0x20:
            return "Ethernet Controller (802.1a)";
        case 0x21:
            return "Ethernet Controller (802.1b)";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0xE:
        switch (subclass)
        {
        case 0x0:
            return "I20";
        }
    case 0xF:
        switch (subclass)
        {
        case 0x1:
            return "Satellite TV Controller";
        case 0x2:
            return "Satellite Audio Controller";
        case 0x3:
            return "Satellite Voice Controller";
        case 0x4:
            return "Satellite Data Controller";
        default:
            return "Unknown Subclass";
        }
    case 0x10:
        switch (subclass)
        {
        case 0x0:
            return "Network and Computing Encrpytion/Decryption";
        case 0x10:
            return "Entertainment Encryption/Decryption";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }
    case 0x11:
        switch (subclass)
        {
        case 0x0:
            return "DPIO Modules";
        case 0x1:
            return "Performance Counters";
        case 0x10:
            return "Communication Synchronizer";
        case 0x20:
            return "Signal Processing Management";
        case 0x80:
            return "Other";
        default:
            return "Unknown Subclass";
        }

    default:
        return "Unknown Class";
    }
}