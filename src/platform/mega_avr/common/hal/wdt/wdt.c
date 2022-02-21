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
#include <syslog.h>
#include <mmio.h>
#include <assert.h>
#include <interrupt.h>
#include <lock/lock.h>
#include <plat_arch.h>
#include <arch.h>
#include <hal/wdt.h>
#include "wdt_private.h"

/**
 * wdt_lock - Lock used by wdt HAL driver.
 */
static lock_t wdt_lock;

/**
 * get_timeout
 *
 * @brief This function returns the timeout value formatted
 * as per the register's bitfields.
 *
 * @param[in] timeout: WDog timeout, [0-9] are valid values
 * @return timeout: formatted value
 */
static inline uint8_t get_timeout(size_t timeout)
{
	uint8_t temp;
	sysdbg5("Configuring WDT timeout gear to %u\n", timeout);
	temp = (timeout & 0xf);
	timeout = (temp & ((1 << WDP0) | (1 << WDP1) | (1 << WDP2)));
	timeout |= ((temp >> 3) << WDP3);
	return (uint8_t) timeout;
}

/**
 * wdt_setup - configures timeout for wdt and enables wbark mode
 *
 * @brief This function configues watchdog interrupt handler for bark
 * irq followed by resetting of wddt device.
 *
 * @param[in] *port: Driver instance for watchdog
 * @param[in] timeout: Watchdog timeout value
 *
 * @return status: return the execution status of wdt_setup
 */
status_t wdt_setup(const wdt_port_t *port)
{
	status_t ret;
	assert(port);

	if(port->wdt_handler == NULL)
		return error_func_inval_arg;

	sysdbg5("Linking WDT IRQ to arch mode IRQ#%u\n", port->wdt_irq);
	ret = link_interrupt(arch, port->wdt_irq, port->wdt_handler);

	lock_acquire(&wdt_lock);
	arch_di_save_state();
	arch_wdt_reset();
	write_wdtcsr(0);
	arch_ei_restore_state();
	lock_release(&wdt_lock);

	if(MMIO8(WDTCSR) != 0)
		ret |= error_driver_init_failed;
	return ret;
}

/**
 * wdt_shutdown - disables watchdog
 *
 * @brief This function unlinks bark IRQ and resets wdt
 *
 * @param[in] *port: Driver instance for watchdog
 *
 * @return status: returns the execution status of wdt_shutdown
 */
status_t wdt_shutdown(const wdt_port_t *port)
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

	if(MMIO8(WDTCSR) != 0)
		return error_driver_data;
	return success;
}

/**
 * wdt_set_timeout - writes timeout to config register
 *
 * @brief This function configures timeout for wdt and enables
 * interrupt.
 *
 * @param[in] *port: Driver instance for watchdog
 *
 * @return status: returns the execution status of wdt_set_timeout
 */
status_t wdt_set_timeout(const wdt_port_t *port)
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
		ret |= error_driver_init_failed;
	return ret;
}

/**
 * wdt_hush - reset watchdog counter
 *
 * @brief This function resets the watchdog timer counter
 * register by performing arch call, which internally executes
 * an instruction "wdr".
 *
 * @param[in] *port: (Unused) In this cases, it is not used
 */
void wdt_hush(const wdt_port_t *port _UNUSED)
{
	assert(port);
	arch_wdt_reset();
}

/**
 * wdt_sre - watchdog system reset enable
 *
 * @brief This function enables system reset after watchdog bark event.
 *
 * @param[in] *port: Driver instance for watchdog
 *
 * @return status: return the execution status of wdt_sre
 */
status_t wdt_sre(const wdt_port_t *port)
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
		return error_driver_init_failed;

	return success;
}

/**
 * wdt_srd - watchdog system reset disable
 *
 * @brief This function disables system reset after watchdog bark event.
 *
 * @param[in] *port: Driver instance for watchdog
 *
 * @return status: return the execution status of wdt_srd
 */
status_t wdt_srd(const wdt_port_t *port)
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
		return error_driver_init_failed;

	return success;
}
