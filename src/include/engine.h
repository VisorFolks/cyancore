/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: engine.h
 * Description		: This file consists of cyancore engine prototype
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _ENGINE_H_

typedef union __ccver
{
	uint32_t v32;
	struct
	{
		uint32_t minor: 8;
		uint32_t major: 16;
		uint32_t arch : 8;
	} v;
} ccver_t;

void engine();
