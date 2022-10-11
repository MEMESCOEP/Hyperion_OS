#include <cpu/acpi/madt.h>

uint64_t lapic_addr = 0;
madt_t * madt_table;
lapic_vec_t madt_local_apics;
ioapic_vec_t madt_io_apics;
iso_vec_t madt_isos;
lapic_nmi_vec_t madt_lapic_nmis;
void madt_init()
{
    nlog_info("[APIC] >> Initializing MADT...\n");
    /* Looks for the APIC in the rsdt/xsdt table */
    madt_table = (madt_t *)(acpi_find_sdt("APIC"));
    /* Checks if it even returned anything */
    if (!madt_table)
    {   
        panic("[APIC] >> APIC is not supported on this device\n");
    }
    lapic_addr = madt_table->lapic_addr;

    /* The APIC exists! */
    uint8_t * madt_ptr = (uint8_t *)madt_table->madt_entries;


    vec_init(&madt_local_apics);
	vec_init(&madt_io_apics);
	vec_init(&madt_isos);
	vec_init(&madt_lapic_nmis);

    for (madt_ptr; (uint64_t)madt_ptr < (uint64_t)madt_table + madt_table->header.length; madt_ptr += *(madt_ptr + 1))
    {
        switch(*madt_ptr)
        {
            case 0:
                vec_push(&madt_local_apics, (madt_lapic_t *)madt_ptr);
                break;
            case 1:
                vec_push(&madt_io_apics, (madt_ioapic_t *)madt_ptr);
                break;
            case 2:
                vec_push(&madt_isos, (madt_iso_t *)madt_ptr);
                break;
            case 4:
                vec_push(&madt_lapic_nmis, (lapic_nmi_vec_t *)madt_ptr);
                break;
            case 5:
                lapic_addr = *(uint64_t*)(madt_ptr + 4);
                break;
        }
    }

    nlog_info("[APIC] >> MADT Initialized\n");
}