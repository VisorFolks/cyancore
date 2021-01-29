#pragma once
#define _SPINLOCK_H_

#include <stdint.h>

typedef size_t spinlock_t;

void spinlock_acquire(spinlock_t *);
void spinlock_release(spinlock_t *);
