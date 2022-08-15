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
#include <stdlib.h>
#include <syslog.h>
#include <lock/spinlock.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <driver/console.h>
#include <driver/sysclk.h>

static uart_port_t *earlycon_port;

static status_t earlycon_serial_setup()
{
	earlycon_port = (uart_port_t *)malloc(sizeof(uart_port_t));
	if(!earlycon_port)
		return error_memory_low;
	uart_get_properties(earlycon_port, console_uart);

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

static status_t earlycon_serial_pre_clk_config()
{
	return success;
}

static status_t earlycon_serial_post_clk_config()
{
	uart_update_baud(earlycon_port);
	return success;
}

static sysclk_config_clk_callback_t *earlycon_handle;

static console_t *earlycon_serial_driver;

status_t earlycon_serial_driver_setup()
{
	status_t ret;

	earlycon_serial_driver = (console_t *)malloc(sizeof(console_t));
	if(!earlycon_serial_driver)
		return error_memory_low;
	earlycon_serial_driver->write = &earlycon_serial_write;

	earlycon_handle = (sysclk_config_clk_callback_t *)malloc(sizeof(sysclk_config_clk_callback_t));
	if(!earlycon_handle)
		return error_memory_low;
	earlycon_handle->pre_config = &earlycon_serial_pre_clk_config;
	earlycon_handle->post_config = &earlycon_serial_post_clk_config;

	ret = earlycon_serial_setup();
	ret |= sysclk_register_config_clk_callback(earlycon_handle);
	ret |= console_attach_device(ret, earlycon_serial_driver);
	return ret;
}

status_t earlycon_serial_driver_exit()
{
	status_t ret;
	ret = console_release_device();
	ret |= sysclk_deregister_config_clk_callback(earlycon_handle);
	ret |= uart_shutdown(earlycon_port);
	free(earlycon_serial_driver);
	free(earlycon_handle);
	return ret;
}

#if EARLYCON_SERIAL==1
INCLUDE_DRIVER(earlycon, earlycon_serial_driver_setup, earlycon_serial_driver_exit, 0, 2, 2);
#endif
