#pragma once
#define _MEGA_AVR_PLATFORM_H_

status_t platform_fetch_dp(unsigned int, unsigned int*);
status_t platform_set_sleep_mode(const uint8_t);
