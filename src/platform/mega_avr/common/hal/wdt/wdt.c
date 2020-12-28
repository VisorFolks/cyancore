#include <stdint.h>
#include <stdbool.h>
#include <status.h>
#include <mmio.h>
#include <assert.h>
#include <plat_arch.h>
#include <arch.h>
#include <hal/wdt.h>
#include "wdt_private.h"

static inline status_t wdt_config_mode(wdt_mode_t mode)
{
	uint8_t value;
	value = MMIO8(WDTCSR);
	switch(mode)
	{
		case wbite:
			value |= (1 << WDE);
		case wbark:
			value |= (1 << WDIE);
			break;
		case wnone:
			value &= (~(1 << WDE)) & (~(1 << WDIE));
			break;
		default:
			return error_inval_arg;
	}

	// Start timed sequence [4 clks from next write]
	MMIO8(WDTCSR) |= (1 << WDCE) | (1 << WDE);
	MMIO8(WDTCSR) |= value;
	return success;
}

static inline status_t wdt_config_prescaler(uint8_t pr)
{
	uint8_t rback;
	uint8_t wdt_pr = ((pr & (1 << WDT2 | (1 << WDT1) | (1 << WDT0))) | ((pr & (1 << WDT3)) << WDT3));
	/*
	 * TODO: Check if WDE bit needs to be set along with wdt_pr
	 *       to configure prescaler
	 *       > As of now proceeding without setting WDE with wdt_pr
	 */
	// Start timed sequence [4 clks from next write]
	MMIO8(WDTCSR) |= (1 << WDCE) | (1 << WDE);
	MMIO8(WDTCSR) |= wdt_pr;	// <-- above todo is for here

	arch_sync();		// relax io bus and let the transaction propagate

	rback = MMIO8(WDTCSR);	// check for readback if the value is successfully written
	rback &= (1 << WDT2 | 1 << WDT1 | 1 << WDT0) | (1 << WDT3);
	return (rback == wdt_pr) ? success : error;
}

status_t wdt_setup(wdt_port_t *port, wdt_mode_t mode, uint8_t pr)
{
	assert(port);
	assert((mode >= 0) && (mode <= wbite));
	assert(pr <= 9);	// max pr switch value;
	if(port->wdt_handler == NULL && mode != wnone)
		return error_inval_arg;
	if(port->wdt_handler != NULL)
		link_interrupt(arch, port->wdt_irq, port->wdt_handler);
	return wdt_config_prescalar(pr);
}

status_t wdt_dis(wdt_port_t *port)
{
	assert(port);
	arch_di_save_state();
	arch_wdt_reset();
	MMIO8(MCUSR) &= ~(1 << 3);	// Clear WDRF bit
	// Start timed sequence [4 clks from next write]
	MMIO8(WDTCSR) |= (1 << WDCE) | (1 << WDE);
	MMIO8(WDTCSR) = 0x00;
	arch_ei_restore_state();
	return (MMIO8(WDTCSR) == 0) ? success : error;
}

status_t wdt_int_en(wdt_port_t *port)
{
	assert(port);
	MMIO8(WDTCSR_OFFSET) |= (1 << WDIE);
	return success;
}

status_t wdt_int_dis(wdt_port_t *port)
{
	assert(port);
	MMIO8(WDTCSR) &= ~(1 << WDIE);
	return success;
}

bool wdt_exp_status(wdt_port_t *port)
{
	assert(port);
	return MMIO8(WDTCSR) & (1 << WDIF) ? true : false;
}
