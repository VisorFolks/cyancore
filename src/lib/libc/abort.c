/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: abort.c
 * Description		: This file contains sources of libc-abort
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern void plat_panic_handler();

void abort(void)
{
	plat_panic_handler();
loop:
	goto loop;
}
