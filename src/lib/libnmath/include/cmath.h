/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cmath.h
 * Description		: This file consists of complex math prototypes
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#include <stdint.h>

#define CREATE_COMPLEX_DATATYPE(type)	\
	typedef struct complex_##type	\
	{				\
		type x;			\
		type y;			\
	} c##type

#define COMPLEX(a, b)			{.x=a, .y=b}

/* int types */
CREATE_COMPLEX_DATATYPE(uint8_t);
CREATE_COMPLEX_DATATYPE(int8_t);
CREATE_COMPLEX_DATATYPE(uint16_t);
CREATE_COMPLEX_DATATYPE(int16_t);
CREATE_COMPLEX_DATATYPE(uint32_t);
CREATE_COMPLEX_DATATYPE(int32_t);
CREATE_COMPLEX_DATATYPE(uint64_t);
CREATE_COMPLEX_DATATYPE(int64_t);

/* generic types */
CREATE_COMPLEX_DATATYPE(int);
CREATE_COMPLEX_DATATYPE(long);
CREATE_COMPLEX_DATATYPE(float);
CREATE_COMPLEX_DATATYPE(double);
