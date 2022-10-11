#include <cpu/irq/irq.h>

void* irq_handler_table[16] = { NULL };

void irq_init()
{
    nlog_info("[IRQ] >> Initializing IRQ...\n");

    irq_install_handler(0, &pit_handler);
    irq_install_handler(1, &keyboard_handler);
	irq_install_handler(12, &mouse_handler);
	
    nlog_info("[IRQ] >> IRQ Initialized\n");
}

void irq_install_handler(uint8_t num, void (*handler)(struct registers*))
{
    irq_handler_table[num] = handler;
}

void irq_uninstall_handler(uint8_t num)
{
    irq_handler_table[num] = 0;
}
void irq_handler(struct registers* r)
{
    void (*handler)(struct registers* r);
    handler = irq_handler_table[r->int_no - 32];

    if(handler != NULL)
    {
        handler(r);
    }
    
    // Sends an EOI (End of Interrupt) to the PIC
    pic_send_eoi(r->int_no - 32);
}