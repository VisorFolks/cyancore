/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: uart.c
 * Description		: This file contains sources for mega-avr
 *			  HAL uart apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <status.h>
#include <mmio.h>
#include <lock/spinlock.h>
#include <platform.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <device.h>
#include <machine_call.h>
#include <arch.h>
#include "uart_private.h"

status_t uart_setup(uart_port_t *port, direction_t d, parity_t p)
{
	status_t ret = success;
	assert(port);
	MMIO8(port->baddr + UCSRA_OFFSET) = 0x00;
	platform_clk_en(port->clk_id);
	mret_t mres = arch_machine_call(fetch_dp, DEV_CLOCK, 0, 0);
	if(mres.status != success)
		return mres.status;
	unsigned long *clk = (unsigned long *)mres.p;


	// Enable module based on direction
	uint8_t en = 0;
	switch(d)
	{
		case trx:
			en |= (1 << TXEN);
			link_interrupt(arch, port->tx_irq, port->tx_handler);
			uart_tx_int_en(port);
		case rx:
			en |= (1 << RXEN);
			uart_rx_int_en(port);
			link_interrupt(arch, port->rx_irq, port->rx_handler);
			uart_rx_int_en(port);
			break;
		case tx:
			en |= (1 << TXEN);
			link_interrupt(arch, port->tx_irq, port->tx_handler);
			uart_tx_int_en(port);
			break;
		default:
			en = 0;
			ret = error_inval_arg;
	}
	MMIO8(port->baddr + UCSRB_OFFSET) |= en;

	// Set baud rate
	uint16_t b = BAUD_RATE_VALUE(*clk, port->baud);
	MMIO8(port->baddr + UBRRH_OFFSET) = (b >> 8);
	MMIO8(port->baddr + UBRRL_OFFSET) = (b & 0xff);

	// Configure frame
	// Defaults to
	// Async UART, 1 stop bit, Rising edge clk
	MMIO8(port->baddr + UCSRC_OFFSET) = 0;
	MMIO8(port->baddr + UCSRC_OFFSET) |= (p << UPM0);	// Set Parity
	MMIO8(port->baddr + UCSRC_OFFSET) |= (3 << UCSZ0);	// 8bit frame
	return ret;
}

status_t uart_shutdown(uart_port_t *port)
{
	status_t ret = success;
	assert(port);
	ret |= uart_tx_int_dis(port);
	ret |= uart_rx_int_dis(port);
	ret |= unlink_interrupt(arch, port->rx_irq);
	ret |= unlink_interrupt(arch, port->tx_irq);
	ret |= platform_clk_dis(port->clk_id);
	return ret;
}

bool uart_buffer_available(uart_port_t *port)
{
	assert(port);
	return (bool)(MMIO8(port->baddr + UCSRA_OFFSET) >> UDRE) & 0x01;
}

bool uart_tx_done(uart_port_t *port)
{
	assert(port);
	return (bool)(MMIO8(port->baddr + UCSRA_OFFSET) >> TXC) & 0x01;
}

bool uart_rx_done(uart_port_t *port)
{
	assert(port);
	return (bool)(MMIO8(port->baddr + UCSRA_OFFSET) >> RXC) & 0x01;
}

bool uart_frame_error(uart_port_t *port)
{
	bool ret = false;
	assert(port);
	if(MMIO8(port->baddr + UCSRC_OFFSET) & (1 << UPM0))
		ret = (MMIO8(port->baddr + UCSRA_OFFSET) & (1 << FE)) ? true : false;
	return ret;
}

status_t uart_tx(uart_port_t *port, const char data)
{
	assert(port);
	while(!uart_buffer_available(port));
	MMIO8(port->baddr + UDR_OFFSET) = data;
	return success;
}

status_t uart_rx(uart_port_t *port, char *data)
{
	assert(port);
	if(uart_frame_error(port))
		return error_data;
	*data = MMIO8(port->baddr + UDR_OFFSET);
	return success;
}

status_t uart_tx_int_en(uart_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + UCSRB_OFFSET) |= (1 << TXCIE);
	return success;
}

status_t uart_tx_int_dis(uart_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + UCSRB_OFFSET) &= ~(1 << TXCIE);
	return success;
}

status_t uart_rx_int_en(uart_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + UCSRB_OFFSET) |= (1 << RXCIE);
	return success;
}

status_t uart_rx_int_dis(uart_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + UCSRB_OFFSET) &= ~(1 << RXCIE);
	return success;
}
