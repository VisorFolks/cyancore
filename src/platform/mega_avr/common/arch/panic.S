/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: panic.S
 * Description		: This file contains platform panic handler
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>

function plat_panic_handler
	push	r24
	ldi	r24, 254
	jmp	isr
