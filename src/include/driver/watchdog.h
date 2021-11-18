
/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: watchdog.h
 * Description		: This file consists of watchdog core prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _WATCHDOG_H_

typedef struct wdog
{
	status_t (*setup)(void);
	status_t (*hush)(void);
} wdog_t;

status_t wdog_attach_device(wdog_t *);
status_t wdog_release_device();
status_t wdog_hush();
void wdog_reset_handler();

