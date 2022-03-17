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
	printf("%s\nVersion %u.%u.%u\n", cyancore_ascii_insignia,
		(uint8_t) FWVersion.v.arch, (uint16_t) FWVersion.v.major,
		(uint8_t) FWVersion.v.minor);
}

static inline void cyancore_insignia_lite()
{
	extern char cyancore_ascii_insignia_lite[];
	extern ccver_t FWVersion;
	printf("%s v%u.%u.%u\n", cyancore_ascii_insignia_lite,
		(uint8_t) FWVersion.v.arch, (uint16_t) FWVersion.v.major,
		(uint8_t) FWVersion.v.minor);
}
