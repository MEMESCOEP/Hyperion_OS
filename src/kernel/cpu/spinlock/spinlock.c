#include <cpu/spinlock/spinlock.h>

void spinlock_lock(lock_t lock)
{
    while(__atomic_test_and_set(&lock, __ATOMIC_ACQUIRE));
}
void spinlock_unlock(lock_t lock)
{
    __atomic_clear(&lock, __ATOMIC_RELEASE);
}

lock_t liballoc_spinlock;

int liballoc_lock()
{
    spinlock_lock(liballoc_spinlock);
    cli();
    return 0;
}
int liballoc_unlock()
{
    spinlock_unlock(liballoc_spinlock);
    sti();
    return 0;
}