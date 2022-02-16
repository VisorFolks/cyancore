#include <stdint.h>
#include <status.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddev.h>
#include <arch.h>
#include <driver.h>
#include <driver/console.h>
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
	driver_setup("stdlogger");
	//driver_setup("earlycon");
	//syslog_print();
	//syslog_stdout_enable();
	stdout_register(&logger_putc);

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_setup()
{
	status_t ret = success;

	cyancore_insignia();

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

void platform_cpu_setup()
{
	status_t ret = success;

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}
