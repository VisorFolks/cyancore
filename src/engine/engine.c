#include <engine.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <compiler_macros.h>

volatile uint32_t FWVersion __attribute__((section(".version"))) = VERSION;

char cyancore_logo[] =
"\n    | | | | |\n\r\
---           ---\n\r\
---           ---\n\r\
---   < / >   ---\n\r\
--- Cyancore® ---\n\r\
---           ---\n\r\
    | | | | |\n\n\r";

_WEAK void setup()
{
	asm volatile("");
	return;
}

_WEAK void loop()
{
	asm volatile("");
	return;
}

void engine()
{
	setup();
	while(true)
		loop();

	exit(EXIT_FAILURE);
}
