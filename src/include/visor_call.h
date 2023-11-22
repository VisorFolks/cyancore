/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019-2023, Cyancore Team
 *
 * File Name		: visor_call.h
 * Description		: This file consists of visor call utils and 
 *			  data types
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _VISOR_CALL_H_

#include <stdint.h>
#include <status.h>
#include <vcall_id.h>

typedef struct mret
{
	uintptr_t p;
	size_t size;
	status_t status;
} vret_t;

#include <arch.h>

typedef struct vcall
{
	vcall_id_t id;
	void (*callback)(call_arg_t a0, call_arg_t a1, call_arg_t a2, vret_t *ret);
} vcall_t;

#define INCLUDE_VCALL(_name, _id , _callback)		\
	const vcall_t _name _SECTION(".vcall") =	\
	{						\
		.id		= _id,			\
		.callback	= _callback		\
	}
