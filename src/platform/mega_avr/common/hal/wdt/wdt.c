/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: wdt.c
 * Description		: This file contains wdt HAL driver api
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <status.h>
#include <mmio.h>
#include <assert.h>
#include <interrupt.h>
#include <lock/lock.h>
#include <plat_arch.h>
#include <arch.h>
#include <hal/wdt.h>
#include "wdt_private.h"

static lock_t wdt_lock;

static inline uint8_t get_timeout(size_t timeout)
{
	uint8_t temp;
	temp = (timeout & 0xf);
	timeout = (temp & ((1 << WDP0) | (1 << WDP1) | (1 << WDP2)));
	timeout |= ((temp >> 3) << WDP3);
	return (uint8_t) timeout;
}

/**
 * wdt_setup - configures timeout for wdt and enables wbark mode
 *
 * @brief This function configues watchdog timeout and enables watchdog
 * interrupt. Internally this function will link the irq_id and handler
 * passed via driver instance.
 *
 * @param[in] *port: Driver instance for watchdog
 * @param[in] timeout: Watchdog timeout value
 *
 * @return status: return the execution status of wdt_setup
 */
status_t wdt_setup(wdt_port_t *port)
{
	status_t ret;
	assert(port);

	if(port->wdt_handler == NULL)
		return error_inval_arg;

	ret = link_interrupt(arch, port->wdt_irq, port->wdt_handler);

	lock_acquire(&wdt_lock);
	arch_di_save_state();
	arch_wdt_reset();
	write_wdtcsr(0);
	arch_ei_restore_state();
	lock_release(&wdt_lock);

	if(MMIO8(WDTCSR) != 0)
		ret |= error_init_not_done;
	return ret;
}

status_t wdt_shutdown(wdt_port_t *port)
{
	assert(port);
	lock_acquire(&wdt_lock);
	arch_di_save_state();
	arch_wdt_reset();
	MMIO8(MCUSR) &= ~(1 << MCUSR_WDRF);
	write_wdtcsr(0);
	unlink_interrupt(arch, port->wdt_irq);
	arch_ei_restore_state();
	lock_release(&wdt_lock);
	return success;
}

status_t wdt_set_timeout(wdt_port_t *port)
{
	status_t ret = success;
	uint8_t timeout;
	assert(port);
	assert(port->timeout <= 9);

	timeout = get_timeout(port->timeout);
	if(timeout)
		timeout |= (1 << WDIE);

	lock_acquire(&wdt_lock);
	arch_di_save_state();
	arch_wdt_reset();
	write_wdtcsr((uint8_t) timeout);
	arch_ei_restore_state();
	lock_release(&wdt_lock);

	if(MMIO8(WDTCSR) != timeout)
		ret |= error_init_not_done;
	return ret;
}

void wdt_hush(wdt_port_t *port _UNUSED)
{
	arch_wdt_reset();
}

status_t wdt_sre(wdt_port_t *port)
{
	assert(port);
	uint8_t val = MMIO8(WDTCSR);
	val |= (1 << WDE);

	lock_acquire(&wdt_lock);
	arch_di_save_state();
	arch_wdt_reset();
	write_wdtcsr(val);
	arch_ei_restore_state();
	lock_release(&wdt_lock);

	if(MMIO8(WDTCSR) != val)
		return error_init_not_done;

	return success;
}

status_t wdt_srd(wdt_port_t *port)
{
	assert(port);
	uint8_t val = MMIO8(WDTCSR);
	val &= ~(1 << WDE);

	lock_acquire(&wdt_lock);
	arch_di_save_state();
	arch_wdt_reset();
	write_wdtcsr(val);
	arch_ei_restore_state();
	lock_release(&wdt_lock);

	if(MMIO8(WDTCSR) != val)
		return error_init_not_done;

	return success;
}
