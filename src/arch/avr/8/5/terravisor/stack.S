/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: stack.S
 * Description		: This file defines the stack space for the AVR core
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <plat_mem.h>
#include <asm.inc>

/**
 * stack - Stack object for AVR cores
 *
 * \brief This defines stack space for AVR core. It is ideal to declare a
 * stack space apriory to avoid shortage of stack after the data in
 * ro-section and heap-section are defined by linker.
 */

.global stack_end
.global stack_start
object stack
stack_end:
	.space STACK_SIZE, 0
stack_start:
