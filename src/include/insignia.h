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
	printf("%s", cyancore_ascii_insignia);
}
