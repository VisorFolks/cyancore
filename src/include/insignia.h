/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: insignia.h
 * Description		: This file consists of all insignia/banners
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdio.h>

static inline void cyancore_insignia()
{
	extern char cyancore_ascii_insignia[];
	extern uint32_t FWVersion;
	printf("%s\nVersion: 0x%08lx\n", cyancore_ascii_insignia, (unsigned long)FWVersion);
}

static inline void cyancore_insignia_lite()
{
	extern char cyancore_ascii_insignia_lite[];
	extern uint32_t FWVersion;
	printf("%s Version: 0x%08lx\n", cyancore_ascii_insignia_lite, (unsigned long)FWVersion);
}
