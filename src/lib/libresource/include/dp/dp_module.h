/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp_module.h
 * Description		: This file contains prototypes of device
 *			  properties - module
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>

typedef struct module
{
	uint8_t id;
	uintptr_t baddr;
	uintptr_t stride;
	unsigned long clk;
	unsigned int clk_id;
	size_t interrupt_id[MAX_INTERRUPTS_PER_DEVICE];
	int_trigger_t interrupt_trigger[MAX_INTERRUPTS_PER_DEVICE];
} module_t;

#define DP_PROTOTYPE_MODULE_FUNCTION(mod)	\
	module_t *dp_get_##mod##_info(uint8_t);

#if UART == 1
DP_PROTOTYPE_MODULE_FUNCTION(uart)
#endif

#if ADC == 1
DP_PROTOTYPE_MODULE_FUNCTION(adc)
#endif

#if TIMER == 1
DP_PROTOTYPE_MODULE_FUNCTION(timer)
#endif

#if SPI == 1
DP_PROTOTYPE_MODULE_FUNCTION(spi)
#endif

#if I2C == 1
DP_PROTOTYPE_MODULE_FUNCTION(i2c)
#endif

#if WDT == 1
DP_PROTOTYPE_MODULE_FUNCTION(wdt)
#endif
