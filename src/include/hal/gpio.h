/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: gpio.h
 * Description		: This file consists of GPIO-HAL prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include <status.h>

typedef uint64_t gpio_parallel_t;

typedef enum gpio_port_name
{	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH,
	PORTI,
	PORTJ,
	PORTK,
	PORTL,
	PORTM,
	PORTN,
	PORTO,
	PORTP,
	PORTQ,
	PORTR,
	PORTS,
	PORTT,
	PORTU,
	PORTV,
	PORTW,
	PORTX,
	PORTY,
	PORTZ
}gpio_port_name_t;

typedef enum gpio_mode
{
	out	= 1,
	in	= 2,
	pull_up	= 3
} gpio_mode_t;

typedef struct gpio_port
{
	uintptr_t pbaddr;
	uint8_t port;
	uint8_t pin;
} gpio_port_t;

status_t gpio_pin_alloc(gpio_port_t *port, uint8_t portID, uint8_t pinID);
status_t gpio_pin_mode(const gpio_port_t *port, gpio_mode_t mode);
status_t gpio_pin_free(gpio_port_t *port);
status_t gpio_pin_set(const gpio_port_t * port);
status_t gpio_pin_clear(const gpio_port_t *port);
status_t gpio_pin_toggle(const gpio_port_t *port);
bool gpio_pin_read(const gpio_port_t *port);

status_t gpio_port_alloc(gpio_port_t *port, uint8_t portID);
status_t gpio_port_mode(const gpio_port_t *port, gpio_mode_t mode);
status_t gpio_port_free(gpio_port_t *port);
status_t gpio_port_write(const gpio_port_t *port, gpio_parallel_t value);
status_t gpio_port_read(const gpio_port_t *port, gpio_parallel_t *value);
