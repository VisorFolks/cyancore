/*
 * CYANCORE LICENSE
 * Copyrights (C) 2021, Cyancore Team
 *
 * File Name		: insignia.h
 * Description		: This file consists of all insignia/banners
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _INSIGNIA_H_

#include <stdio.h>
#include <stdint.h>
#include <engine.h>

static inline void cyancore_insignia()
{
	extern char cyancore_ascii_insignia[];
	extern ccver_t FWVersion;
	printf("%s\nVersion %d.%d.%d\n", cyancore_ascii_insignia,
		FWVersion.v.arch, FWVersion.v.major, FWVersion.v.minor);
}

static inline void cyancore_insignia_lite()
{
	extern char cyancore_ascii_insignia_lite[];
	extern ccver_t FWVersion;
	printf("%s v%d.%d.%d\n", cyancore_ascii_insignia_lite,
		FWVersion.v.arch, FWVersion.v.major, FWVersion.v.minor);
}
