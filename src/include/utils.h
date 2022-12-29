/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: utils.h
 * Description		: This file defines the utilities macros
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define RET_ON_FAIL(condition, status)	if(!(condition)) return status
#define ROUNDUP_ALIGN(x, align)		x += align - (x % align)
