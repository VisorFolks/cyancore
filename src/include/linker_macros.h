/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: linker_macro.h
 * Description		: This file defines the linker macro utilities
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define DRIVER_TABLE					\
		PROVIDE(_driver_table_start = .);	\
		KEEP(*(.driver))			\
		PROVIDE(_driver_table_end = .);

#define ECALL_TABLE					\
		PROVIDE(_ecall_table_start = .);	\
		KEEP(*(.ecall))				\
		PROVIDE(_ecall_table_end = .);
