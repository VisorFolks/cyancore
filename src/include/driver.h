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

#include <stdint.h>
#include <status.h>
#include <lock/lock.h>

#pragma pack(4)
typedef struct device
{
	char name[15];
	status_t (*driver_setup)(void);
	status_t (*driver_exit)(void);
	uint32_t sorder:8;
	uint32_t eorder:8;
	uint32_t exec:1;
	uint32_t percpu:1;
	lock_t key;
} device_t;
#pragma pack()

#define INCLUDE_DRIVER(_name, _driver_setup, _driver_exit, _pcpu, _sorder, _eorder)		\
	const device_t _name _SECTION(".driver") =			\
	{								\
		.name		= #_name,				\
		.driver_setup	= _driver_setup,			\
		.driver_exit	= _driver_exit,				\
		.sorder		= _sorder,				\
		.eorder		= _eorder,				\
		.exec		= 0,					\
		.percpu		= _pcpu,				\
	}

status_t driver_setup_all();
status_t driver_exit_all();
status_t driver_setup(const char *);
status_t driver_exit(const char *);
status_t driver_register(device_t *);
status_t driver_deregister(device_t *);
