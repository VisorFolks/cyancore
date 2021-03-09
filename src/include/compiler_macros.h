/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: compiler_macro.h
 * Description		: This file defines the compiler macro utilities
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _PRAGMA(x)	_Pragma (#x)
#define INFO(x)		_PRAGMA(message (#x))
#define WARN(x)		_PRAGMA(GCC warning #x)
#define ERROR(x)	_PRAGMA(GCC error #x)
#define TODO(x)		INFO(TODO: x)

#define _WEAK		__attribute__((weak))
#define _UNUSED		__attribute__((unused))
