/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: machine_call.c
 * Description		: This file contains sources of machine call handler
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <status.h>
#include <machine_call.h>
#include <platform.h>
#include <resource.h>

void machine_call(unsigned int code, unsigned int a0 _UNUSED, unsigned int a1 _UNUSED, unsigned int a2 _UNUSED, mret_t *ret)
{
	switch(code)
	{
		case FETCH_DP:
			*ret = platform_fetch_dp(a0, a1);
			break;
		default:
			ret->p = (uintptr_t)NULL;
			ret->size = 0x00;
			ret->status = error_inval_code;
			break;
	}

	return;
}
