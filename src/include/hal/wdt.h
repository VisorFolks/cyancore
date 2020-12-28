#pragma once
#define _WDT_H_

#include <stdint.h>
#include <stdbool.h>
#include <status.h>

typedef enum wdc_mode
{
	wnone = 0,
	wbark = 1,
	wbite = 2,
} wdt_mode_t;

typedef struct wdt_port
{
	uint8_t port_id;
	unsigned int clk_id;
	uintptr_t baddr;
	uintptr_t stride;
	size_t wdt_irq;
	void (*wdt_handler)(void);
} wdt_port_t;

status_t wdt_setup(wdt_port_t *, wdt_mode_t, uint8_t);
status_t wdt_dis(wdt_port_t *);
status_t wdt_int_en(wdt_port_t *);
status_t wdt_int_dis(wdt_port_t *);
bool wdt_exp_status(wdt_port_t *);
