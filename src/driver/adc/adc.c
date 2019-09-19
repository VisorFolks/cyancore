#include <adc.h>
#include <platform_api.h>
#include <assert.h>
#include <stdint.h>

void adc_enable(adc_prescale_clk ps)
{
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
