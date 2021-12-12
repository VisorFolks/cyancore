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

typedef struct gpio_module
{
	hw_devid_t id;
	uintptr_t baddr;
	uintptr_t stride;
} gpio_module_t;

gpio_module_t *dp_get_port_info(hw_devid_t);
