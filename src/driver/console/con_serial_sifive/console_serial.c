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
#include <driver/sysclk.h>
#include <driver/console.h>

static uart_port_t console_port;

static void console_serial_irq_handler(void);

static status_t console_serial_setup(void)
{
	uart_get_properties(&console_port, console_uart);

	console_port.irq_handler = console_serial_irq_handler;

	sysdbg2("UART engine @ %p\n", console_port.baddr);
	sysdbg2("UART baud @ %lubps\n", console_port.baud);
	sysdbg2("UART irqs - %u\n", console_port.irq);
	/*
	 * If memory mapping is applicable,
	 * put it in mmu supported guide.
	 */
	return uart_setup(&console_port, trx, no_parity);
}

static status_t console_serial_write(const char c)
{
	status_t ret;
	while(!uart_buffer_available(&console_port));
	ret = uart_tx(&console_port, c);
	return ret;
}

static int_wait_t con_read_wait;
static char con_buff[32];
static uint8_t wp, rp, occ;

static status_t console_serial_read(char *c)
{
	status_t ret = success;
	if(!occ)
	{
		ret = wait_lock(&con_read_wait);
		ret |= wait_till_irq(&con_read_wait);
	}

	*c = con_buff[wp++];
	wp = wp % 32;
	occ--;

	return ret;
}

static void console_serial_irq_handler(void)
{
	if(uart_rx_pending(&console_port))
	{
		wait_release_on_irq(&con_read_wait);
		while(uart_rx_pending(&console_port))
		{
			uart_rx(&console_port, &con_buff[rp++]);
			rp = rp % 32;
			occ++;
		}
	}
}

static console_t console_serial_driver =
{
	.write = &console_serial_write,
	.read = &console_serial_read,
	.payload_size = (unsigned int *)&occ,
};

static status_t console_serial_pre_clk_config(void)
{
	return success;
}

static status_t console_serial_post_clk_config(void)
{
	uart_update_baud(&console_port);
	return success;
}

static sysclk_config_clk_callback_t console_handle =
{
	.pre_config = &console_serial_pre_clk_config,
	.post_config = &console_serial_post_clk_config
};

status_t console_serial_driver_setup(void)
{
	status_t ret;
	driver_exit("earlycon");
	ret = console_serial_setup();
	ret |= sysclk_register_config_clk_callback(&console_handle);
	ret |= console_attach_device(ret, &console_serial_driver);
	return ret;
}

status_t console_serial_driver_exit(void)
{
	status_t ret;
	ret = console_release_device();
	ret |= sysclk_deregister_config_clk_callback(&console_handle);
	ret |= uart_shutdown(&console_port);
	driver_setup("earlycon");
	return ret;
}

#if CONSOLE_SERIAL==1
INCLUDE_DRIVER(console, console_serial_driver_setup, console_serial_driver_exit, 0, 255, 255);
#endif
