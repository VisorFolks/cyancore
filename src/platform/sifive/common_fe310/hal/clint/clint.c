/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: clint.c
 * Description		: This file contains sources of CLINT core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <stdlib.h>
#include <assert.h>
#include <arch.h>
#include <machine_call.h>
#include <resource.h>
#include <hal/clint.h>
#include <driver.h>
#include <mmio.h>
#include <platform.h>

#ifndef PLIC_VERSION
#define PLIC_VERSION	0x0100		// 01.00
#endif

#include "clint_private.h"

static clint_port_t *port;

static status_t clint_setup()
{
	mret_t mres;
	const module_t *dp;

	arch_machine_call(fetch_dp, clint, 0, 0, &mres);

	if(mres.status != success)
		return mres.status;

	port = (clint_port_t *)malloc(sizeof(clint_port_t));
	if(!port)
		return error_memory_low;

	dp = (module_t *)mres.p;
	port->baddr = dp->baddr;
	port->stride = dp->stride;
	port->port_id = clint;
	MMIO64(port->baddr + MTIME_OFFSET) = 0;
	return success;
}

static status_t clint_exit()
{
	free(port);
	return success;
}

status_t clint_send_softirq(size_t core_id)
{
	assert(port->baddr);
	if(core_id >= N_CORES)
		return error_func_inval_arg;
	MMIO32(port->baddr + MSIP_OFFSET(core_id)) = 1;
	arch_dsb();
	return success;
}

status_t clint_config_tcmp(size_t core_id, uint64_t value)
{
	assert(port->baddr);
	if(core_id >= N_CORES)
		return error_func_inval_arg;
	MMIO64(port->baddr + MTCMP_OFFSET(core_id)) = value;
	arch_dsb();
	return success;
}

uint64_t clint_read_time()
{
	assert(port->baddr);
	uint64_t time_stamp;
	time_stamp = MMIO64(port->baddr + MTIME_OFFSET);
	return time_stamp;
}

INCLUDE_DRIVER(plat_clint, clint_setup, clint_exit, 0, 0, 0);
