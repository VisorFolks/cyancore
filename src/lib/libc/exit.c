/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: exit.c
 * Description		: This file contains sources of libc-exit
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdlib.h>
#include <stdbool.h>

static void (*exit_func)(int status);

void exit(int status)
{
	if(exit_func)
		(*exit_func)(status);
	while(true);
}

int atexit(void (*func)(int status))
{
	if(exit_func)
		return -1;
	exit_func = func;
	return 0;
}
