/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: engine.c
 * Description		: This file contains sources of cyancore engine
 *			  It also defines cyancore insignia
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <status.h>
#include <arch.h>
#include <engine.h>

const ccver_t FWVersion _SECTION(".version") =
{
	.v32 = VERSION,
};

const char cyancore_ascii_insignia[] =
"\n    | | | | |\n\
---           ---\n\
---           ---\n\
---   < / >   ---\n\
--- Cyancore© ---\n\
---           ---\n\
    | | | | |\n\n";

const char cyancore_ascii_insignia_lite[] = "Cyancore© < / >";

_WEAK void plug()
{
	asm volatile("");
	return;
}

_WEAK void play()
{
	arch_wfi();
	return;
}

_WEAK void plug_secondary()
{
	asm volatile("");
	return;
}

_WEAK void play_secondary()
{
	arch_wfi();
	return;
}

void engine()
{
	plug();

	do
		play();
	while(1);
}

void engine_secondary()
{
	plug_secondary();

	do
		play_secondary();
	while(1);
}
