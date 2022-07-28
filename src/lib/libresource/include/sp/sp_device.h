/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: sp_device.h
 * Description		: This file contains software device IDs
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _SP_DEVICE_H_

typedef enum
{
	console_uart	= 0x100,
	bt_uart		= 0x101,
	sched_timer	= 0x200,
	onboard_led	= 0x300,
} sw_devid_t;


