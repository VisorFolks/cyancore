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
#include <stddef.h>
#include <status.h>
#include <resource.h>

/* Refer dp.c file for info */
extern dp_t *dev_prop;

/**
 * *dp_get_port_into - Get GPIO port info
 *
 * @brief This function fetches GPIO port info from
 * device properties. Developer needs to provided
 * enumerated ID to the function as argument which needs
 * to be as assigned in device properties. This function
 * is put under GPIO Guard as the structure itself will
 * the member if GPIO is turned off in platform config.mk
 *
 * @param[in] id: Enumerated ID for the GPIO port
 *
 * @return gpio_module_t *: Pointer to GPIO port module
 */
gpio_module_t *dp_get_port_info(hw_devid_t id)
{
	unsigned int i, n_ports;
	n_ports = dev_prop->n_ports;
	for(i = 0; i < n_ports; i++)
	{
		if(dev_prop->ports[i]->id == id)
			return dev_prop->ports[i];
	}
	return NULL;
}
