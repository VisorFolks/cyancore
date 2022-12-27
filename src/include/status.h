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
#include <utils.h>

typedef enum status
{
	success				=  0x0000,
/* Generic error */
	error_generic			= -0x0001,
	error_func_inval		= -0x0002,
	error_func_inval_arg		= -0x0003,
	error_overflow			= -0x0004,
/* Driver related error */
	error_driver			= -0x0100,
	error_driver_init_done		= -0x0101,
	error_driver_init_failed	= -0x0102,
	error_driver_busy		= -0x0103,
	error_driver_data		= -0x0104,
/* Device related error */
	error_device			= -0x0200,
	error_device_id_inval		= -0x0201,
	error_device_inval		= -0x0202,
	error_device_busy		= -0x0203,
/* Machine Call related error */
	error_mcall			= -0x0300,
	error_mcall_code_inval		= -0x0301,
/* hcall related error */
	error_hcall			= -0x0400,
/* Syscall related error */
	error_scall			= -0x0500,
	error_scall_code_inval		= -0x0501,
/* Memory related error */
	error_memory			= -0x0600,
	error_memory_low		= -0x0601,
/* File related error */
	error_file			= -0x0700,
	error_file_desc			= -0x0701,
	error_file_exist		= -0x0702,
	error_file_not_found		= -0x0703,
	error_file_no_space		= -0x0704,
	error_file_long_name		= -0x0705,
	error_file_io			= -0x0706,
/* String related error */
	error_string			= -0x0800,
/* Math related error */
	error_math			= -0x0900,
	error_math_inval_arg		= -0x0901,
	error_math_large_val		= -0x0902,
/* Access related error */
	error_access			= -0x0a00,
/* System related error */
	error_system			= -0x0b00,
	error_system_irq_link_fail	= -0x0b01,
	error_system_irq_unlink_fail	= -0x0b02,
	error_system_clk_caliberation	= -0x0b03,
/* Network related error */
	error_net			= -0x0c00,
	error_net_con_timeout		= -0x0c01,
/* User space related error */
	error_user			= -0x0d00,
/* IO related error */
	error_io			= -0x0e00,
/* OS related error */
	error_os			= -0x0f00,
	error_os_task_overfow		= -0x0f01,
	error_os_deadlock		= -0x0f02,
	error_os_invalid_op		= -0x0f03,
	error_os_sem_get		= -0x0f04,
/* Mesg related error */
	error_mesg			= -0x1000,
	error_mesg_long			= -0x1001,
/* List related error */
	error_list			= -0x1100,
	error_list_node_exists		= -0x1101,
	error_list_node_not_found	= -0x1102,
} status_t;
