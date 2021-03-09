/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_bss_clear.S
 * Description		: This file contains platform bss clear routine
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <string.h>
#include <status.h>
#include <platform.h>

extern uint16_t _bss_start, _bss_size;

status_t platform_bss_clear()
{
	memset(&_bss_start, 0, (size_t)&_bss_size);
	return success;
}
