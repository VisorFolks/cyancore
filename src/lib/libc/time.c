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
#include <string.h>
#include <time.h>

/**
 * udelay - microsecond delay
 *
 * @brief This function is used to produces microsecond delay.
 * But it uses get_timestamp function which in few platforms
 * can change only every millisecond. During generation of delay,
 * this function enters wfi state to save cpu clocks.
 * Note: To be used carefully.
 *
 * @param[in] d: 1-2000 usec
 */
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

/**
 * mdelay - millisecond delay
 *
 * @brief This function is used to produces millisecond delay.
 * During generation of delay, this function enters wfi state
 * to save cpu clocks.
 *
 * @param[in] d: 1-10000 msec
 */
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

/**
 * getTime - Function that returns Julian days-time
 */
status_t getTime(time_t *t)
{
	uint64_t tstamp;
	status_t ret = get_timestamp(&tstamp);
	if(ret)
	{
		memset(t, 0, sizeof(time_t));
		goto exit;
	}
	 tstamp /= 10000;
	t->cs = tstamp % 100;
	tstamp /= 100;
	t->s = tstamp % 60;
	tstamp /= 60;
	t->m = tstamp % 60;
	tstamp /= 60;
	t->h = tstamp % 24;
	t->dd = tstamp / 24;
exit:
	return ret;
}
