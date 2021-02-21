#include <stdint.h>
#include <status.h>
#include <arch.h>
#include <terravisor/platform.h>
#include <terravisor/bootstrap.h>


status_t bootstrap()
{
	reset_t resetSyndrome;
	arch_early_setup();
	arch_setup();

	if(arch_core_id() == BOOT_CORE_ID)
	{
		platform_early_setup();
		platform_setup();
		resetSyndrome = platform_get_reset_syndrome();
		platform_reset_handler(resetSyndrome);
	}

	platform_cpu_setup();

	return success;
}
