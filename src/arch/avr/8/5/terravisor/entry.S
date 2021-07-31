/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: entry.S
 * Description		: This file consists of entry point of the framework.
 *			  After the reset of system, program in this file gets
 *			  executed.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>
#include <plat_arch.h>

/**
 * stack_start - Variable pointing to stack start assigned while linking
 *
 * This variable is substituted by the linker with actual value of
 * stack start. Please refer linker script for this variable assignment.
 */

/**
 * Entry - Entry point of the framework
 *
 * This is the entry point for the framework. After the reset interrupt
 * is triggered, PC should be updated with the address of this function.
 * This function initialises stack pointer and later it jumps to 'init',
 * from here the framework boots.
 */
function entry
	cli
	ldi	r18, lo8(stack_start)
	ldi	r30, SPL
	st	Z, r18
	ldi	r18, hi8(stack_start)
	ldi	r30, SPH
	st	Z, r18
	eor	r18, r18
	eor	r30, r30
	rjmp	init
