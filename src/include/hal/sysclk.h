/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: sysclk.h
 * Description		: This file consists of SYSCLK prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*
 * Note:
 * - For SiFive HAL, this header file is associated with prci.c
 */

#pragma once

#include <status.h>
#include <stdint.h>
#include <resource.h>
#include <lock/lock.h>
#include <platform.h>

typedef enum clock_type
{
	internal,
	external
} clock_type_t;

typedef struct sysclk_port
{
	hw_devid_t port_id;
	unsigned int base_clk;
	uintptr_t baddr;
	uintptr_t stride;
	clock_type_t type;
	lock_t key;
} sysclk_port_t;
