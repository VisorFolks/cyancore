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
	uint8_t cs;
	uint8_t s;
	uint8_t m;
	uint8_t h;
	uint32_t dd;
} time_t;

status_t get_timestamp(uint64_t *);
status_t get_timeticks(uint64_t *);
status_t udelay(uint16_t);
status_t mdelay(uint16_t);
status_t getTime(time_t *);
