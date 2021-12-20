/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp_device.h
 * Description		: This file contains hardware device IDs
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _DP_DEVICE_H_

typedef enum
{
	cpu		= 0x100,
	memory		= 0x200,
	clock		= 0x300,
	uart		= 0x400,
	gpio		= 0x500,
	wdt		= 0x600,
	timer		= 0x700,
} hw_devid_t;

