/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: console_serial.c
 * Description		: This file contains sources of uart console
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
#include <machine_call.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <driver/console.h>

static uart_port_t *console_port;

static void console_serial_write_irq_handler(void);
static void console_serial_read_irq_handler(void);

static status_t console_serial_setup()
{
	mret_t mres;
	const swdev_t *sp;
	const module_t *dp;
	hw_devid_t devid;
	arch_machine_call(fetch_sp, console_uart, 0, 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("Console could not found!\n");
		return mres.status;
	}
	sp = (swdev_t *) mres.p;
	devid = sp->hwdev_id;
	arch_machine_call(fetch_dp, (devid & 0xff00), (devid & 0x00ff), 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("UART Device %d not found!\n", devid);
		return mres.status;
	}
	dp = (module_t *)mres.p;
	console_port = (uart_port_t *)malloc(sizeof(uart_port_t));
	if(!console_port)
		return error_memory_low;
	console_port->port_id = dp->id;
	console_port->clk_id = dp->clk_id;
	console_port->baddr = dp->baddr;
	console_port->stride = dp->stride;
	console_port->baud = dp->clk;
	console_port->tx_irq = &dp->interrupt[1];
	console_port->tx_handler = console_serial_write_irq_handler;
	console_port->rx_irq = &dp->interrupt[0];
	console_port->rx_handler = console_serial_read_irq_handler;

	sysdbg2("UART engine @ %p\n", console_port->baddr);
	sysdbg2("UART baud @ %lubps\n", console_port->baud);
	sysdbg2("UART irqs - %u & %u\n", dp->interrupt[1].id, dp->interrupt[0].id);
	/*
	 * If memory mapping is applicable,
	 * put it in mmu supported guide.
	 */
	return uart_setup(console_port, trx, no_parity);
}

static int_wait_t con_write_wait;

static void console_serial_write_irq_handler()
{
	wait_release_on_irq(&con_write_wait);
}

status_t console_serial_write(const char c)
{
	status_t ret;
	ret = wait_lock(&con_write_wait);
	ret |= uart_tx(console_port, c);
	ret |= wait_till_irq(&con_write_wait);
	return ret;
}

static int_wait_t con_read_wait;
static char con_char;

static void console_serial_read_irq_handler()
{
	wait_release_on_irq(&con_read_wait);
	uart_rx(console_port, &con_char);
}

static status_t console_serial_read(char *c)
{
	status_t ret;
	ret = wait_lock(&con_read_wait);
	ret |= wait_till_irq(&con_read_wait);
	*c = con_char;
	return ret;
}

static console_t *console_serial_driver;

status_t console_serial_driver_exit()
{
	status_t ret;
	ret = console_release_device();
	ret |= uart_shutdown(console_port);
	free(console_serial_driver);
	free(console_port);
	ret |= driver_setup("earlycon");
	return ret;
}

status_t console_serial_driver_setup()
{
	status_t ret;
	driver_exit("earlycon");
	console_serial_driver = (console_t *)malloc(sizeof(console_t));
	if(!console_serial_driver)
		return error_memory_low;
	console_serial_driver->write = &console_serial_write;
	console_serial_driver->read = &console_serial_read;
	ret = console_serial_setup();
	if(ret)
		goto cleanup_exit;
	ret = console_attach_device(ret, console_serial_driver);
	if(!ret)
		goto exit;
cleanup_exit:
	console_serial_driver_exit();
exit:
	return ret;
}

#if CONSOLE_SERIAL==1
INCLUDE_DRIVER(console, console_serial_driver_setup, console_serial_driver_exit, 0, 255, 255);
#endif
