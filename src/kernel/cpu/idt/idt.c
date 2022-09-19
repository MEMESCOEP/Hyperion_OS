#include <cpu/idt/idt.h>

/**
 * Sets a IDT entry
 *
 * @param num Index of the IDT table
 * @param base Base of the IDT entry
 * @param selector Selector of the IDT entry
 * @param flags Flags of the GDT entry
 */
void idt_set_gate(uint16_t num, uint64_t base, uint16_t selector, uint8_t flags) {
    idt_table[num].base0 = base;
    idt_table[num].base1 = (base >> 16) & 0xFFFF;
    idt_table[num].base2 = (base >> 32) & 0xFFFFFFFF;
    idt_table[num].selector = selector;
    idt_table[num].zero = 0;
    idt_table[num].flags = flags; 
    idt_table[num].ist = 0;
}
/**
 * Initializes IDT
 */
void idt_init()
{
    /* Sets the first 32 IDT gates, which are exceptions */
    idt_set_gate(0, (uint64_t)isr0, 0x28, 0x8E);
    idt_set_gate(1, (uint64_t)isr1, 0x28, 0x8E);
    idt_set_gate(2, (uint64_t)isr2, 0x28, 0x8E);
    idt_set_gate(3, (uint64_t)isr3, 0x28, 0x8E);
    idt_set_gate(4, (uint64_t)isr4, 0x28, 0x8E);
    idt_set_gate(5, (uint64_t)isr5, 0x28, 0x8E);
    idt_set_gate(6, (uint64_t)isr6, 0x28, 0x8E);
    idt_set_gate(7, (uint64_t)isr7, 0x28, 0x8E);
    idt_set_gate(8, (uint64_t)isr8, 0x28, 0x8E);
    idt_set_gate(9, (uint64_t)isr9, 0x28, 0x8E);
    idt_set_gate(10, (uint64_t)isr10, 0x28, 0x8E);
    idt_set_gate(11, (uint64_t)isr11, 0x28, 0x8E);
    idt_set_gate(12, (uint64_t)isr12, 0x28, 0x8E);
    idt_set_gate(13, (uint64_t)isr13, 0x28, 0x8E);
    idt_set_gate(14, (uint64_t)isr14, 0x28, 0x8E);
    idt_set_gate(15, (uint64_t)isr15, 0x28, 0x8E);
    idt_set_gate(16, (uint64_t)isr16, 0x28, 0x8E);
    idt_set_gate(17, (uint64_t)isr17, 0x28, 0x8E);
    idt_set_gate(18, (uint64_t)isr18, 0x28, 0x8E);
    idt_set_gate(19, (uint64_t)isr19, 0x28, 0x8E);
    idt_set_gate(20, (uint64_t)isr20, 0x28, 0x8E);
    idt_set_gate(21, (uint64_t)isr21, 0x28, 0x8E);
    idt_set_gate(22, (uint64_t)isr22, 0x28, 0x8E);
    idt_set_gate(23, (uint64_t)isr23, 0x28, 0x8E);
    idt_set_gate(24, (uint64_t)isr24, 0x28, 0x8E);
    idt_set_gate(25, (uint64_t)isr25, 0x28, 0x8E);
    idt_set_gate(26, (uint64_t)isr26, 0x28, 0x8E);
    idt_set_gate(27, (uint64_t)isr27, 0x28, 0x8E);
    idt_set_gate(28, (uint64_t)isr28, 0x28, 0x8E);
    idt_set_gate(29, (uint64_t)isr29, 0x28, 0x8E);
    idt_set_gate(30, (uint64_t)isr30, 0x28, 0x8E);
    idt_set_gate(31, (uint64_t)isr31, 0x28, 0x8E);

    pic_init();

    /* Sets all of the IRQ gates, which are 16 */
    idt_set_gate(32, (uint64_t)irq0, 0x28, 0x8E);
    idt_set_gate(33, (uint64_t)irq1, 0x28, 0x8E);
    idt_set_gate(34, (uint64_t)irq2, 0x28, 0x8E);
    idt_set_gate(35, (uint64_t)irq3, 0x28, 0x8E);
    idt_set_gate(36, (uint64_t)irq4, 0x28, 0x8E);
    idt_set_gate(37, (uint64_t)irq5, 0x28, 0x8E);
    idt_set_gate(38, (uint64_t)irq6, 0x28, 0x8E);
    idt_set_gate(39, (uint64_t)irq7, 0x28, 0x8E);
    idt_set_gate(40, (uint64_t)irq8, 0x28, 0x8E);
    idt_set_gate(41, (uint64_t)irq9, 0x28, 0x8E);
    idt_set_gate(42, (uint64_t)irq10, 0x28, 0x8E);
    idt_set_gate(43, (uint64_t)irq11, 0x28, 0x8E);
    idt_set_gate(44, (uint64_t)irq12, 0x28, 0x8E);
    idt_set_gate(45, (uint64_t)irq13, 0x28, 0x8E);
    idt_set_gate(46, (uint64_t)irq14, 0x28, 0x8E);
    idt_set_gate(47, (uint64_t)irq15, 0x28, 0x8E);

    idt_set_gate(128, (uint64_t)isr128, 0x28, 0x8E);

    /* Loads the IDT Pointer */
    idt_reload();

    /* Prints it to the screen */
    nlog_info("[IDT] >> IDT Initialized\n");
}
void idt_reload()
{
    idt_desc_t idt_table_desc;
    
    /* Sets the 80-bit pointer */
    idt_table_desc.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_table_desc.base = (uint64_t)&idt_table;
    
    /* Calls the assembly function to set the IDT */
    idt_load(&idt_table_desc);
}