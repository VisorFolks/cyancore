/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: gpio.c
 * Description		: This file contains macors used by gpio HAL
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <mmio.h>
#include <arch.h>
#include <aon.h>
#include "aon_private.h"

status_t aon_pmucause(aon_port_t *port, uint32_t *reset_val)
{
	if(!port)
		return error_func_inval_arg;
	*reset_val = MMIO32(port->baddr + PMUCAUSE_OFFSET);
	return success;
}
