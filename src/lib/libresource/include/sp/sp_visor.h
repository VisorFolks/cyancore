/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: sp_visor.h
 * Description		: This file contains data structures of software 
 *			  properties
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>
#include <sp/sp_device.h>
#include <dp/dp_device.h>
#include <dp/dp_gpio.h>

typedef struct swdev
{
	sw_devid_t swdev_id;
	hw_devid_t hwdev_id;
	pinmux_t *pmux;
} swdev_t;

typedef struct visor
{
	sw_devid_t *devids;
	size_t n_dev;
} visor_t;

#define add_visor_devs(x)	{				\
					.devids = x,		\
					.n_dev = propsize(x)	\
				}

typedef enum
{
	terravisor_id		= 0x1010,
	nsec_hypervisor_id	= 0x2020,
	sec_hypervisor_id	= 0x3030,
	nsec_supervisor_id	= 0x4040,
	sec_supervisor_id	= 0x5050,
} visor_id_t;


swdev_t *sp_terravisor_dev_info(sw_devid_t devid);

#if NSEC_HYP == 1
swdev_t *sp_nsec_hypervisor_dev_into(sw_devid_t devid);
#endif

#if SEC_*HYP == 1
swdev_t *sp_sec_hypervisor_dev_info(sw_devid_t devid);
#endif

#if NSEC*_SUP >= 1
swdev_t *sp_nsec_supervisor_dev_info(size_t index, sw_devid_t devid);
#endif

#if SEC_*SUP >= 1
swdev_t *sp_sec_supervisor_dev_info(size_t index, sw_devid_t devid);
#endif
