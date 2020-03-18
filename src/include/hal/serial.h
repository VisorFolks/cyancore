#pragma once
#define _SERIAL_H_

typedef enum direction
{
	tx = 1,
	rx = 2,
	trx = 3
} direction_t;

typedef enum parity
{
	no_parity = 0,
	e_parity = 2,
	o_parity = 3,
} parity_t;

typedef struct uart_port
{
	uint8_t port_id;
	unsigned int clk_id;
	unsigned long baud;
	uintptr_t baddr;
	uintptr_t stride;
} uart_port_t;


//spinlock_t serial_spinlock;

status_t serial_setup(uart_port_t *, direction_t, parity_t);
status_t serial_shutdown(uart_port_t *);
bool serial_rx_done(uart_port_t *);
status_t serial_tx(uart_port_t *, const char);
status_t serial_rx(uart_port_t *, char *);
status_t serial_rx_int_en(uart_port_t *);
