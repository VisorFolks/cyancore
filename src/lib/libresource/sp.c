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

sp_t *sw_prop;

status_t sp_init(sp_t *plat_sw_prop)
{
	status_t ret;

	if(plat_sw_prop)
	{
		sw_prop = plat_sw_prop;
		ret = success;
	}
	else
		ret = error_inval_arg;
	return ret;
}
