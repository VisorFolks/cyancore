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

/**
 * create_gpio_module - Instantiates gpio module
 *
 * @param[in] _name - Name of the module
 * @param[in] _id - id of the module
 * @param[in] _baddr - base address of the module
 * @param[in] _stride - stride of the address space
 */
#define create_gpio_module(_name, _id, _baddr, _stride)	\
	gpio_module_t _name =		\
	{				\
		.id = _id,		\
		.baddr = _baddr,	\
		.stride = _stride	\
	}

/**
 * create_gpio_list - Creates a list of gpio module
 *
 * @param[in] _name - Name of the list
 * @param[in] _gpio - name of first module
 * @param[in] ... - variable args if there is more than 1 module
 */
#define create_gpio_list(_name, gpio, ...)	\
	gpio_module_t * const _name[] =		\
	{					\
		gpio,				\
		##__VA_ARGS__			\
	}

gpio_module_t *dp_get_port_info(hw_devid_t);
