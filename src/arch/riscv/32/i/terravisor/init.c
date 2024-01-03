/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: init.c
 * Description		: This file consists of init routine of the framework.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <arch.h>
#include <engine.h>

/**
 * init - Entry point for the framework
 *
 * @brief This function runs to reset the cpu reg bank to architectrually
 * reset state and jump to 'engine'.
 */
void _NAKED init()
{
	arch_di();
	asm volatile("la	tp, _tls_start");
        /* Capture unique seed value before memory initialization */
        arch_rseed_capture();
	/* Boot framework */
#if CCSMP == 0
	engine();
#else
	if(arch_core_index() == BOOT_CORE_ID)
	{
		arch_early_signal_boot_start();
		engine();
	}
	else
	{
		arch_wait_till_boot_done();
		engine_secondary();
	}
#endif

	/* Accidental trap, if control returns from framework */
	exit(EXIT_FAILURE);
}
