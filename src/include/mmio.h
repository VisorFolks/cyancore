#pragma once
#define _MMIO_H_

#include <stdint.h>

#define MMIO8(X)	(*(volatile uint8_t *)(X))
#define MMIO16(X)	(*(volatile uint16_t *)(X))
#define MMIO32(X)	(*(volatile uint32_t *)(X))
#define MMIO64(X)	(*(volatile uint64_t *)(X))
