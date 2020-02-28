#include <arc.h>
#include <project.h>
#include <arc/stdbool.h>
#include <arc/stdlib.h>
#include <arc/stdint.h>
#include <status.h>

volatile uint32_t ArcVersion __attribute__((section(".version"))) = VERSION;

#if AUTOINIT==1
status_t autoinit();
#endif

void arc()
{	
#if AUTOINIT==1
	autoinit();
#endif

	project_setup();

	while(true)
		project_loop();
	exit(EXIT_FAILURE);
}
