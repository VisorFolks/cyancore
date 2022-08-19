/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019-2022, Cyancore Team
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

// Machine call IDs
typedef enum mcall_id
{
	fetch_sp		= 0x0001,
	fetch_dp		= 0x0002,
	set_sleep_mode		= 0x0003,
	fetch_clk		= 0x0004,
	config_clk		= 0x0005,
} mcall_id_t;

typedef struct mret
{
	uintptr_t p;
	size_t size;
	status_t status;
} mret_t;

#include <arch.h>

typedef struct mcall
{
	mcall_id_t id;
	void (*callback)(call_arg_t a0, call_arg_t a1, call_arg_t a2, mret_t *ret);
} mcall_t;

#define INCLUDE_MCALL(_name, _id , _callback)		\
	const mcall_t _name _SECTION(".ecall") =	\
	{						\
		.id		= _id,			\
		.callback	= _callback		\
	}
