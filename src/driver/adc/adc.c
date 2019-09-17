#include <adc.h>
#include <platform_api.h>
#include <assert.h>
#include <stdint.h>

void adc_setup(adc_prescale_clk ps)
{
	platform_adc_setup(ps);
}

uint16_t adc_read(uint8_t pin, adc_refv v, adc_res res)
{
	uint16_t adc_value;
	platform_adc_refv(v);
	platform_adc_res(res);
	adc_value = platform_adc_read(pin);
	return adc_value;
}
