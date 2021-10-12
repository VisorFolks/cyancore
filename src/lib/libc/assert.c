/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: assert.c
 * Description		: This file contains sources of libc-assert
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <status.h>

#if CONSOLE
#include <driver/console.h>
#endif

extern void plat_panic_handler();
void __assert_dbg(const char *func, unsigned int line)
{
	printf("< x > Assert: %s - %d\n", func, (int)line);
#if CONSOLE
	console_flush();
#endif
	plat_panic_handler();
}

void __assert()
{
#if CONSOLE
	console_flush();
#endif
	plat_panic_handler();
}
