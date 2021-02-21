/*
 * File Name		: arch_vectors.S
 * Description		: This file defines architecture specific interrupt vectors
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 */

#include <asm.inc>
/**
 * archvectors - AVR architecture defined interrupt vectors section
 */
vectors archvectors
	jmp	init
