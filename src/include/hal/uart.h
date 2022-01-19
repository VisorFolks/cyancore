/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: uart.h
 * Description		: This file consists of UART-HAL prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _UART_H_

#include <stdint.h>
#include <stdbool.h>
#include <status.h>
#include <resource.h>

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
	hw_devid_t port_id;
	unsigned int clk_id;
	unsigned long baud;
	uintptr_t baddr;
	uintptr_t stride;
	size_t tx_irq;
	void (*tx_handler)(void);
	size_t rx_irq;
	void (*rx_handler)(void);
} uart_port_t;


//spinlock_t uart_spinlock;

status_t uart_setup(uart_port_t *, direction_t, parity_t);
status_t uart_shutdown(uart_port_t *);
bool uart_buffer_available(uart_port_t *);
void uart_tx_wait_till_done(uart_port_t *);
bool uart_rx_done(uart_port_t *);
status_t uart_tx(uart_port_t *, const char);
status_t uart_rx(uart_port_t *, char *);
status_t uart_tx_int_en(uart_port_t *);
status_t uart_tx_int_dis(uart_port_t *);
status_t uart_rx_int_en(uart_port_t *);
status_t uart_rx_int_dis(uart_port_t *);
void uart_update_baud(uart_port_t *);
