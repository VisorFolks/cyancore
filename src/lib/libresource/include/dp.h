/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp.h
 * Description		: This file contains prototypes of device properties
 *			  data structure and function prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <dp/dp_system.h>
#include <dp/dp_module.h>
#include <dp/dp_gpio.h>

typedef struct device_properties
{
	cpu_t *core[N_CORES];
	uint8_t datawidth;
	unsigned long base_clock;
	memory_t *memory;
#if GPIO == 1
	gpio_module_t *port[N_PORT];
#endif
#if UART == 1
	module_t *uart[N_UART];
#endif
#if ADC == 1
	module_t *adc[N_ADC];
#endif
#if TIMER == 1
	module_t *timer[N_TIMER];
#endif
#if SPI == 1
	module_t *spi[N_SPI];
#endif
#if I2C == 1
	module_t *i2c[N_I2C];
#endif
#if WDT == 1
	module_t *wdt[N_WDT];
#endif
} dp_t;

status_t dp_init(dp_t *);
