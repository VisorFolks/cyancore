/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: prci.c
 * Description		: This file contains prototypes of platform
 *			  power, reset, clock and interrupt module
 *			  functions and api calls
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <stddef.h>
#include <mmmio.h>
#include <platform.h>
#include <hal/pll.h>
#include <arch.h>
#include <machine_call.h>
#include "prci_private.h"

status_t pll_setup(pll_port_t *port)
{
}

status_t pll_set_clk(pll_port_t *port, unsigned long clock)
{
}

status_t pll_get_clk(pll_port_t *port, unsigned long *clock)
{
}
