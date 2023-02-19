/*
 * CYANCORE LICENSE
 * Copyrights (C) 2023, Cyancore Team
 *
 * File Name		: platform.c
 * Description		: This file contains sources for platform apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <platform.h>

void platform_jump_to_user_code(void)
{
	void (*jmp)(void) = (void *) 0x20000000;
	jmp();
}
