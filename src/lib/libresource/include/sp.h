/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: sp.h
 * Description		: This file contains datatype and macros for
 *			  software properties
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <status.h>
#include <sp/sp_visor.h>

/*
 * sp
 * |- (terra/hyper/super)visor
 * |  |- devids
 * |  |  |- dev_1
 * |  |  |- dev_2
 * |  |  \- ...
 * |  \- n_dev
 * |- swdev
 * |  |- swdev_1
 * |  |- swdev_2
 * |  \- ...
 * \- n_swdev <- n(swdev)
 */
typedef const struct sp
{
	visor_t *terravisor;

#if NSEC_HYP == 1
	visor_t *nsec_hypervisor;
#endif

#if SEC_HYP == 1
	visor_t *sec_hypervisor;
#endif

#if NSEC_SUP >= 1
	visor_t * const *nsec_supervisor;
	size_t n_nsec_supervisor;
#endif

#if SEC_SUP >= 1
	visor_t * const *sec_supervisor;
	size_t n_sec_supervisor;
#endif

	swdev_t * const *swdev;
	size_t n_swdev;
} sp_t;

/**
 * create_swdev_list - Creates list of all software devices
 *
 * @param[in] _name - Name of the list
 * @param[in] dev1 - minimum of 1 device is needed
 * @param[in] ... - Variable arg if more than 1 device is present
 */
#define create_swdev_list(_name, dev1, ...)		\
	swdev_t * const _name[] =			\
	{dev1, ##__VA_ARGS__}

/**
 * add_swdev - Adds software devices into SP
 *
 * @param[in] x - Name of swdev list created
 */
#define add_swdev(x)		.swdev = x,		\
				.n_swdev = propsize(x)

/**
 * add_terravisor - Adds terravisor node into SP
 *
 * @param[in] x - Name of the terravisor node
 */
#define add_terravisor(x)	.terravisor = &x

/**
 * create_sp - Instantiates SP tree
 *
 * @param[in] _name - Name of the SP tree
 * @param[in] devs - use add_swdev macro to append list
 * @param[in] visor1 - Minimum of 1 visor is required
 * @param[in] ... - Variable args for more visors
 */
#define create_sp(_name, devs, visor1, ...)		\
	sp_t _name =					\
	{						\
		devs,					\
		visor1,					\
		##__VA_ARGS__				\
	}

status_t sp_init(sp_t *);
