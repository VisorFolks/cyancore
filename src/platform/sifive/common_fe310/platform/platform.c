#include <stdint.h>
#include <status.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddev.h>
#include <arch.h>
#include <driver.h>
//#include <driver/console.h>
#include <driver/sysclk.h>
#include <insignia.h>
#include <terravisor/platform.h>
#include <terravisor/workers.h>
#include <platform.h>

void platform_early_setup()
{
	status_t ret = success;

	ret |= platform_copy_data();
	ret |= platform_copy_itim();
	ret |= platform_bss_clear();
	ret |= platform_resources_setup();
	syslog_stdout_disable();
	driver_setup("mslog");

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_setup()
{
	status_t ret = success;

	driver_setup("sysclk_prci");
	ret |= sysclk_reset();

	driver_setup("earlycon");
	bootmsgs_enable();
	cyancore_insignia();

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_cpu_setup()
{
	arch_ei();
	return;
}
