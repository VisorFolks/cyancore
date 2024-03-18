/*
 * CYANCORE LICENSE
 * Copyrights (C) 2023, Cyancore Team
 *
 * File Name		: plat_mem.h
 * Description		: This file contains memory config of fe310-g002
 * Primary Author	: Mayuri Lokhande [mayurilokhande01@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define FLASH_SIZE	16M
#define RAM_SIZE	264K

#define V_IMEM_START	0x10000000
#define V_DMEM_START	0x21000000
#define V_STAK_START	0x20040000

#define L_MEM_START	0x10000000
#define	L_MEM_LENGTH	16M

#define DMEM_LENGTH	264K
#define	IMEM_LENGTH	16M

#define ALIGN_BOUND	4
#define HEAP_ALIGN      ALIGN_BOUND
