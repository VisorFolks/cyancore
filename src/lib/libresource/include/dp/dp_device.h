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
	cpu		= 0x00001000,
	memory		= 0x00002000,
	clock		= 0x00003000,
	uart		= 0x00004000,
	gpio		= 0x00005000,
	wdt		= 0x00006000,
	timer		= 0x00007000,
	generic_ic	= 0x00008000,
	nvic		= 0x00008100,
	gic		= 0x00008200,
	apic		= 0x00008300,
	clint		= 0x00008400,
	plic		= 0x00008500,
	prci		= 0x00009000,
	aon		= 0x0000a000,
} hw_devid_t;

