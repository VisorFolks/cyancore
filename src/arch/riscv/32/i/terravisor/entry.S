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
#include <plat_mem.h>

/**
 * stack_start - Variable pointing to stack start assigned while linking
 *
 * @brief This variable is substituted by the linker with actual value of
 * stack start. Please refer linker script for this variable assignment.
 */

/**
 * global_start - Variable pointing to global start assigned while linking
 *
 * @brief This variable is substituted by the linker with actual value of
 * global start. Please refer linker script for this variable assignment.
 * RISC-V CPU has global var symbol access range of gp +/- 2KB, total of 4KB.
 * gp = <start_of_s(data/bss)> + 0x800
 */

/**
 * tls_start - Variable pointing to thread data start assigned while linking
 *
 * @brief This variable is substituted by the linker with actual value of
 * tls start. Please refer linker script for this variable assignment.
 */

/**
 * Entry - Entry point of the framework
 *
 * @brief This is the entry point for the framework. After the reset interrupt
 * is triggered, PC should be updated with the address of this function.
 * This function initialises stack pointer and later it jumps to 'init',
 * from here the framework boots.
 */
function entry
.option push
.option norvc
.option norelax
	la	gp, _global_start
.option pop

stack_setup:
	la	a0, _stack_start
	csrr	a1, mhartid
	mv	t0, zero
1:	/* Start of for loop, assume mul is not supported */
	beq	t0, a1, 1f
	li	t1, STACK_SIZE_PCPU
	sub	a0, a0, t1
	addi	t0, t0, 1
	j	1b
1:
	mv	sp, a0
	mv	a0, zero
	mv	a1, zero
	mv	t0, zero
	mv	t1, zero

jump_to_init:
	j	init
