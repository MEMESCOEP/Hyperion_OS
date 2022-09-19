#include <cpu/timer/pit.h>

uint64_t timer_ticks = 0;

void pit_init(int32_t hz)
{
    int32_t divisor = INPUT_CLOCK_FREQUENCY / hz;
    outb(TIMER_COMMAND, TIMER_OCW);
    outb(TIMER_DATA, divisor & 0xFF); 
    outb(TIMER_DATA, divisor >> 8);
    
    nlog_info("PIT Frequency Set\n");
}
void pit_handler(struct registers* regs)
{

}
uint64_t pit_get_ticks()
{
    return timer_ticks;
}