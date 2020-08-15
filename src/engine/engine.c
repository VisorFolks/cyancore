#include <engine.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <compiler_macros.h>

volatile uint32_t FWVersion __attribute__((section(".version"))) = VERSION;

char cyancore_insignia[] =
"\n    | | | | |\n\r\
---           ---\n\r\
---           ---\n\r\
---   < / >   ---\n\r\
--- Cyancore® ---\n\r\
---           ---\n\r\
    | | | | |\n\n\r";

_WEAK void launch()
{
	asm volatile("");
	return;
}

_WEAK void encore()
{
	asm volatile("");
	return;
}

void engine()
{
	launch();
	while(true)
		encore();

	exit(EXIT_FAILURE);
}
