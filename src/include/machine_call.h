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
#include <status.h>
#include <call_type.h>

// Machine call IDs
typedef enum mcall_id
{
	fetch_sp		= 0x0001,
	fetch_dp		= 0x0002,
	set_sleep_mode		= 0x0003,
} mcall_id_t;

typedef struct mret
{
	uintptr_t p;
	size_t size;
	status_t status;
} mret_t;

typedef struct mcall
{
	mcall_id_t id;
	mret_t (*callback)(call_args a0, call_args a1, call_args a2);
} mcall_t;

#define INCLUDE_MCALL(_name, _id , _callback)		\
	const mcall_t _name _SECTION(".mcall") =	\
	{						\
		.id		= _id,			\
		.callback	= _callback		\
	}
