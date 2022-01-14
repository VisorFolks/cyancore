#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <status.h>
#include <arch.h>
#include <terravisor/platform.h>
#include <terravisor/workers.h>
#include <platform.h>

unsigned int reset_syndrome;

void platform_early_setup()
{
	status_t ret = success;

	ret |= platform_copy_data();
	ret |= platform_copy_itim();
	ret |= platform_bss_clear();

	reset_syndrome = 1;
	
	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_setup()
{
	status_t ret = success;

//	ret |= platform_resources_setup();

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_cpu_setup()
{
	status_t ret = success;

	arch_ei();

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}
