/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: plat_mem.h
 * Description		: This file contains memory config of fe310-g002
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define FLASH_SIZE	(4M-64K)
#define RAM_SIZE	16K

#define V_ITMEM_START	0x08000000
#define V_IMEM_START	0x20000000
#define V_DMEM_START	0x80000000

#define L_MEM_START	0x20000000
#define L_MEM_LENGTH	0x003f0000

#define ITMEM_LENGTH	0x00002000
#define IMEM_LENGTH	0x20000000
#define DMEM_LENGTH	0x00004000

#define ALIGN_BOUND	4
#define HEAP_ALIGN	ALIGN_BOUND
