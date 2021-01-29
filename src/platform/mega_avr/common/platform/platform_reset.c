#include <stdint.h>
#include <status.h>
#include <platform.h>
#include <terravisor/platform.h>

extern uint8_t reset_syndrome;

_WEAK reset_t plarform_get_reset_syndrome()
{
	return (reset_t) reset_syndrome;
}

_WEAK void platform_reset_handler(reset_t rsyn)
{
	if(rsyn > external_reset)
		plat_panic_handler();
	return;
}
