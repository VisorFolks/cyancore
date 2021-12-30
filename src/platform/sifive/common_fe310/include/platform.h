/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform.h
 * Description		: This file contains prototypes of platform apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _SIFIVE_PLATFORM_H_

#include <status.h>

void plat_panic_handler();
status_t platform_copy_itim();
status_t platform_copy_data();
status_t platform_bss_clear();
status_t platform_resources_setup();
status_t platform_clk_reset();
status_t platform_clk_en(unsigned int);
status_t platform_clk_dis(unsigned int);
status_t platform_wdt_reset();
