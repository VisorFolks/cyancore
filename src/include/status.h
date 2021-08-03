/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: status.h
 * Description		: This file consists of return status codes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STATUS_H_

#include <compiler_macros.h>

typedef enum status
{
	error_assertion		= -8,
	error_inval_dev_id	= -7,
	error_inval_code	= -6,
	error_data		= -5,
	error_busy		= -4,
	error_inval_func	= -3,
	error_inval_arg		= -2,
	error			= -1,
	success			= 0,
} status_t;
