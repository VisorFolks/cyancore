/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: stdbool.h
 * Description		: This file contains sources of libc-stdbool
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STDBOOL_H_

#ifndef __cplusplus
typedef _Bool bool;
#endif

#define true		1
#define false		0

#define __bool_true_false_are_defined	1
