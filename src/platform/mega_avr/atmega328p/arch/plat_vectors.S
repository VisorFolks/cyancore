/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: plat_vectors.S
 * Description		: This file contains platform vector of atmega328p
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <asm.inc>

vectors platvectors
	jmp	int_1
	jmp	int_2
	jmp	int_3
	jmp	int_4
	jmp	int_5
	jmp	int_6
	jmp	int_7
	jmp	int_8
	jmp	int_9
	jmp	int_10
	jmp	int_11
	jmp	int_12
	jmp	int_13
	jmp	int_14
	jmp	int_15
	jmp	int_16
	jmp	int_17
	jmp	int_18
	jmp	int_19
	jmp	int_20
	jmp	int_21
	jmp	int_22
	jmp	int_23
	jmp	int_24
	jmp	int_25
