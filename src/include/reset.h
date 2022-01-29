/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: reset.h
 * Description		: This file consists of reset status datatypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _RESET_H_

typedef enum reset
{
	power_on_reset		= 0,
	external_reset		= 1,
	brownout_reset		= 2,
	wdog_reset		= 3,
	jtag_reset		= 4,
	not_reset		= 254,
	inval_reset		= 255
} reset_t;
