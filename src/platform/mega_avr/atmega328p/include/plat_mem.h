/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: plat_mem.h
 * Description		: This file contains memory config of atmega328p
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define FLASH_SIZE	32K
#define RAM_SIZE	2K

#define V_IMEM_START	0x00000000
#define V_DMEM_START	0x00800100

#define L_MEM_START	0x00000000

#define IMEM_LENGTH	0x8000
#define DMEM_LENGTH	0x0800

#define ALIGN_BOUND	2
#define HEAP_ALIGN	1
