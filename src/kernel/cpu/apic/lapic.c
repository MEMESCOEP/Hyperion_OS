#include <cpu/apic/lapic.h>

static uint32_t lapic_timer_freq = 0;

static void lapic_write(uint32_t reg, uint32_t val)
{
    mmoutd((uintptr_t)lapic_addr + hhdm_request.response->offset + reg, val);
}
static uint32_t lapic_read(uint32_t reg)
{
    return mmind((uintptr_t)lapic_addr + hhdm_request.response->offset + reg);
}
void lapic_send_eoi()
{
    lapic_write(LAPIC_EOI_REG, 0);
}
void lapic_stop_timer()
{
	lapic_write(LAPIC_TIMER_INITCNT_REG, 0);
	lapic_write(LAPIC_TIMER_REG, LAPIC_TIMER_DISABLE_BIT);
}
void lapic_calibrate_timer()
{
    lapic_stop_timer();
}
void lapic_oneshot_timer(uint8_t vec, uint64_t us)
{
	lapic_stop_timer();

	uint64_t ticks = us * (lapic_timer_freq / 1000000);

	lapic_write(LAPIC_TIMER_REG, vec);
	lapic_write(LAPIC_TIMER_DIV_REG, 0);
	lapic_write(LAPIC_TIMER_INITCNT_REG, ticks);
}