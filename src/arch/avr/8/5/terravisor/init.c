/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: init.c
 * Description		: This file consists of entry point of the framework.
 *			  After the reset of system, program in this file gets
 *			  executed.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdlib.h>
#include <mmio.h>
#include <plat_arch.h>
#include <engine.h>

/**
 * stack_start - Variable pointing to stack start assigned while linking
 *
 * This variable is substituted by the linker with actual value of
 * stack start. Please refer linker script for this variable assignment.
 */
extern uint16_t stack_start;

/*
 * zero_reg - Reset registers to 0
 *
 * This function is defined in asm.S file
 */
extern void zero_reg(void);

/**
 * init - Entry point for the framework
 *
 * This is the entry point for the framework. After the reset interrupt
 * is triggered, PC should be updated with the address of this function.
 * This function initialises stack pointer and set the register bank to
 * architecturally defined reset state. Later it jumps to 'engine', from
 * here the framework boots.
 */
void init()
{
	/* Get stack start */
	uint16_t *stack_location = &stack_start;

	/* Update the Stack pointer */
	MMIO8(SPL) = (uint8_t)((uint16_t)stack_location & 0x00ff);
	MMIO8(SPH) = (uint8_t)(((uint16_t)stack_location >> 8) & 0x00ff);

	/* Set resisters to architecturally defined reset */
	zero_reg();

	/* Boot framework */
	engine();

	/* Accidental trap, if control returns from framework */
	exit(EXIT_FAILURE);
}
