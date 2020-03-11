#pragma once
#define _DRIVER_H_

typedef struct device
{
	char name[15];
	status_t (*driver_setup)(void);
} device_t;

#define INCLUDE_DRIVER(_name,_driver_setup)				\
	const device_t _name __attribute__((section(".driver"))) =	\
	{								\
		.name		= #_name,				\
		.driver_setup	= _driver_setup				\
	}

status_t driver_setup_all();
status_t driver_setup(const char *);
status_t driver_register(device_t *);
status_t driver_deregister(device_t *);
