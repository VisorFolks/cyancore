/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: stddef.h
 * Description		: This file contains sources of libc-stddef
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STDDEF_H_

#ifndef NULL
#define NULL		((void *)0x00)
#endif

#define offsetof(st, m)	__builtin_offsetof(st, m)
