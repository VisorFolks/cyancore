/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: platform_mem.c
 * Description		: This file contains implementation of platform early setup APIs.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <string.h>
#include <platform.h>

extern uintptr_t _bss_start, _bss_size, _data_start, _data_size,
                 _data_vstart;

status_t platform_bss_clear()
{
	memset(&_bss_start, 0, (size_t)&_bss_size);
	return success;
}

status_t platform_copy_data()
{
	memcpy(&_data_vstart, &_data_start, (size_t)&_data_size);
	return success;
}
