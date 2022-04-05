/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: stdlib.h
 * Description		: This file contains sources of libc-rand
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STDLIB_H_
#include <status.h>
#define EXIT_FAILURE		1
#define EXIT_SUCCESS		0
#define ATEXIT_MAX		1

void abort(void);
int atexit(void (*func)(int));
void exit(int status) _NORETURN;
