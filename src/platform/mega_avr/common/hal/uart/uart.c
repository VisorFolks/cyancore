#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <status.h>
#include <mmio.h>
#include <lock/spinlock.h>
#include <driver/serial.h>
#include <mega_avr_platform.h>
#include "uart_private.h"


status_t serial_setup(uart_port_t *port, direction_t d, baud_t rate, parity_t p)
{
	status_t ret = success;
	assert_ndbg(port);
	MMIO8(port->baddr + UCSRA_OFFSET) = 0x00;
	platform_clk_en(port->clk_id);

	// Enable module based on direction
	uint8_t en = 0;
	switch(d)
	{
		case trx:
			en |= (1 << TXEN);
		case rx:
			en |= (1 << RXEN);
			break;
		case tx:
			en |= (1 << TXEN);
			break;
		default:
			en = 0;
			ret = error_inval_arg;
	}
	MMIO8(port->baddr + UCSRB_OFFSET) |= en;

	// Set baud rate
	uint16_t b = 0;
	switch(rate)
	{
		case b2400:
			b = B2400;
			break;
		case b4800:
			b = B4800;
			break;
		case b9600:
			b = B9600;
			break;
		case b19k2:
			b = B19200;
			break;
		case b38k4:
			b = B38400;
			break;
		case b115k2:
			b = B115200;
			break;
		case b230k4:
			b = B230400;
			break;
		case b250k0:
			b = B250000;
			break;
		default:
			b = 0;
			ret = error_inval_arg;
			break;
	}
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

status_t serial_shutdown(uart_port_t *port)
{
	return platform_clk_dis(port->clk_id);
}

bool serial_buffer_available(uart_port_t *port)
{
	return (bool)(MMIO8(port->baddr + UCSRA_OFFSET) >> UDRE) & 0x01;
}

bool serial_tx_done(uart_port_t *port)
{
	return (bool)(MMIO8(port->baddr + UCSRA_OFFSET) >> TXC) & 0x01;
}

bool serial_rx_done(uart_port_t *port)
{
	return (bool)(MMIO8(port->baddr + UCSRA_OFFSET) >> RXC) * 0x01;
}

bool serial_frame_error(uart_port_t *port)
{
	bool ret = false;
	if(MMIO8(port->baddr + UCSRC_OFFSET) & (1 << UPM0))
		ret = (MMIO8(port->baddr + UCSRA_OFFSET) & (1 << FE)) ? true : false;
	return ret;
}

status_t serial_tx(uart_port_t *port, const char data)
{
	assert_ndbg(port);
	while(!serial_buffer_available(port));
	MMIO8(port->baddr + UDR_OFFSET) = data;
	return success;
}

status_t serial_rx(uart_port_t *port, char *data)
{
	uint8_t *d = (uint8_t *)data;
	assert_ndbg(port);
	while(!serial_rx_done(port));
	if(serial_frame_error(port))
		return error_data;
	*d = MMIO8(port->baddr + UDR_OFFSET);
	return success;
}

status_t serial_rx_int_en(uart_port_t *port)
{
	assert_ndbg(port);
	MMIO8(port->baddr + UCSRB_OFFSET) = (1 << RXCIE);
	return success;
}
