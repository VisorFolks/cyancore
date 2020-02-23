#include <arc.h>
#include <project.h>
#include <arch.h>
#include <arc/stdbool.h>
#include <arc/stdint.h>
#include <arc/stdlib.h>
#include <arc/stdio.h>
#include <lock/spinlock.h>

volatile uint32_t ArcVersion __attribute__((section(".version"))) = VERSION;

extern void platform_early_setup();
extern void platform_setup();
extern void platform_cpu_setup();

static uint8_t boot_done = 0;
spinlock_t arc_lock;

void arc()
{
	static uint8_t n_cpu_online = 0;
	bool boot = false;
	
	arch_early_setup();
	arch_setup();

	// Critical section start
	spinlock_acquire(&arc_lock);
	if(!boot_done)
	{
		boot_done = 1;
		boot = true;
	}
	else
	{
		boot = false;
	}
	spinlock_release(&arc_lock);
	// Critical section end

	if(boot)
		goto boot;
	else
		goto boot_end;
boot:
	aprintf("< ! > Arc Framework version %x\n", ArcVersion);
	platform_early_setup();
	platform_setup();
boot_end:
	platform_cpu_setup();
	aprintf("< ! > ARC: Boot complete!\n");

	n_cpu_online++;

	project_setup();

	while(true)
		project_loop();
	exit(EXIT_FAILURE);

}
