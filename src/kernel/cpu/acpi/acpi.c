#include <cpu/acpi/acpi.h>
#include <stdint.h>
#include <stddef.h>
#include <limine.h>

/* Pointer to the rsdp */
rsdp_t * rsdp_ptr;
/* 
    rsdt Table gotten from the rsdp_ptr.
    Either a rsdt or xsdt, depending on whether it's supported.
*/
rsdt_t * rsdt_table;
uint64_t rsdp_address;

void acpi_init()
{
    /* Get the address of the rsdp table */
    rsdp_address = rsdp_request.response->address;

    /* Check if the rsdp_address isn't 0, if it is, then panic the system */
    if (rsdp_address == 0)
    {
        panic("[ACPI] >> ACPI is not supported on this device\n");
    }

    /* Acquire the rsdp table */
    rsdp_ptr = (rsdp_t *)rsdp_address;
    
    /* Check if xsdt is available */
    if (rsdp_ptr->revision >= 2 && rsdp_address != 0)
    {
        /* Gets the xsdt */
        rsdt_table = (rsdt_t *)(rsdp_ptr->xsdt_addr + hhdm_request.response->offset);
    }
    else 
    {
        /* Uses the rsdt instead of the xsdt, due to the version not being 2 or greater */
        rsdt_table = (rsdt_t *)(rsdp_ptr->rsdt_addr + hhdm_request.response->offset);
    }

    nlog_info("[ACPI] >> ACPI Initialized\n");    
}
/**
 * @brief 
 * 
 */
void * acpi_find_sdt(const char * signature)
{
    /* 
        Gets the number of entries in the rsdt_table.
        The ternary operation checks if the rsdt is a xsdt, by checking the revision and the address.
        If it's xsdt, 8 if not 4.
    */
    uint64_t entry_count = (rsdt_table->header.length - sizeof(sdt_header_t) / (rsdp_ptr->revision >= 2 && rsdp_address != 0) ? 8 : 4);

    for (uint64_t i = 0; i < entry_count; i++)
    {
        sdt_header_t * header_ptr;

        /* Check if xsdt is being used */
        if (rsdp_ptr->revision >= 2 && rsdp_address != 0) 
        {
            /* Casts it as uint64_t, because the xsdt being used */
            header_ptr = (sdt_header_t *)(uintptr_t)((uint64_t *)rsdt_table->sdt_ptr)[i];
        }
        else 
        {
            /* Casts it as uint32_t, because the rsdt being used */
            header_ptr = (sdt_header_t *)(uintptr_t)((uint32_t *)rsdt_table->sdt_ptr)[i];
        }
        /* Checks for the signature */
        if(header_ptr->signature != NULL)
        {
            if (strncmp(header_ptr->signature, signature, 4) == 0)
            {
                /* Return the pointer to the sdt found */
                return (void *)header_ptr + hhdm_request.response->offset;
            }
        }
    }
    
    return NULL;
}

uint64_t *SMI_CMD;
unsigned char ACPI_ENABLE;
unsigned char ACPI_DISABLE;
uint64_t *PM1a_CNT;
uint64_t *PM1b_CNT;
uint64_t SLP_TYPa;
uint64_t SLP_TYPb;
uint64_t SLP_EN;
uint64_t SCI_EN;
unsigned char PM1_CNT_LEN;

void acpiPowerOff(struct limine_rsdp_request limine_rsdp)
{
   // SCI_EN is set to 1 if acpi shutdown is possible
   if (SCI_EN == 0)
      return;

   //acpiEnable();

   // send the shutdown command
   outb((unsigned int) PM1a_CNT, SLP_TYPa | SLP_EN );
   if ( PM1b_CNT != 0 )
      outb((unsigned int) PM1b_CNT, SLP_TYPb | SLP_EN );

    outb(limine_rsdp.id, 0x00);
   panic("acpi poweroff failed.\n");
}

