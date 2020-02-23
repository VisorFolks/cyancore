#pragma once

typedef unsigned int spinlock_t;

void spinlock_acquire(spinlock_t *);
void spinlock_release(spinlock_t *);
