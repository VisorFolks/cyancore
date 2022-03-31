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
#include <hal/gpio.h>

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
	pinmux_t *pmux;
	gpio_port_t io[2];
#if MAX_INTERRUPTS_PER_DEVICE < 2
	const irqs_t *irq;
	void (*irq_handler)(void);
#else
	const irqs_t *tx_irq;
	void (*tx_handler)(void);
	const irqs_t *rx_irq;
	void (*rx_handler)(void);
#endif
} uart_port_t;


status_t uart_get_properties(uart_port_t *, sw_devid_t);
status_t uart_setup(uart_port_t *, direction_t, parity_t);
status_t uart_shutdown(uart_port_t *);
bool uart_buffer_available(const uart_port_t *);
void uart_tx_wait_till_done(const uart_port_t *);
bool uart_rx_empty(const uart_port_t *);
bool uart_rx_done(const uart_port_t *);
status_t uart_tx(const uart_port_t *, const char);
status_t uart_rx(const uart_port_t *, char *);
status_t uart_tx_int_en(const uart_port_t *);
status_t uart_tx_int_dis(const uart_port_t *);
status_t uart_rx_int_en(const uart_port_t *);
status_t uart_rx_int_dis(const uart_port_t *);
void uart_update_baud(const uart_port_t *);
bool uart_tx_pending(const uart_port_t *);
bool uart_rx_pending(const uart_port_t *);
