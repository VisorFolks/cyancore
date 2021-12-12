/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp.c
 * Description		: This file contains sources of device properties core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <resource.h>

/**
 * *dev_prop - A pointer to device properties
 *
 * @brief This variable is used by all the device properties
 * functons inside libresource.
 */
dp_t *dev_prop;

/**
 * dp_init - Device properties init
 *
 * @brief This function links the pointer to device
 * properties to actual device properties structure.
 *
 * @param[in] *plat_dev_prop: Pointer to device properties
 *			      Global structure
 *
 * @return status: Execution status of the function
 */
status_t dp_init(dp_t *plat_dev_prop)
{
	status_t ret;

	/* Check for NULL */
	if(plat_dev_prop)
	{
		/* Link the pointer and return success */
		dev_prop = plat_dev_prop;
		ret = success;
	}
	else
		/* If arg is NULL return error */
		ret = error_inval_arg;
	return ret;
}
