/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_copy data.S
 * Description		: This file contains platform data flash routine
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>
#include <plat_mem.h>

function platform_copy_data
	ldi	r17, hi8(_data_vend)
	ldi	r26, lo8(_data_vstart)
	ldi	r27, hi8(_data_vstart)
	ldi	r30, lo8(_data_start)
	ldi	r31, hi8(_data_start)
	rjmp	1f
2:
	lpm	r0, Z+
	st	X+, r0
1:
	cpi	r26, lo8(_data_vend)
	cpc	r27, r17
	brmi	2b
	breq	2b
	ldi	r24, 0
	ldi	r25, 0
	ret
