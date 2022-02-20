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
#include <syslog.h>
#include <stdbool.h>
#include <assert.h>
#include <mmio.h>
#include <resource.h>
#include <arch.h>
#include <lock/lock.h>
#include <hal/gpio.h>
#include "gpio_private.h"

status_t gpio_pin_alloc(gpio_port_t *port, uint8_t portID, uint8_t pinID)
{
	mret_t mres;
	const gpio_module_t *dp;
	unsigned char flag;

	assert(port);

	lock_acquire(&gpio_lock);
	flag = 0;
	if(port_status[portID] & (1 << pinID))
		flag = 1;
	else
		port_status[portID] |= (1 << pinID);
	lock_release(&gpio_lock);

	if(flag)
	{
		sysdbg("GPIO Pin %d on Port %d is already taken\n", pinID, portID);
		return error_driver_busy;
	}

	port->pin = pinID;
	port->port = portID;
	arch_machine_call(fetch_dp, gpio, portID, 0, &mres);
	if(mres.status != success)
	{
		sysdbg("GPIO Port %d not found in DP\n", portID);
		return mres.status;
	}
	dp = (gpio_module_t *)mres.p;
	port->pbaddr = dp->baddr;
	sysdbg("GPIO engine @ %p\n", dp->baddr);
	sysdbg("Using GPIO Pin %d on Port %d\n", port->pin, port->port);
	return success;
}

status_t gpio_pin_mode(const gpio_port_t *port, gpio_mode_t mode)
{
	uintptr_t baddr;
	uint8_t pin;
	assert(port);
	pin = port->pin;
	baddr = port->pbaddr;

	MMIO32(baddr + OUTPUTEN_OFFSET) &= ~(1 << pin);
	MMIO32(baddr + INPUTEN_OFFSET) &= ~(1 << pin);
	MMIO32(baddr + PUE_OFFSET) &= ~(1 << pin);

	arch_dsb();

	switch(mode)
	{
		case out:
			MMIO32(baddr + OUTPUTEN_OFFSET) |= (1 << pin);
			break;
		case pull_up:
			MMIO32(baddr + PUE_OFFSET) |= (1 << pin);
			break;
		case in:
			MMIO32(baddr + INPUTEN_OFFSET) |= (1 << pin);
			break;
		default:
			return error_func_inval_arg;
	}
	return success;
}

status_t gpio_pin_free(gpio_port_t *port)
{
	assert(port);
	lock_acquire(&gpio_lock);
	sysdbg("Releasing GPIO Pin %d on Port, %d", port->pin, port->port);
	port_status[port->port] &= ~(1 << port->pin);
	port->pbaddr = 0;
	port->port = 0;
	port->pin = 0;
	lock_release(&gpio_lock);
	return success;
}

status_t gpio_pin_set(const gpio_port_t *port)
{
	assert(port);
	MMIO32(port->pbaddr + OUTPUTVAL_OFFSET) |= (1 << port->pin);
	return success;
}

status_t gpio_pin_clear(const gpio_port_t *port)
{
	assert(port);
	MMIO32(port->pbaddr + OUTPUTVAL_OFFSET) &= ~(1 << port->pin);
	return success;
}

status_t gpio_pin_toggle(const gpio_port_t *port)
{
	assert(port);
	MMIO32(port->pbaddr + OUTPUTVAL_OFFSET) ^= (1 << port->pin);
	return success;
}

bool gpio_pin_read(const gpio_port_t *port)
{
	assert(port);
	return (MMIO32(port->pbaddr + INPUTVAL_OFFSET) & (1 << port->pin)) ? true : false;
}
