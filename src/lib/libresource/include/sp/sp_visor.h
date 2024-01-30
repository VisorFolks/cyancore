/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
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

typedef const struct swdev
{
	sw_devid_t swdev_id;
	hw_devid_t hwdev_id;
	pinmux_t *pmux;
} swdev_t;

typedef const struct visor
{
	sw_devid_t const *devids;
	size_t n_dev;
} visor_t;

/**
 * create_pmux - Instantiates pinmux struct
 *
 * @param[in] _name - Name of the struct
 * @param[in] _port - port of all the pins
 * @param[in] _func - type of function
 * @param[in] _pin1 - Needs minimum of 1 pin
 * @param[in] ... - Variable args for more pin
 */
#define create_pmux(_name, _port, _func, _pin1, ...)		\
	static const uint8_t _name##pins[] = {_pin1,		\
					##__VA_ARGS__};		\
	static const pinmux_t _name = addpins(_port,		\
				_name##pins, _func)

/**
 * add_pinmux - Adds pinmux node to create_swdev
 *
 * @param[in] x - pinmux node
 */
#define add_pinmux(x)	.pmux = &x

/**
 * create_swdev - Instantiates sw dev module
 *
 * @param[in] _name - Name of the node
 * @param[in] _swdev_id - sw dev ID
 * @param[in] _hwdev_id - hw dev ID of connecting hardware
 * @param[in] ... - Variable args if pinmux is needed
 */
#define create_swdev(_name, _swdev_id, _hwdev_id, ...)		\
	static swdev_t _name =					\
	{							\
		.swdev_id = _swdev_id,				\
		.hwdev_id = _hwdev_id,				\
		##__VA_ARGS__					\
	}

#define add_visor_devs(x)	{				\
					.devids = x,		\
					.n_dev = propsize(x)	\
				}

/**
 * create_visor - Instantiates visor struct
 *
 * @param[in] _name - Name of the visor module
 * @param[in] _dev1 - Minimum of 1 device needs to be assiged
 * @param[in] ... - Variable args for more than 1 device
 */
#define create_visor(_name, dev1, ...)				\
	const sw_devid_t _name##_dev[] = {dev1, ##__VA_ARGS__};	\
	static visor_t _name = add_visor_devs(_name##_dev)

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
