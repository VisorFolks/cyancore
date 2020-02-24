#pragma once

typedef struct device
{
	char *name;
	void (*driver_setup)(void);
} device_t;

#define INCLUDE_DRIVER(_name,_driver_setup)				\
	const device_t _name __attribute__((section(".driver"))) =	\
	{								\
		.name		= #_name,				\
		.driver_setup	= _driver_setup				\
	}

void driver_setup_all();
status_t driver_setup(device_t *);
status_t driver_register(device_t *);
status_t driver_deregister(device_t *);
