/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_mcall.c
 * Description		: This file contains platform mcall registration
 *			  api
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stddef.h>
#include <stdint.h>
#include <status.h>
#include <machine_call.h>
#include <plat_arch.h>
#include <platform.h>

status_t platform_mcall_update(void *handler)
{
	if(handler)
	{
		mcall = handler;
		return success;
	}
	return error_inval_arg;
}
