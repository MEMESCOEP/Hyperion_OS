/**
 * @file spinlock.h
 * @author xyve
 * 
 * Spinlock.
 * 
 */
#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <neptunium/neptunium.h>
#include <stdbool.h>

typedef volatile bool lock_t;


void spinlock_lock(lock_t lock);
void spinlock_unlock(lock_t lock);

#endif