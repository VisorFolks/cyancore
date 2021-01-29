#include <engine.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <compiler_macros.h>

volatile uint32_t FWVersion __attribute__((section(".version"))) = VERSION;

char cyancore_ascii_insignia[] =
"\n\r    | | | | |\n\r\
---           ---\n\r\
---           ---\n\r\
---   < / >   ---\n\r\
--- Cyancore® ---\n\r\
---           ---\n\r\
    | | | | |\n\n\r";

_WEAK void plug()
{
	asm volatile("");
	return;
}

_WEAK void play()
{
	asm volatile("");
	return;
}

void engine()
{
	plug();
player:
	play();
	goto player;
}
