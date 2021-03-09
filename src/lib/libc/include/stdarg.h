/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: stdarg.h
 * Description		: This file contains sources of libc-stdarg
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STDARG_H_

#define va_list			__builtin_va_list
#define va_start(ap, last)	__builtin_va_start(ap, last)
#define va_end(ap)		__builtin_va_end(ap)
#define va_copy(to, from)	__builtin_va_copy(to, from)
#define va_arg(to, type)	__builtin_va_arg(to, type)
