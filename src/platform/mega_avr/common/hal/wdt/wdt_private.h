/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: wdt_private.h
 * Description		: This file contains defines and prototypes of
 *                        functions used by watchdog timer HAL driver
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define WDIF		7
#define WDIE		6
#define WDP3		5
#define WDCE		4
#define WDE		3
#define WDP2		2
#define WDP1		1
#define WDP0		0

#ifndef __ASSEMBLER__
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
void write_wdtcsr(uint8_t);
#endif
