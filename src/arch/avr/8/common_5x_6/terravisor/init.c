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
#include <stdlib.h>
#include <mmio.h>
#include <plat_arch.h>
#include <engine.h>
#include <arch.h>

extern uint16_t stack_start;

/*
 * zero_reg - Reset registers to 0
 *
 * This function is defined in asm.S file
 */
extern void zero_reg(void) _NAKED;

/**
 * init - Entry point for the framework
 *
 * @brief This function runs to reset the cpu reg bank to architectrually
 * reset state and jump to 'engine'.
 */
void _NAKED init()
{
	/* Set resisters to architecturally defined reset */
	zero_reg();
	/* Capture unique seed value before memory initialization */
	arch_rseed_capture();
	/* Boot framework */
	engine();

	/* Accidental trap, if control returns from framework */
	exit(EXIT_FAILURE);
}
