#pragma once

#include <reset.h>

reset_t platform_get_reset_syndrome();
void platform_reset_handler();
void platform_early_setup();
void platform_setup();
void platform_cpu_setup();
