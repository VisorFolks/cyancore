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
#include <stdlib.h>
#include <lock/spinlock.h>
#include <resource.h>
#include <machine_call.h>
#include <arch.h>
#include <driver.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <driver/sysclk.h>
#include <driver/console.h>

static uart_port_t *console_port;

static void console_serial_irq_handler(void);

static status_t console_serial_setup(void)
{
	status_t ret;

	ret = uart_get_properties(console_port, console_uart);
	if(ret)
		goto exit;

	console_port->irq_handler = console_serial_irq_handler;

	sysdbg2("UART engine @ %p\n", console_port->baddr);
	sysdbg2("UART baud @ %lubps\n", console_port->baud);
	sysdbg2("UART irqs - %u\n", console_port->irq);
	/*
	 * If memory mapping is applicable,
	 * put it in mmu supported guide.
	 */
	ret = uart_setup(console_port, trx, no_parity);
exit:
	return ret;
}

static status_t console_serial_write(const char c)
{
	status_t ret;
	while(!uart_buffer_available(console_port));
	ret = uart_tx(console_port, c);
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
	if(uart_rx_pending(console_port))
	{
		wait_release_on_irq(&con_read_wait);
		while(uart_rx_pending(console_port))
		{
			uart_rx(console_port, &con_buff[rp++]);
			rp = rp % 32;
			occ++;
		}
	}
}

static console_t *console_serial_driver;

static status_t console_serial_pre_clk_config(void)
{
	return success;
}

static status_t console_serial_post_clk_config(void)
{
	uart_update_baud(console_port);
	return success;
}

static sysclk_config_clk_callback_t *console_handle;

status_t console_serial_driver_exit(void)
{
	status_t ret;
	ret = console_release_device();
	if(console_handle)
		ret |= sysclk_deregister_config_clk_callback(console_handle);
	if(console_port)
		ret |= uart_shutdown(console_port);
	free(console_port);
	free(console_serial_driver);
	free(console_handle);
	ret |= driver_setup("earlycon");
	return ret;
}

status_t console_serial_driver_setup(void)
{
	status_t ret;
	driver_exit("earlycon");

	console_port = (uart_port_t *)malloc(sizeof(uart_port_t));
	if(!console_port)
	{
		ret = error_memory_low;
		goto cleanup_1;
	}

	console_serial_driver = (console_t *)malloc(sizeof(console_t));
	if(!console_serial_driver)
	{
		ret = error_memory_low;
		goto cleanup_1;
	}

	console_serial_driver->write = &console_serial_write;
	console_serial_driver->read = &console_serial_read;
	console_serial_driver->payload_size = (unsigned int *)&occ;

	console_handle = (sysclk_config_clk_callback_t*)malloc(sizeof(sysclk_config_clk_callback_t));
	if(!console_handle)
	{
		ret = error_memory_low;
		goto cleanup_1;
	}

	console_handle->pre_config = &console_serial_pre_clk_config;
	console_handle->post_config = &console_serial_post_clk_config;

	ret = console_serial_setup();
	if(ret)
		goto cleanup_1;

	ret = sysclk_register_config_clk_callback(console_handle);
	if(ret && ret != error_list_node_exists)
		goto cleanup_1;
	ret = console_attach_device(ret, console_serial_driver);
	if(!ret)
		goto exit;

cleanup_1:
	console_serial_driver_exit();
exit:
	return ret;
}

#if CONSOLE_SERIAL==1
INCLUDE_DRIVER(console, console_serial_driver_setup, console_serial_driver_exit, 0, 255, 255);
#endif
