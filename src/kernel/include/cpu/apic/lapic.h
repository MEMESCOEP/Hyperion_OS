#ifndef LAPIC_H
#define LAPIC_H

#include <cpu/acpi/madt.h>

#define LAPIC_ID_REG		0x020
#define LAPIC_EOI_REG		0x0B0
#define LAPIC_SPURIOUS_REG	0x0F0
#define LAPIC_ICR0_REG		0x300
#define LAPIC_ICR1_REG		0x310
#define LAPIC_TIMER_REG		0x320
#define LAPIC_TIMER_INITCNT_REG	0x380
#define LAPIC_TIMER_CURCNT_REG	0x390
#define LAPIC_TIMER_DIV_REG	0x3E0

#define LAPIC_ENABLE_BIT	(1 << 8)
#define LAPIC_TIMER_DISABLE_BIT	(1 << 16)

#define LAPIC_TIMER_PERIODIC_MODE 0x20000

#define US_TIMESLICE_PERIOD 5000

#define LAPIC_TIMER_INT	32

void lapic_send_eoi();


#endif