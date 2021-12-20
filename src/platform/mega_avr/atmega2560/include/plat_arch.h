/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: plat_arch.h
 * Description		: This file contains arch specific defines and
 *			  prototypes
 * Primary Author	: Rahul Goyal [rhgoyal01@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _PLAT_ARCH_H_

#define __AVR_ATMEGA328P__
#define ARCH_AVR

#define GPIOR0		0x3e
#define GPIOR1		0x4a
#define GPIOR2		0x4b
#define MCUSR		0x54
#define MCUSR_WDRF	0x3
#define MCUCR		0x55
#define SPMCSR		0x57
#define SPL		0x5d
#define SPH		0x5e
#define SREG		0x3f
#define SMCR		0x53
#define WDTCSR		0x60
#define CLKPR		0x61
#define PRR0		0x64
#define PRR1		0x65
#define OSCCAL		0x66

#ifdef _MACHINE_CALL_H_
extern void (*mcall)(unsigned int, unsigned int, unsigned int, unsigned int, mret_t *);
#endif
