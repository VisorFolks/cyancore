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
	clock = 0x100,
	uart = 0x200,
	gpio = 0x300,
	wdt = 0x400,
} hw_devid_t;

