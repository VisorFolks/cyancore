/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: stdint.h
 * Description		: This file contains sources of libc-stdint
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STDINT_H_

#include <limits.h>
#include <../include/stdint-gcc.h>

#if !defined(size_t)
typedef __SIZE_TYPE__ size_t;
#endif
