/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp_gpio.c
 * Description		: This file contains sources of device properties - gpio
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <resource.h>

extern dp_t *dev_prop;

#if N_PORT
gpio_module_t *dp_get_port_info(uint8_t id)
{
	return &dev_prop->port[id];
}
#endif
