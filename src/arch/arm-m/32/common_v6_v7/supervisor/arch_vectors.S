/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: arch_verctors.S
 * Description		: This file consists of array of vector table
 *			  specific to arm-m proile.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>

object arch_vectors
	.word _stack_start
	.word init

.set i, 1
.rept (N_EXCEP + N_IRQ)
	.word isr
.set i, i+1
.endr
