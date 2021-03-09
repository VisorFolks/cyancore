/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: mmio.h
 * Description		: This file consists of mmio defines
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _MMIO_H_

#include <stdint.h>

#define MMIO8(X)	(*(volatile uint8_t *)(X))
#define MMIO16(X)	(*(volatile uint16_t *)(X))
#define MMIO32(X)	(*(volatile uint32_t *)(X))
#define MMIO64(X)	(*(volatile uint64_t *)(X))
