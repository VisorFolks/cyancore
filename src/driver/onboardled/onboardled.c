/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: onboardled.c
 * Description		: This file contains sources of onboardled driver
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <stdlib.h>
#include <resource.h>
#include <machine_call.h>
#include <lock/lock.h>
#include <driver.h>
#include <driver/onboardled.h>
#include <hal/gpio.h>

static gpio_port_t *obledPort;
static swdev_t *obled_sp;
static lock_t obledlock;

status_t onboardled_toggle(void)
{
	status_t ret = success;
	lock_acquire(&obledlock);
	if(!obled_sp)
	{
		ret = error_driver_init_failed;
		goto exit;
	}
	for(uint8_t i = 0; i < obled_sp->pmux->npins; i++)
		ret |= gpio_pin_toggle(&obledPort[i]);
exit:
	lock_release(&obledlock);
	return ret;
}

status_t onboardled_on(void)
{
	status_t ret = success;
	lock_acquire(&obledlock);
	if(!obled_sp)
	{
		ret = error_driver_init_failed;
		goto exit;
	}
	for(uint8_t i = 0; i < obled_sp->pmux->npins; i++)
		ret |= gpio_pin_set(&obledPort[i]);
exit:
	lock_release(&obledlock);
	return ret;
}

status_t onboardled_off(void)
{
	status_t ret = success;
	lock_acquire(&obledlock);
	if(!obled_sp)
	{
		ret = error_driver_init_failed;
		goto exit;
	}
	for(uint8_t i = 0; i < obled_sp->pmux->npins; i++)
		ret |= gpio_pin_clear(&obledPort[i]);
exit:
	lock_release(&obledlock);
	return ret;
}

static status_t onboardled_setup(void)
{
	mret_t mres;
	status_t ret;

	lock_acquire(&obledlock);
	arch_machine_call(fetch_sp, onboard_led, 0, 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("%p - sp node could not be found!\n", onboard_led);
		ret = mres.status;
		goto exit;
	}
	obled_sp = (swdev_t *) mres.p;
	ret = mres.status;

	obledPort = (gpio_port_t *)malloc(sizeof(gpio_port_t));

	for(uint8_t i = 0; i < obled_sp->pmux->npins; i++)
	{
		ret |= gpio_pin_alloc(&obledPort[i], obled_sp->pmux->port, obled_sp->pmux->pins[i]);
		ret |= gpio_pin_mode(&obledPort[i], out);
	}
exit:
	lock_release(&obledlock);
	return ret;
}

static status_t onboardled_exit(void)
{
	status_t ret = success;
	lock_acquire(&obledlock);
	if(!obled_sp)
	if(!obled_sp)
	{
		ret = error_driver_init_failed;
		goto exit;
	}
	for(uint8_t i = 0; i < obled_sp->pmux->npins; i++)
	{
		ret |= gpio_pin_free(&obledPort[i]);
		free(&obledPort[i]);
	}
	obled_sp = NULL;
exit:
	lock_release(&obledlock);
	return ret;
}

INCLUDE_DRIVER(OBrdLED, onboardled_setup, onboardled_exit, 0, 255, 255);
