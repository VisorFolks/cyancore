/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: timer.c
 * Description		: This file contains sources for mega-avr
 *			  HAL timer/pwm apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <lock/lock.h>
#include <status.h>
#include <mmio.h>
#include <interrupt.h>
#include <platform.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <hal/timer.h>
#include "timer8.h"
#include "timer16.h"

status_t timer_setup(const timer_port_t *port, unsigned int mode, unsigned int ps)
{
	status_t ret;
	unsigned id;
	assert(port);
	id = port->port_id & 0xf0;
	ret = platform_clk_en(port->clk_id);
	if(id == 0 || id == 0x20)
	{
		if(port->tmr_handler)
		{
			timer8_set(port, port->value);
			ret |= link_interrupt(int_arch, port->tmr_irq, port->tmr_handler);
			timer8_irq_en(port);
		}
		timer8_config_mode(port, mode);
		timer8_config_ps(port, ps);
	}
	else
	{
		if(port->tmr_handler)
		{
			timer16_set(port, port->value);
			ret |= link_interrupt(int_arch, port->tmr_irq, port->tmr_handler);
			timer16_irq_en(port);
		}
		timer16_config_mode(port, mode);
		timer16_config_ps(port, ps);
	}
	return ret;
}

status_t timer_shutdown(const timer_port_t *port)
{
	status_t ret = success;
	unsigned id;
	assert(port);
	id = port->port_id & 0xf0;
	if(id == 0 || id == 0x20)
	{
		timer8_config_mode(port, 0);
		timer8_config_ps(port, 0);
		timer8_irq_dis(port);
	}
	else
	{
		timer16_config_mode(port, 0);
		timer16_config_ps(port, 0);
		timer16_irq_dis(port);
	}
	ret |= unlink_interrupt(int_arch, port->tmr_irq);
	ret |= platform_clk_dis(port->clk_id);
	return ret;
}

status_t timer_read(const timer_port_t *port, size_t *value)
{
	unsigned id;
	assert(port);
	id = port->port_id & 0xf0;
	if(id == 0 || id == 0x20)
		*value = timer8_read(port);
	else
		*value = timer16_read(port);
	return success;
}


status_t timer_pwm_set(const timer_port_t *port, bool invert, size_t value)
{
	status_t ret = success;
	unsigned id;
	assert(port);
	id = port->port_id & 0xf0;
	if(id == 0 || id == 0x20)
	{
		timer8_config_op_mode(port, 1, invert);
		timer8_set(port, (uint8_t)value);
	}
	else
	{
		timer16_config_op_mode(port, 1, invert);
		timer16_set(port, value);
	}
	return ret;
}

