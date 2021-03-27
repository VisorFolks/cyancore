/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: driver.h
 * Description		: This file consists of driver core prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _DRIVER_H_

typedef struct device
{
	char name[15];
	status_t (*driver_setup)(void);
	status_t (*driver_exit)(void);
	size_t sorder;
	size_t eorder;
	size_t exec;
} device_t;

#define INCLUDE_DRIVER(_name, _driver_setup, _driver_exit, _sorder, _eorder)		\
	const device_t _name __attribute__((section(".driver"))) =	\
	{								\
		.name		= #_name,				\
		.driver_setup	= _driver_setup,			\
		.driver_exit	= _driver_exit,				\
		.sorder		= _sorder,				\
		.eorder		= _eorder,				\
		.exec		= 0					\
	}

status_t driver_setup_all();
status_t driver_setup(const char *);
status_t driver_exit(const char *);
status_t driver_register(device_t *);
status_t driver_deregister(device_t *);
