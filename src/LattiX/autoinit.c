#include <stdint.h>
#include <status.h>
#include <arch.h>

#if AUTOINIT==1
extern void platform_early_setup();
extern void platform_setup();
extern void platform_cpu_setup();
extern volatile uint32_t ArcVersion;

status_t autoinit()
{
	arch_early_setup();
	arch_setup();

	if(arch_core_id() == PRIMARY_CORE_ID)
	{
		platform_early_setup();
		platform_setup();
	}

	platform_cpu_setup();

	return success;
}
#endif