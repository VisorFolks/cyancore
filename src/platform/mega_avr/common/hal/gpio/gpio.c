#include <status.h>
#include <stdint.h>
#include <stdbool.h>
#include <mmio.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <device.h>
#include <hal/gpio.h>
#include "gpio_private.h"

#if N_PORT
uintptr_t port_baddr[N_PORT];

status_t gpio_setup()
{
	mret_t mres;
	gpio_module_t *dp;
	for(uint8_t i = 0; i < N_PORT; i++)
	{
		mres = arch_machine_call(FETCH_DP, DEV_GPIO, i, 0);
		if(mres.status != success)
			return mres.status;
		dp = (gpio_module_t *)mres.p;
		port_baddr[i] = dp->baddr;
	}
	return success;
}

status_t gpio_pin_config(uint8_t port_id, uint8_t pin, gpio_mode_t mode)
{
	uintptr_t pbaddr;
	if(port_id >= N_PORT)
		return error_inval_arg;

	pbaddr = port_baddr[port_id];

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

status_t gpio_pin_set(uint8_t port_id, uint8_t pin)
{
	if(port_id >= N_PORT)
		return error_inval_arg;
	MMIO8(port_baddr[port_id] + PORT_OFFSET) |= (1 << pin);
	return success;
}

status_t gpio_pin_clear(uint8_t port_id, uint8_t pin)
{
	if(port_id >= N_PORT)
		return error_inval_arg;
	MMIO8(port_baddr[port_id] + PORT_OFFSET) &= ~(1 << pin);
	return success;
}

status_t gpio_pin_toggle(uint8_t port_id, uint8_t pin)
{
	if(port_id >= N_PORT)
		return error_inval_arg;
	MMIO8(port_baddr[port_id] + PORT_OFFSET) ^= (1 << pin);
	return success;
}

bool gpio_pin_read(uint8_t port_id, uint8_t pin)
{
	if(port_id >= N_PORT)
		return false;
	return (MMIO8(port_baddr[port_id] + PIN_OFFSET) & (1 << pin)) ? true : false;
}

status_t gpio_port_write(uint8_t port_id, uint8_t val)
{
	if(port_id >= N_PORT)
		return error_inval_arg;
	MMIO8(port_baddr[port_id] + PORT_OFFSET) = val;
	return success;
}

status_t gpio_port_read(uint8_t port_id, uint8_t *val)
{
	if(port_id >= N_PORT)
		return error_inval_arg;
	*val = MMIO8(port_baddr[port_id] + PIN_OFFSET);
	return success;
}
#endif
