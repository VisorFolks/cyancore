/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: time.h
 * Description		: This file contains sources of libc-time
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */
#pragma once
#define _TIME_H_

typedef struct time
{
	uint8_t s;
	uint8_t m;
	uint8_t h;
	uint8_t dd;
	uint8_t mm;
	uint8_t yy;
	uint8_t c;
} time_t;
