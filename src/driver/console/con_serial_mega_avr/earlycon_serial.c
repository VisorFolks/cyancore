/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: earlycon_serial.c
 * Description		: This file contains sources of uart earlycon
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <status.h>
#include <syslog.h>
#include <stdlib.h>
#include <lock/spinlock.h>
#include <resource.h>
#include <visor_call.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <driver/console.h>

static uart_port_t *earlycon_port;

static status_t earlycon_serial_setup()
{
	vret_t vres;
	swdev_t *sp;
	module_t *dp;
	hw_devid_t devid;
	arch_visor_call(fetch_sp, console_uart, 0, 0, &vres);
	if(vres.status != success)
	{
		sysdbg3("Console could not found!\n");
		return vres.status;
	}
	sp = (swdev_t *) vres.p;
	devid = sp->hwdev_id;
	arch_visor_call(fetch_dp, (devid & 0xff00), (devid & 0x00ff), 0, &vres);
	if(vres.status != success)
	{
		sysdbg3("UART Device %d not found!\n", devid);
		return vres.status;
	}
	dp = (module_t *)vres.p;
	earlycon_port = (uart_port_t *)malloc(sizeof(uart_port_t));
	if(!earlycon_port)
		return error_memory_low;

	earlycon_port->port_id = dp->id;
	earlycon_port->clk_id = dp->clk_id;
	earlycon_port->baddr = dp->baddr;
	earlycon_port->stride = dp->stride;
	earlycon_port->baud = dp->clk;

	sysdbg2("UART engine @ %p\n", earlycon_port->baddr);
	sysdbg2("UART baud @ %lubps\n", earlycon_port->baud);
	/*
	 * If memory mapping is applicable,
	 * put it in mmu supported guide.
	 */
	return uart_setup(earlycon_port, tx, no_parity);
}

static status_t earlycon_serial_write(const char c)
{
	status_t ret;
	ret = uart_tx(earlycon_port, c);
	uart_tx_wait_till_done(earlycon_port);
	return ret;
}

static console_t *earlycon_serial_driver;

status_t earlycon_serial_driver_exit()
{
	status_t ret;
	ret = console_release_device();
	ret |= uart_shutdown(earlycon_port);
	free(earlycon_port);
	free(earlycon_serial_driver);
	return ret;
}

status_t earlycon_serial_driver_setup()
{
	status_t ret;
	earlycon_serial_driver = (console_t *)malloc(sizeof(console_t));
	if(!earlycon_serial_driver)
		return error_memory_low;
	earlycon_serial_driver->write = &earlycon_serial_write;
	ret = earlycon_serial_setup();
	if(ret)
		goto cleanup_exit;
	ret = console_attach_device(ret, earlycon_serial_driver);
	if(!ret)
		goto exit;
cleanup_exit:
	earlycon_serial_driver_exit();
exit:
	return ret;
}

#if EARLYCON_SERIAL==1
INCLUDE_DRIVER(earlycon, earlycon_serial_driver_setup, earlycon_serial_driver_exit, 0, 2, 2);
#endif
