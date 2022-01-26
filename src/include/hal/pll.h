/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: pll.h
 * Description		: This file consists of ADC-PLL prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>

typedef pll_port
{
	hw_devid_t port_id;
	uintptr_t baddr;
	uintptr_t stride;
} pll_port_t;
