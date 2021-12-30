/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_mcall.c
 * Description		: This file contains platform mcall registration
 *			  api
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stddef.h>
#include <stdint.h>
#include <status.h>
#include <arch.h>
#include <interrupt.h>
#include <machine_call.h>
#include <terravisor/workers.h>
#include <platform.h>

static void platform_mcall_handler()
{
	context_frame_t *frame = get_context_frame();
	mret_t mres;
	machine_call(frame->a0, frame->a1, frame->a2, frame->a3, &mres);
	fence(w, w);
	frame->a0 = mres.p;
	frame->a1 = mres.size;
	frame->a2 = mres.status;
	return;
}

status_t platform_mcall_update()
{
	return link_interrupt(arch, 11, &platform_mcall_handler);
}
