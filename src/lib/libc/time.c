/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: time.c
 * Description		: This file contains sources of libc-time
 *			  functions
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <arch.h>
#include <time.h>

status_t udelay(uint16_t d)
{
	status_t ret;
	uint64_t tstamp;
	uint64_t delay;

	if(d > 2000)
		return error_func_inval_arg;
	else if(d == 0)
		delay = 1;
	else
		delay = d;

	ret = get_timestamp(&tstamp);
	delay += tstamp;
	do
	{
		arch_wfi();
		ret = get_timestamp(&tstamp);
	} while(delay >= tstamp);
	return ret;
}

status_t mdelay(uint16_t d)
{
	status_t ret;
	uint64_t tstamp;
	uint64_t delay;

	if(d > 10000)
		return error_func_inval_arg;
	else if(d == 0)
		delay = 1000;
	else
		delay = (uint64_t)d * 1000U;

	ret = get_timestamp(&tstamp);
	delay += tstamp;
	do
	{
		arch_wfi();
		ret = get_timestamp(&tstamp);
	} while(delay >= tstamp);
	return ret;
}
