#include <stdint.h>
#include <status.h>
#include <arch.h>
#include <terravisor/platform.h>
#include <terravisor/bootloader.h>


status_t bootloader()
{
	arch_early_setup();
	arch_setup();

	if(arch_core_id() == BOOT_CORE_ID)
	{
		platform_early_setup();
		platform_setup();
	}

	platform_cpu_setup();

	return success;
}
