/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp_gpio.h
 * Description		: This file contains prototypes of device
 *			  properties - gpio
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>

typedef const struct pinmux
{
	uint8_t port;
	uint8_t function;
	uint8_t npins;
	const uint8_t *pins;
} pinmux_t;

typedef const struct gpio_module
{
	hw_devid_t id;
	uintptr_t baddr;
	uintptr_t stride;
} gpio_module_t;


#define addpins(p, x, func)	{				\
					.port = p,		\
					.pins = x,		\
					.npins = propsize(x),	\
					.function = func	\
				}

#define add_ports(x)		.ports = x,		\
				.n_ports = propsize(x)

gpio_module_t *dp_get_port_info(hw_devid_t);
