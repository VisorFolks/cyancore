/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: wdt_util.S
 * Description		: This file contains wdt HAL driver utilities
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>
#include <plat_arch.h>
#include "wdt_private.h"

/**
 * write_wdtcsr - Writes to WDTCSR
 *
 * @brief This function is responsible to write data to WDTCSR.
 * To perfom a successful write to this register, first set WDCE
 * and WDE bits in WDTCSR, upon successful write we get 4 clocks
 * to write the data to register.
 * The writes to this register is controlled to prevent accidental
 * writes.
 *
 * Note:
 *     - or/ori/and and other instructions take 1 clock
 *     - ld/st takes 2 clocks
 *
 * @param data - Data to be written to the register
 * @return void
 */
function write_wdtcsr
	/*
	 * In this function we are hardcoding the address as the
	 * MegaAVR uses same address in all mcus.
	 * We can chose to make it dynamic, at the cost of number
	 * of instructions. To make it dynamic, use r20-23 as args.
	 */
	ldi	r25, WDTCSR
	ori	r25, (1 << WDCE) | (1 << WDE)
	sts	WDTCSR, r25
	// 4 clks from now
	sts	WDTCSR, r24
	nop
	nop
	ret
