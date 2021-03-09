/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: machine_call.h
 * Description		: This file consists of machine call IDs and prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _MACHINE_CALL_H_

#include <stdint.h>

typedef struct mret
{
	uintptr_t p;
	size_t size;
	status_t status;
} mret_t;

// Machine call IDs

#define FETCH_DP		0x0001
#define SET_SLEEP_MODE		0x0002
