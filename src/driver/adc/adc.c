#include <adc.h>
#include <shi.h>
#include <platform_api.h>
#include <assert.h>
#include <stdint.h>

SYSTEM_HARDWARE_INFO;

void adc_enable(uint8_t module, adc_prescale_clk ps)
{
	shi * config;
	FETCH_SHI(config);
	assert(config -> n_adc > 0);
	platform_adc_enable(ps);
}

void adc_setup(adc_config * config, adc_refv v, adc_res res)
{
	config -> refv = platform_adc_refv(v);
	config -> res = platform_adc_res(res);
}

uint16_t adc_read(adc_config * config)
{
	uint16_t adc_value;
	adc_value = platform_adc_read(config);
	return adc_value;
}
