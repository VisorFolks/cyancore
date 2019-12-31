#include <arc.h>
#include <project.h>
#include <arch.h>
#include <stdint.h>

volatile uint32_t ArcVersion __attribute__((section(".version"))) = VERSION;

extern void platform_early_setup();
extern void platform_setup();

void arc()
{
	static uint8_t boot_done = 0;
	static uint8_t n_cpu_online = 0;
	boot_done = 0;

	arch_early_setup();
	arch_setup();

	if(!boot_done)
	{
		platform_early_setup();
		platform_setup();
#if USE_KERNEL==1
// Only needs to be executed once during first boot
		heap_setup();
		kernel_setup();
#endif
		boot_done = 1;
	}

	n_cpu_online++;

	project_setup();
	while(1)
	{
		project_loop();
	}
	return;
}
