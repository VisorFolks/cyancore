#include <status.h>
#include <arch.h>
#include <arc/stdbool.h>
#include <arc/stdint.h>
#include <arc/stdlib.h>
#include <arc/stdio.h>
#include <lock/spinlock.h>

#if AUTOINIT==1
extern void platform_early_setup();
extern void platform_setup();
extern void platform_cpu_setup();
extern volatile uint32_t ArcVersion;

status_t autoinit()
{
	static uint8_t boot_done = 0;
	spinlock_t arc_lock;
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
	{
		aprintf("< ! > Arc Framework version %x\n", ArcVersion);
		platform_early_setup();
		platform_setup();
	}
	platform_cpu_setup();
	aprintf("< ! > ARC: Boot complete!\n");

	n_cpu_online++;

	return success;
}
#endif
