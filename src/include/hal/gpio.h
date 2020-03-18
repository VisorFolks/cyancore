#pragma once
#define _GPIO_H_

typedef enum gpio_mode
{
	out	= 1,
	in	= 2,
	pull_up	= 3
} gpio_mode_t;

status_t gpio_setup();
status_t gpio_pin_config(uint8_t, uint8_t, gpio_mode_t);
status_t gpio_pin_set(uint8_t, uint8_t);
status_t gpio_pin_clear(uint8_t, uint8_t);
status_t gpio_pin_toggle(uint8_t, uint8_t);
bool gpio_pin_read(uint8_t, uint8_t);
