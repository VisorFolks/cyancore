#include <arc.h>
#include <project.h>
#include <arch.h>
#include <stdint.h>

volatile uint32_t ArcVersion __attribute__((section(".version"))) = VERSION;

void arc()
{
	arch_init();
	project_setup();
	while(1)
	{
		project_loop();
	}
	return;
}
