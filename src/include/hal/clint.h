/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: clint.h
 * Description		: This file consists of CLINT-HAL prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _CLINT_H_

status_t clint_send_softirq(size_t);
status_t clint_config_tcmp(size_t, uint64_t);
uint64_t clint_read_time();
