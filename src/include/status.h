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
	success				= 0x0000,
	error_generic			= -0x0001,
	error_func_inval		= -0x0002,
	error_func_inval_arg		= -0x0003,
	error_driver			= -0x0100,
	error_driver_init_done		= -0x0101,
	error_driver_init_failed	= -0x0102,
	error_driver_busy		= -0x0103,
	error_driver_data		= -0x0104,
	error_device			= -0x0200,
	error_device_id_inval		= -0x0201,
	error_device_inval		= -0x0202,
	error_mcall			= -0x0300,
	error_mcall_code_inval		= -0x0301,
	error_hcall			= -0x0400,
	error_scall			= -0x0500,
	error_memory			= -0x0600,
	error_file			= -0x0700,
	error_string			= -0x0800,
	error_math			= -0x0900,
	error_math_inval_arg		= -0x0901,
	error_access			= -0x0a00,
	error_system			= -0x0b00,
	error_system_irq_link_fail	= -0x0b01,
	error_system_irq_unlink_fail	= -0x0b02,
	error_network			= -0x0c00,
	error_user			= -0x0d00,
	error_io			= -0x0e00,
} status_t;
