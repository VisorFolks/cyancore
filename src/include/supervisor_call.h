/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: supervisor_call.h
 * Description		: This file consists of supervisor call IDs and prototypes
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _SUPER_CALL_H_

#include <stdint.h>
#include <status.h>

// Supervisor call IDs
typedef enum scall_id
{
	scall_def_placeholder
} scall_id_t;

typedef struct sret
{
	uintptr_t p;
	size_t size;
	status_t status;
} sret_t;

typedef struct scall
{
	scall_id_t id;
	sret_t (*callback)(unsigned int a0, unsigned int a1, unsigned int a2);
} scall_t;

#define INCLUDE_SCALL(_name, _id , _callback)		\
	const scall_t _name _SECTION(".scall") =	\
	{						\
		.id		= _id,			\
		.callback	= _callback		\
	}
