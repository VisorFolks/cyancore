/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp_module.c
 * Description		: This file contains sources of device properties - module
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <status.h>
#include <resource.h>

extern dp_t *dev_prop;

module_t *dp_get_module_info(hw_devid_t dev)
{
	unsigned int i, n_mods;
	n_mods = dev_prop->n_mods;
	for(i = 0; i < n_mods; i++)
	{
		if(dev_prop->modules[i]->id == dev)
			return dev_prop->modules[i];
	}
	return NULL;
}
