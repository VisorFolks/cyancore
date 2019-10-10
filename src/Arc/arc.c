#include <arc.h>
#include <platform_api.h>
#include <project.h>
#include <arch.h>
#include <stdint.h>

volatile uint32_t ArcVersion __attribute__((section(".version"))) = VERSION;

void arc()
{
	arch_setup();
	platform_early_setup();
	platform_setup();
	project_setup();
	while(1)
	{
		project_loop();
	}
	return;
}
