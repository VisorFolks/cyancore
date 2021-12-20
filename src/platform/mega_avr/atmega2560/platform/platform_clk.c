/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_clk.c
 * Description		: This file contains sources for platform
 *			  clock apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <mmio.h>
#include <plat_arch.h>
#include <platform.h>

status_t platform_clk_reset()
{
	MMIO8(PRR0) = 0xff;
	MMIO8(PRR1) = 0xff;
	return success;
}

status_t platform_clk_en(unsigned int id)
{
	if(id >= 16)
		return error_data;
	if(id < 8)
		MMIO8(PRR0) &= ~(1 << id);
	else
		MMIO8(PRR1) &= ~(1 << (id-8));
	return success;
}

status_t platform_clk_dis(unsigned int id)
{
	if(id >= 16)
		return error_data;
	if(id < 8)
		MMIO8(PRR0) |= (1 << id);
	else
		MMIO8(PRR1) |= (1 << (id-8));
	return success;
}
