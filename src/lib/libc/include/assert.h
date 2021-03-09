/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: assert.h
 * Description		: This file contains sources of libc-assert
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define assert_dbg(X)	(X ? (void)0 : __assert_dbg(__func__, __LINE__))
#define assert(X)	(X ? (void)0 : __assert())

void __assert_dbg(const char *, unsigned int);
void __assert();
