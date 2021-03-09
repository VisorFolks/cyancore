/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: resources.h
 * Description		: This file contains prototypes of resources
 *			  apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <dp/dp_system.h>
#include <dp/dp_module.h>
#include <dp/dp_gpio.h>

typedef struct device_properties
{
	cpu_t core[N_CORES];
	uint8_t datawidth;
	unsigned long base_clock;
	memory_t memory;
#if GPIO
	gpio_module_t port[N_PORT];
#endif
#if UART0
	module_t uart0;
#endif
#if ADC0
	module_t adc0;
#endif
#if TIMER0
	module_t timer0;
#endif
#if TIMER1
	module_t timer1;
#endif
#if TIMER2
	module_t timer2;
#endif
#if SPI0
	module_t spi0;
#endif
#if I2C0
	module_t i2c0;
#endif
#if WDT0
	module_t wdt0;
#endif
} dp_t;

status_t dp_init(dp_t *);
