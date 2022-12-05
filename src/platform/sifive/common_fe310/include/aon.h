/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: aon_private.h
 * Description		: This file contains macors used by AON HAL
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

typedef struct aon_port
{
	uintptr_t baddr;
	uintptr_t stride;

} aon_port_t;

status_t aon_pmucause(const aon_port_t *, uint32_t *);
status_t aon_pmusleep_program(const aon_port_t *, const uint16_t *);
status_t aon_pmuwake_program(const aon_port_t *, const uint16_t *);
status_t aon_pmu_ie(const aon_port_t *, uint32_t);
status_t aon_pmusleep_trigger(const aon_port_t *);
