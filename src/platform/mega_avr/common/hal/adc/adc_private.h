/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: adc_private.h
 * Description		: This file contains macros used by adc HAL
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _ADC_PRIVATE_H_

#include <compiler_macros.h>

#ifndef N_ADC_PINS
#define N_ADC_PINS	1
INFO(< ! > Using N_ADC_PINS = 1)
#endif

#define ADCL_OFFSET	0x00
#define ADCH_OFFSET	0x01
#define ADCSRA_OFFSET	0x02
#define ADCSRB_OFFSET	0x03
#define ADMUX_OFFSET	0x04

#define CTO		1
#define CTK		1

/**
 * DIDR0 & DIDR2 are given to ADC module
 * DIDR0 controls pins 0-7
 * DIDR2 controls pins 8-15
 *
 * But in memory map DIDR2 falls before DODR0
 * So while computing the address of DIDR(X)
 * subtract from base address
 */
#define DIDR_OFFSET	0x06

// ADCSRA Bitfields
#define ADPS		0
#define ADIE		3
#define ADIF		4
#define ADATE		5
#define ADSC		6
#define ADEN		7

//ADCSRB Bitfields
#define ADTS		0
#define ACME		6

// ADCMUX Bitfields
#define MUX		0
#define ADLAR		5
#define REFS		6

// Prescaler division factors
#define fdiv2		1
#define fdiv4		2
#define fdiv8		3
#define fdiv16		4
#define fdiv32		5
#define fdiv64		6
#define fdiv128		7
