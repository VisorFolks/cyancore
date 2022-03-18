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
#include <platform.h>
#include <interrupt.h>
#include <hal/uart.h>
#include <machine_call.h>
#include <arch.h>
#include "uart_private.h"

status_t uart_setup(const uart_port_t *port, direction_t d, parity_t p _UNUSED)
{
	status_t ret = success;
	assert(port);

	// Enable module based on direction
	uint32_t txctlr = 0;
	uint32_t rxctlr = 0;
	switch(d)
	{
		case trx:
			txctlr |= (1 << TXEN) | (7 << TXCNT);
			if(port->tx_irq)
			{
				link_interrupt(port->tx_irq->module, port->tx_irq->id, port->tx_handler);
				uart_tx_int_en(port);
			}
			_FALLTHROUGH;
		case rx:
			rxctlr |= (1 << RXEN) | (1 << RXCNT);
			if(port->rx_irq)
			{
				link_interrupt(port->rx_irq->module, port->rx_irq->id, port->rx_handler);
				uart_rx_int_en(port);
			}
			break;
		case tx:
			txctlr |= (1 << TXEN) | (7 << TXCNT);
			if(port->tx_irq)
			{
				link_interrupt(port->tx_irq->module, port->tx_irq->id, port->tx_handler);
				uart_tx_int_en(port);
			}
			break;
		default:
			ret = error_func_inval_arg;
	}
	MMIO32(0x10012000 + 0x38) |= (3 << 16);
	MMIO32(port->baddr + TXCTRL_OFFSET) = txctlr;
	sysdbg5("TXCTRL=%x", txctlr);
	MMIO32(port->baddr + RXCTRL_OFFSET) = rxctlr;
	sysdbg5("RXCTRL=%x", rxctlr);
	arch_dsb();

	// Set baud rate
	uart_update_baud(port);
	return ret;
}

status_t uart_shutdown(const uart_port_t *port)
{
	status_t ret = success;
	assert(port);
	if(port->tx_irq)
	{
		ret |= uart_tx_int_dis(port);
		ret |= unlink_interrupt(port->tx_irq->module, port->tx_irq->id);
	}
	if(port->rx_irq)
	{
		ret |= uart_rx_int_dis(port);
		ret |= unlink_interrupt(port->rx_irq->module, port->rx_irq->id);
	}
	MMIO32(port->baddr + TXCTRL_OFFSET) = 0;
	MMIO32(port->baddr + RXCTRL_OFFSET) = 0;
	arch_dsb();
	return ret;
}

void uart_update_baud(const uart_port_t *port)
{
	assert(port);
	TODO(Replace with clock get api!)
	unsigned long plat_clk = 20000000;
	MMIO32(port->baddr + UARTBR_OFFSET) = BAUD_DIV(plat_clk, port->baud) & 0xffff;
	arch_dsb();
}

bool uart_buffer_available(const uart_port_t *port)
{
	assert(port);
	return (bool)(MMIO32(port->baddr + TXDATA_OFFSET) >> TX_FULL) ^ 1;
}

void uart_tx_wait_till_done(const uart_port_t *port)
{
	assert(port);
	while((MMIO32(port->baddr + TXDATA_OFFSET) & (1U << TX_FULL)))
		arch_nop();
}

status_t uart_tx(const uart_port_t *port, const char data)
{
	assert(port);
	while(!uart_buffer_available(port))
		arch_nop();
	MMIO32(port->baddr + TXDATA_OFFSET) |= data;
	return success;
}

status_t uart_rx(const uart_port_t *port, char *data)
{
	assert(port);
	*data = MMIO32(port->baddr + RXDATA_OFFSET) & 0xff;
	return success;
}

status_t uart_tx_int_en(const uart_port_t *port)
{
	assert(port);
	MMIO32(port->baddr + UARTIE_OFFSET) |= (1 << TXWM);
	return success;
}

status_t uart_tx_int_dis(const uart_port_t *port)
{
	assert(port);
	MMIO32(port->baddr + UARTIE_OFFSET) &= ~(1 << TXWM);
	return success;
}

status_t uart_rx_int_en(const uart_port_t *port)
{
	assert(port);
	MMIO32(port->baddr + UARTIE_OFFSET) |= (1 << RXWM);
	return success;
}

status_t uart_rx_int_dis(const uart_port_t *port)
{
	assert(port);
	MMIO32(port->baddr + UARTIE_OFFSET) &= ~(1 << RXWM);
	return success;
}
