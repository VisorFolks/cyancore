/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: platform.h
 * Description		: This file contains prototypes of platform apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _RP2_PLATFORM_H_

#include <status.h>

void plat_panic_handler(void);
void platform_print_cpu_info(void);
status_t platform_copy_data(void);
status_t platform_bss_clear(void);
status_t platform_resources_setup(void);
status_t platform_sysclk_reset(void);
