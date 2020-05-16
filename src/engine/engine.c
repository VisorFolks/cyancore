#include <engine.h>
#include <project.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <status.h>

volatile uint32_t FWVersion __attribute__((section(".version"))) = VERSION;

#if AUTOINIT==1
status_t autoinit();
#endif

void engine()
{
#if AUTOINIT==1
	autoinit();
#endif
	project_setup();

	while(true)
		project_loop();

	exit(EXIT_FAILURE);
}
