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
#include <lock/spinlock.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <driver.h>
#include <device.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <driver/console.h>

uart_port_t console_port;

void console_serial_write_irq_handler(void);
void console_serial_read_irq_handler(void);

status_t console_serial_setup()
{
	mret_t mres;
	module_t *dp;
	mres = arch_machine_call(FETCH_DP, DEV_CONSOLE, 0, 0);
	if(mres.status != success)
		return mres.status;
	dp = (module_t *)mres.p;
	console_port.port_id = dp->id;
	console_port.clk_id = dp->clk_id;
	console_port.baddr = dp->baddr;
	console_port.stride = dp->stride;
	console_port.baud = dp->clk;
	console_port.tx_irq = dp->interrupt_id[1];
	console_port.tx_handler = console_serial_write_irq_handler;
	console_port.rx_irq = dp->interrupt_id[0];
	console_port.rx_handler = console_serial_read_irq_handler;
	/*
	 * If memory mapping is applicable,
	 * put it in mmu supported guide.
	 */
	return uart_setup(&console_port, trx, no_parity);
}

int_wait_t con_write_wait;

void console_serial_write_irq_handler()
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

int_wait_t con_read_wait;
char con_char;

void console_serial_read_irq_handler()
{
	wait_release_on_irq(&con_read_wait);
	uart_rx(&console_port, &con_char);
}

status_t console_serial_read(char *c)
{
	wait_till_irq(&con_read_wait);
	*c = con_char;
	return success;
}

status_t console_serial_flush()
{
	return success;
}

console_t console_serial_driver =
{
	.setup = console_serial_setup,
	.write = console_serial_write,
	.error = console_serial_write,
	.read = console_serial_read,
	.flush = console_serial_flush
};

status_t console_serial_driver_setup()
{
	return console_attach_device(&console_serial_driver);
}

status_t console_serial_driver_exit()
{
	status_t ret;
	ret = console_release_device();
	ret |= uart_shutdown(&console_port);
	return ret;
}

#if EARLYCON_SERIAL==1
INCLUDE_DRIVER(earlycon, console_serial_driver_setup, console_serial_driver_exit, 0, 0);
#endif

#if CONSOLE_SERIAL==1
INCLUDE_DRIVER(console, console_serial_driver_setup, console_serial_driver_exit, 0, 0);
#endif
