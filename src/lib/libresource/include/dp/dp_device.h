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
	cpu		= 0x1000,
	memory		= 0x2000,
	clock		= 0x3000,
	uart		= 0x4000,
	gpio		= 0x5000,
	wdt		= 0x6000,
	timer		= 0x7000,
	ic		= 0x8000,
	nvic		= 0x8100,
	gic		= 0x8200,
	apic		= 0x8300,
	clint		= 0x8400,
	plic		= 0x8500,
	prci		= 0x9000,
	aon		= 0xa000,
} hw_devid_t;

