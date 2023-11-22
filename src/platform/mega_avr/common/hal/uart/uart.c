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
#include <syslog.h>
#include <resource.h>
#include <mmio.h>
#include <lock/spinlock.h>
#include <platform.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <visor_call.h>
#include <arch.h>
#include "uart_private.h"

status_t uart_setup(uart_port_t *port, direction_t d, parity_t p)
{
	status_t ret = success;
	assert(port);
	MMIO8(port->baddr + UCSRA_OFFSET) = 0x00;
	platform_clk_en(port->clk_id);
	vret_t vres;
	arch_visor_call(fetch_dp, clock, 0, 0, &vres);
	if(vres.status != success)
		return vres.status;
	unsigned long *clk = (unsigned long *)vres.p;


	// Enable module based on direction
	uint8_t en = 0;
	switch(d)
	{
		case trx:
			en |= (1 << TXEN);
			if(port->tx_irq)
			{
				sysdbg5("Linking module#%u Tx IRQ#%u\n", port->tx_irq->module, port->tx_irq->id);
				link_interrupt(port->tx_irq->module, (unsigned int) port->tx_irq->id,
						port->tx_handler);
				uart_tx_int_en(port);
			}
		case rx:
			en |= (1 << RXEN);
			if(port->rx_irq)
			{
				sysdbg5("Linking module#%u Rx IRQ#%u\n", port->rx_irq->module, port->rx_irq->id);
				link_interrupt(port->rx_irq->module, (unsigned int) port->rx_irq->id,
						port->rx_handler);
				uart_rx_int_en(port);
			}
			break;
		case tx:
			en |= (1 << TXEN);
			if(port->tx_irq)
			{
				sysdbg5("Linking module#%u Tx IRQ#%u\n", port->tx_irq->module, port->tx_irq->id);
				link_interrupt(port->tx_irq->module, (unsigned int )port->tx_irq->id,
						port->tx_handler);
				uart_tx_int_en(port);
			}
			break;
		default:
			en = 0;
			ret = error_func_inval_arg;
			goto uart_setup_exit;
	}
	MMIO8(port->baddr + UCSRB_OFFSET) |= en;

	// Set baud rate
	uint16_t b = BAUD_RATE_VALUE(*clk, port->baud);
	sysdbg5("Baud Prescalar = %u\n", b);
	MMIO8(port->baddr + UBRRH_OFFSET) = (b >> 8);
	MMIO8(port->baddr + UBRRL_OFFSET) = (b & 0xff);

	// Configure frame
	// Defaults to
	// Async UART, 1 stop bit, Rising edge clk
	MMIO8(port->baddr + UCSRC_OFFSET) = (uint8_t) (p << UPM0) | (3 << UCSZ0); // Set Parity & 8 bit frame
uart_setup_exit:
	return ret;
}

status_t uart_shutdown(uart_port_t *port)
{
	status_t ret = success;
	assert(port);
	if(port->tx_irq)
	{
		ret |= uart_tx_int_dis(port);
		ret |= unlink_interrupt(port->tx_irq->module, (unsigned int) port->tx_irq->id);
	}
	if(port->rx_irq)
	{
		ret |= uart_rx_int_dis(port);
		ret |= unlink_interrupt(port->rx_irq->module, (unsigned int) port->rx_irq->id);
	}
	ret |= platform_clk_dis(port->clk_id);
	return ret;
}

bool uart_buffer_available(const uart_port_t *port)
{
	assert(port);
	return (bool)((MMIO8(port->baddr + UCSRA_OFFSET) >> UDRE) & 0x01);
}

void uart_tx_wait_till_done(const uart_port_t *port)
{
	assert(port);
	while(!(MMIO8(port->baddr + UCSRA_OFFSET) & (1 << TXC)))
		arch_nop();
	MMIO8(port->baddr + UCSRA_OFFSET) |= (1 << TXC);
}

bool uart_rx_done(const uart_port_t *port)
{
	assert(port);
	return (bool)((MMIO8(port->baddr + UCSRA_OFFSET) >> RXC) & 0x01);
}

bool uart_frame_error(const uart_port_t *port)
{
	bool ret = false;
	assert(port);
	if(MMIO8(port->baddr + UCSRC_OFFSET) & (1 << UPM0))
		ret = (MMIO8(port->baddr + UCSRA_OFFSET) & (1 << FE)) ? true : false;
	return ret;
}

status_t uart_tx(const uart_port_t *port, const char data)
{
	assert(port);
	while(!uart_buffer_available(port))
		arch_nop();
	MMIO8(port->baddr + UDR_OFFSET) = data;
	return success;
}

status_t uart_rx(const uart_port_t *port, char *data)
{
	assert(port);
	if(uart_frame_error(port))
		return error_driver_data;
	*data = MMIO8(port->baddr + UDR_OFFSET);
	return success;
}

status_t uart_tx_int_en(const uart_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + UCSRB_OFFSET) |= (1 << TXCIE);
	return success;
}

status_t uart_tx_int_dis(const uart_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + UCSRB_OFFSET) &= ~(1 << TXCIE);
	return success;
}

status_t uart_rx_int_en(const uart_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + UCSRB_OFFSET) |= (1 << RXCIE);
	return success;
}

status_t uart_rx_int_dis(const uart_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + UCSRB_OFFSET) &= ~(1 << RXCIE);
	return success;
}
