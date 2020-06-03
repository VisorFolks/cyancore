#include <engine.h>
#include <project.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

volatile uint32_t FWVersion __attribute__((section(".version"))) = VERSION;

void engine()
{
	project_setup();
	while(true)
		project_loop();

	exit(EXIT_FAILURE);
}
