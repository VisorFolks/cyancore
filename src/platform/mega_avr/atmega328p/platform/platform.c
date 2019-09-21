#include <platform_api.h>
#include <shi.h>

SYSTEM_HARDWARE_INFO;

void platform_early_setup()
{
	shi config =
	{
		.architecture		= ARCHITECTURE,
		.datawidth		= BITWIDTH,
		.n_adc			= 1,
		.adc_base_addr[0]	= ADCL,
		.adc_interrupt_id[0]	= 22,
	};
	UPDATE_SHI(config);
	return;
}

void platform_setup()
{
	return;
}
