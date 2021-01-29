#pragma once
#define _GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include <status.h>

typedef uint64_t gpio_parallel_t;

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

status_t gpio_setup(gpio_port_t *port, uint8_t portID, uint8_t pinID);
status_t gpio_pin_mode(gpio_port_t *port, gpio_mode_t mode);
status_t gpio_pin_set(gpio_port_t * port);
status_t gpio_pin_clear(gpio_port_t *port);
status_t gpio_pin_toggle(gpio_port_t *port);
bool gpio_pin_read(gpio_port_t *port);
status_t gpio_port_write(gpio_port_t *port, gpio_parallel_t value);
status_t gpio_port_read(gpio_port_t *port, gpio_parallel_t *value);
