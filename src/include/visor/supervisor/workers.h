/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: worker.h
 * Description		: This file consists of supervisor-workers
 *			  and related prototypes
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <supervisor_call.h>

void super_call(scall_id_t id, unsigned int a0, unsigned int a1, unsigned int a2, sret_t *ret);
