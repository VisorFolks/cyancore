/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: wdt.h
 * Description		: This file consists of WDT-HAL prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _WDT_H_

#include <stdint.h>
#include <stdbool.h>
#include <status.h>
#include <resource.h>

typedef struct wdt_port
{
	hw_devid_t port_id;
	unsigned int clk_id;
	uintptr_t baddr;
	uintptr_t stride;
	size_t wdt_irq;
	size_t timeout;
	void (*wdt_handler)(void);
} wdt_port_t;

status_t wdt_setup(const wdt_port_t *);
status_t wdt_shutdown(const wdt_port_t *);
status_t wdt_set_timeout(const wdt_port_t *);
void wdt_hush(const wdt_port_t *);
status_t wdt_sre(const wdt_port_t *);
status_t wdt_srd(const wdt_port_t *);
