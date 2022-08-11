/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: plat_mem.h
 * Description		: This file contains memory config of atmega328p
 * Primary Author	: Rahul Goyal [rhgoyal01@gmail.com]
 * Organisation		: Cyancore Contributor
 */

#pragma once

#define FLASH_SIZE	128K
#define RAM_SIZE	8K

#define V_IMEM_START	0x00000000
#define V_DMEM_START	0x00800200

#define L_MEM_START	0x00000000

#define IMEM_LENGTH	0x20000
#define DMEM_LENGTH	0x1fff

#define ALIGN_BOUND	2

#define STACK_SIZE	1024

#define HEAP_SIZE	1024
