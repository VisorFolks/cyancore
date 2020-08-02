#include <status.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <mmio.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <device.h>
#include <hal/gpio.h>
#include "gpio_private.h"

#if N_PORT
status_t gpio_setup(gpio_port_t *port, uint8_t portID, uint8_t pinID)
{
	mret_t mres;
	gpio_module_t *dp;
	assert(port);
	if(portID >= N_PORT)
		return error_inval_arg;
	port->pin = pinID;
	port->port = portID;
	mres = arch_machine_call(FETCH_DP, DEV_GPIO, portID, 0);
	if(mres.status != success)
		return mres.status;
	dp = (gpio_module_t *)mres.p;
	port->pbaddr = dp->baddr;
	return success;
}

status_t gpio_pin_mode(gpio_port_t *port, gpio_mode_t mode)
{
	uintptr_t pbaddr;
	assert(port);
	uint8_t pin = port->pin;
	pbaddr = port->pbaddr;

	switch(mode)
	{
		case out:
			MMIO8(pbaddr + DDR_OFFSET) |= (1 << pin);
			break;
		case pull_up:
			MMIO8(pbaddr + PORT_OFFSET) |= (1 << pin);
		case in:
			MMIO8(pbaddr + DDR_OFFSET) &= ~(1 << pin);
			break;
		default:
			return error_inval_arg;
	}
	return success;
}

status_t gpio_pin_set(gpio_port_t *port)
{
	assert(port);
	MMIO8(port->pbaddr + PORT_OFFSET) |= (1 << port->pin);
	return success;
}

status_t gpio_pin_clear(gpio_port_t *port)
{
	assert(port);
	MMIO8(port->pbaddr + PORT_OFFSET) &= ~(1 << port->pin);
	return success;
}

status_t gpio_pin_toggle(gpio_port_t *port)
{
	assert(port);
	MMIO8(port->pbaddr + PORT_OFFSET) ^= (1 << port->pin);
	return success;
}

bool gpio_pin_read(gpio_port_t *port)
{
	assert(port);
	return (MMIO8(port->pbaddr + PIN_OFFSET) & (1 << port->pin)) ? true : false;
}

status_t gpio_port_write(gpio_port_t *port, gpio_parallel_t val)
{
	assert(port);
	// MegaAVR has 8-bit i/o modules, value to write should be 8-bit wide
	MMIO8(port->pbaddr + PORT_OFFSET) = (uint8_t)(val & 0xff);
	return success;
}

status_t gpio_port_read(gpio_port_t *port, gpio_parallel_t *val)
{
	assert(port);
	// MegaAVR has 8-bit i/o modules, value returned is 8-bit wide
	*val = (gpio_parallel_t)MMIO8(port->pbaddr + PIN_OFFSET);
	return success;
}
#endif
