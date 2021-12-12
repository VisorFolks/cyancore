/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: sp.c
 * Description		: This file contains sources of software properties core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <sp.h>

/**
 * *sw_prop - A pointer to software properties
 *
 * @brief This variable is used by all the software properties
 * functons inside libresource.
 */
sp_t *sw_prop;

/**
 * sp_init - Software properties init
 *
 * @brief This function links the pointer to software
 * properties to actual software properties structure.
 *
 * @param[in] *plat_dev_prop: Pointer to software properties
 *			      Global structure
 *
 * @return status: Execution status of the function
 */
status_t sp_init(sp_t *plat_sw_prop)
{
	status_t ret;

	/* Check for NULL */
	if(plat_sw_prop)
	{
		/* Link the pointer and return success */
		sw_prop = plat_sw_prop;
		ret = success;
	}
	else
		/* If arg is NULL return error */
		ret = error_inval_arg;
	return ret;
}
