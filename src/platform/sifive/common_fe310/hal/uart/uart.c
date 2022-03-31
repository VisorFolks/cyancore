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
#include <arch.h>
#include <machine_call.h>
#include <resource.h>
#include <driver/sysclk.h>
#include <driver/interrupt_controller.h>
#include <mmio.h>
#include <interrupt.h>
#include <hal/uart.h>
#include "uart_private.h"

status_t uart_get_properties(uart_port_t *port, sw_devid_t dev)
{
	mret_t mres;
	swdev_t *sp;
	module_t *dp;
	hw_devid_t devid;

	arch_machine_call(fetch_sp, dev, 0, 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("%p - sp node could not be found!\n", dev);
		return mres.status;
	}
	sp = (swdev_t *) mres.p;
	devid = sp->hwdev_id;
	port->pmux = sp->pmux;

	arch_machine_call(fetch_dp, (devid & 0xff00), (devid & 0xff), 0, &mres);
	if(mres.status != success)
	{
		sysdbg3("UART Device %d not found!\n", devid);
		return mres.status;
	}
	dp = (module_t *) mres.p;
	port->port_id = dp->id;
	port->clk_id = dp->clk_id;
	port->baddr = dp->baddr;
	port->baud = dp->clk;
	port->irq = &dp->interrupt[0];
	return success;
}

status_t uart_setup(uart_port_t *port, direction_t d, parity_t p _UNUSED)
{
	status_t ret = success;

	// Enable module based on direction
	volatile uint32_t txctlr = 0;
	volatile uint32_t rxctlr = 0;

	for(uint8_t i = 0; i < port->pmux->npins; i++)
	{
		ret |= gpio_pin_alloc(&port->io[i], port->pmux->port, port->pmux->pins[i]);
		ret |= gpio_enable_alt_io(&port->io[i], port->pmux->function);
	}

	switch(d)
	{
		case trx:
			txctlr |= (1 << TXEN) | (0 << TXCNT);
			_FALLTHROUGH;
		case rx:
			rxctlr |= (1 << RXEN) | (0 << RXCNT);
			break;
		case tx:
			txctlr |= (1 << TXEN) | (0 << TXCNT);
			break;
		default:
			ret = error_func_inval_arg;
	}

	if(port->irq->id && port->irq_handler)
	{
		ret |= link_interrupt(port->irq->module, port->irq->id, port->irq_handler);
		ret |= ic_en_irq(port->irq->id);
		if(d == rx)
			ret |= uart_rx_int_en(port);
		else if(d == trx)
		{
			ret |= uart_tx_int_en(port);
			ret |= uart_rx_int_en(port);
		}
	}
	MMIO32(port->baddr + TXCTRL_OFFSET) = txctlr;
	sysdbg5("TXCTRL=%x", txctlr);
	MMIO32(port->baddr + RXCTRL_OFFSET) = rxctlr;
	sysdbg5("RXCTRL=%x", rxctlr);
	arch_dsb();

	// Set baud rate
	uart_update_baud(port);
	return ret;
}

status_t uart_shutdown(uart_port_t *port)
{
	status_t ret = success;

	for(uint8_t i = 0; i < port->pmux->npins; i++)
	{
		ret |= gpio_disable_alt_io(&port->io[i]);
		ret |= gpio_pin_free(&port->io[i]);
	}

	if(port->irq->id && port->irq_handler)
	{
		ret |= ic_dis_irq(port->irq->id);
		ret |= uart_tx_int_dis(port);
		ret |= uart_rx_int_dis(port);
		ret |= unlink_interrupt(port->irq->module, port->irq->id);
	}
	
	MMIO32(port->baddr + TXCTRL_OFFSET) = 0;
	MMIO32(port->baddr + RXCTRL_OFFSET) = 0;
	arch_dsb();
	return ret;
}

void uart_update_baud(const uart_port_t *port)
{
	unsigned int plat_clk;
	sysclk_get_clk(&plat_clk);
	MMIO32(port->baddr + UARTBR_OFFSET) = BAUD_DIV(plat_clk, port->baud) & 0xffff;
	arch_dsb();
}

bool uart_buffer_available(const uart_port_t *port)
{
	return (bool)(MMIO32(port->baddr + TXDATA_OFFSET) >> TX_FULL) ^ 1;
}

void uart_tx_wait_till_done(const uart_port_t *port)
{
	while((MMIO32(port->baddr + TXDATA_OFFSET) & (1U << TX_FULL)))
		arch_nop();
}

status_t uart_tx(const uart_port_t *port, const char data)
{
	while(!uart_buffer_available(port))
		arch_nop();
	MMIO32(port->baddr + TXDATA_OFFSET) |= data;
	return success;
}

bool uart_rx_empty(const uart_port_t *port)
{
	return (MMIO32(port->baddr + RXDATA_OFFSET) & (1U << RX_EMPTY)) ? true : false;
}

status_t uart_rx(const uart_port_t *port, char *data)
{
	*data = MMIO32(port->baddr + RXDATA_OFFSET) & 0xff;
	return success;
}

status_t uart_tx_int_en(const uart_port_t *port)
{
	MMIO32(port->baddr + UARTIE_OFFSET) |= (1 << TXWM);
	return success;
}

status_t uart_tx_int_dis(const uart_port_t *port)
{
	MMIO32(port->baddr + UARTIE_OFFSET) &= ~(1 << TXWM);
	return success;
}

status_t uart_rx_int_en(const uart_port_t *port)
{
	MMIO32(port->baddr + UARTIE_OFFSET) |= (1 << RXWM);
	return success;
}

status_t uart_rx_int_dis(const uart_port_t *port)
{
	MMIO32(port->baddr + UARTIE_OFFSET) &= ~(1 << RXWM);
	return success;
}

bool uart_tx_pending(const uart_port_t *port)
{
	return ((MMIO32(port->baddr + UARTIP_OFFSET) & (1 << TXWM)) ? false : true);
}

bool uart_rx_pending(const uart_port_t *port)
{
	return ((MMIO32(port->baddr + UARTIP_OFFSET) & (1 << RXWM)) ? true : false);
}
