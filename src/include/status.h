#pragma once

typedef enum status
{
	error_data		=- 5,
	error_busy		= -4,
	error_inval_func	= -3,
	error_inval_arg		= -2,
	error			= -1,
	success			= 0,
} status_t;
