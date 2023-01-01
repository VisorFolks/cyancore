/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: pwm.h
 * Description		: This file consists of PWM-HAL prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _PWM_H_

#include <stdint.h>
#include <status.h>
#include <resource.h>
#include <hal/gpio.h>

typedef struct pwm_port
{
	hw_devid_t port_id;
	unsigned int clk_id;
	uintptr_t baddr;
	uintptr_t stride;
	size_t prescale;
	irqs_t *pwm_irq;
	void (*pwm_handler)(void);
	pinmux_t *pmux;
	gpio_port_t io;
} pwm_port_t;

status_t pwm_get_properties(pwm_port_t *, sw_devid_t);
status_t pwm_setup(const pwm_port_t *, unsigned int);
status_t pwm_set(const pwm_port_t *, size_t value, bool invert);
