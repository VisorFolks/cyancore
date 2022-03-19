/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: prci.c
 * Description		: This file contains prototypes of platform
 *			  power, reset, clock and interrupt module
 *			  functions and api calls
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <hal/sysclk.h>
#include <assert.h>
#include <arch.h>
#include "prci_private.h"

status_t sysclk_configure(sysclk_port_t *port, clock_type_t type)
{
	status_t ret = success;
	assert(port);
	istate_t istate;
	lock_acquire(&port->key);
	arch_di_save_state(&istate);
	port->type = type;
	arch_ei_restore_state(&istate);
	lock_release(&port->key);
	return ret;
}

status_t sysclk_set_clk(sysclk_port_t *port, unsigned int hz _UNUSED)
{
	status_t ret = success;
	assert(port);
	istate_t istate;
	lock_acquire(&port->key);
	arch_di_save_state(&istate);

	arch_ei_restore_state(&istate);
	lock_release(&port->key);
	return ret;
}

status_t sysclk_get_clk(sysclk_port_t *port, unsigned int *hz _UNUSED)
{
	status_t ret = success;
	assert(port);
	istate_t istate;
	lock_acquire(&port->key);
	arch_di_save_state(&istate);

	arch_ei_restore_state(&istate);
	lock_release(&port->key);
	return ret;
}

