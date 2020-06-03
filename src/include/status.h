#pragma once
#define _STATUS_H_

#include <compiler_macros.h>

typedef enum status
{
	error_inval_dev_id	= -7,
	error_inval_code	= -6,
	error_data		= -5,
	error_busy		= -4,
	error_inval_func	= -3,
	error_inval_arg		= -2,
	error			= -1,
	success			= 0,
} status_t;
