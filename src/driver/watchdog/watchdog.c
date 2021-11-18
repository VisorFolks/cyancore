
/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: console.c
 * Description		: This file contains sources of watchdog engine
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <status.h>
#include <arch.h>
#include <driver/watchdog.h>

static wdog_t *port[N_CORES];

static bool wdog_attached[N_CORES] = {[0 ... N_CORES-1] = false};

status_t wdog_attach_device(wdog_t *pwdog)
{
	status_t ret;
	size_t cpu_id = arch_core_id();

	port[cpu_id] = pwdog;

	if(port[cpu_id] != NULL)
	{
		ret = port[cpu_id]->setup();
		wdog_attached[cpu_id] = (ret == success) ? true : false;
	}
	else
		ret = error_inval_arg;
	return ret;
}

status_t wdog_release_device()
{
	size_t cpu_id = arch_core_id();
	port[cpu_id] = NULL;
	wdog_attached[cpu_id] = false;
	return success;
}

status_t wdog_hush()
{
	size_t cpu_id = arch_core_id();
	if(wdog_attached[cpu_id] && port[cpu_id]->hush != NULL)
	{
		port[cpu_id]->hush();
		return success;
	}
	return error_inval_func;
}

extern void plat_panic_handler();
void wdog_reset_handler()
{
	printf("\n< x > Watchdog Bite on Core: [%d]\n", (int)arch_core_id());
	plat_panic_handler();
}
