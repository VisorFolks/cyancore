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
typedef struct sp
{
	visor_t *terravisor;

#if NSEC_HYP == 1
	visor_t *nsec_hypervisor;
#endif

#if SEC_HYP == 1
	visor_t *sec_hypervisor;
#endif

#if NSEC_SUP >= 1
	visor_t **nsec_supervisor;
	size_t n_nsec_supervisor;
#endif

#if SEC_SUP >= 1
	visor_t **sec_supervisor;
	size_t n_sec_supervisor;
#endif

	swdev_t **swdev;
	size_t n_swdev;
} sp_t;

status_t sp_init(sp_t *);
