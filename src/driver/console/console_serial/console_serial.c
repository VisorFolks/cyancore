/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
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
#include <lock/spinlock.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <driver/console.h>

static uart_port_t console_port;

static void console_serial_write_irq_handler(void);
static void console_serial_read_irq_handler(void);

static status_t console_serial_setup()
{
	mret_t mres;
	const module_t *dp;
	hw_devid_t devid;
	arch_machine_call(fetch_sp, console_uart, 0, 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("Console could not found!\n");
		return mres.status;
	}
	devid = (hw_devid_t) mres.p;
	arch_machine_call(fetch_dp, (devid & 0xff00), (devid & 0x00ff), 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("UART Device %d not found!\n", devid);
		return mres.status;
	}
	dp = (module_t *)mres.p;
	console_port.port_id = dp->id;
	console_port.clk_id = dp->clk_id;
	console_port.baddr = dp->baddr;
	console_port.stride = dp->stride;
	console_port.baud = dp->clk;
	console_port.tx_irq = &dp->interrupt[1];
	console_port.tx_handler = console_serial_write_irq_handler;
	console_port.rx_irq = &dp->interrupt[0];
	console_port.rx_handler = console_serial_read_irq_handler;

	sysdbg2("UART engine @ %p\n", console_port.baddr);
	sysdbg2("UART baud @ %llubps\n", console_port.baud);
	sysdbg2("UART irqs - %u & %u\n", dp->interrupt[1].id, dp->interrupt[0].id);
	/*
	 * If memory mapping is applicable,
	 * put it in mmu supported guide.
	 */
	return uart_setup(&console_port, trx, no_parity); //
}

static int_wait_t con_write_wait;

static void console_serial_write_irq_handler()
{
	wait_release_on_irq(&con_write_wait);
}

status_t console_serial_write(const char c)
{
	status_t ret;
	ret = uart_tx(&console_port, c);
	wait_till_irq(&con_write_wait);
	return ret;
}

static int_wait_t con_read_wait;
static char con_char;

static void console_serial_read_irq_handler()
{
	wait_release_on_irq(&con_read_wait);
	uart_rx(&console_port, &con_char);
}

static status_t console_serial_read(char *c)
{
	wait_till_irq(&con_read_wait);
	*c = con_char;
	return success;
}

static status_t console_serial_flush()
{
	return success;
}

static console_t console_serial_driver =
{
	.write = &console_serial_write,
	.read = &console_serial_read,
	.flush = &console_serial_flush
};

status_t console_serial_driver_setup()
{
	status_t ret;
	driver_exit("earlycon");
	ret = console_serial_setup();
	ret |= console_attach_device(ret, &console_serial_driver);
	return ret;
}

status_t console_serial_driver_exit()
{
	status_t ret;
	ret = console_release_device();
	ret |= uart_shutdown(&console_port);
	driver_setup("earlycon");
	return ret;
}

#if CONSOLE_SERIAL==1
INCLUDE_DRIVER(console, console_serial_driver_setup, console_serial_driver_exit, 0, 255, 255);
#endif
