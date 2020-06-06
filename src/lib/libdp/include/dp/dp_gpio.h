#pragma once

typedef struct gpio_module
{
	uintptr_t baddr;
	uintptr_t stride;
} gpio_module_t;

#if GPIO
gpio_module_t *dp_get_port_info(uint8_t);
#endif
