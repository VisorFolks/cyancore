#include <adc.h>
#include <assert.h>
#include <stdint.h>
#include <platform_api.h>

#define ADCL_OFFSET	0x00
#define ADCH_OFFSET	0x01
#define ADCSRA_OFFSET	0x02
#define ADCSRB_OFFSET	0x03
#define ADMUX_OFFSET	0x04
#define DIDR2_OFFSET	0x05
#define DIDR0_OFFSET	0x06
#define DIDR1_OFFSET	0x07

// PRR bit field
#define PRADC		0
// ADCSRA bit fields
#define ADEN		7
#define ADSC		6
#define ADATE		5
#define ADIE		3
// ADMUX bit fields
#define REFS		6
#define ADLAR		5

// Vaiable to define resolution used by adc instance
volatile adc_res use_res;

void platform_adc_enable(adc_prescale_clk ps)
{
	assert(ps <= div128);
	// Enable clock to adc module
	REG(PRR) |= (1 << PRADC);
	// Enable ADC module
	REG(ADCSRA) |= (1 << ADEN);
	
	/* Configuring the driver to free running mode
	 * if auto trigger mode is needed you may add
	 * code here
	 *
	 * TODO: Add the enum type for auto trigger in
	 * 'adc.h' under Arc/src/include/
	 */

	// Configure adc clk prescalling
	REG(ADCSRA) |= (ps & 0x07);
}

uint8_t platform_adc_refv(adc_refv v)
{
	// Configure adc reference voltage
	switch(v)
	{
		case i1_1:
			return 3;
		case ivref:
			return 0;
		case aref:
			return 1;
		default:
			assert(0);
	}
	return 1;
}

uint8_t platform_adc_res(adc_res res)
{
	// Configure res (left align)
	switch(res)
	{
		case bit8:
			return 1;
		case bit10:
			return 0;
		default:
			assert(0);
	}
	return 0;
}

uint16_t platform_adc_read(adc_config * config)
{
	uint8_t adch, adcl;
	assert(config -> a_pin <= 7);
	// Set pin number, ref voltage, res
	REG(ADMUX) = (config -> a_pin & 0x07) | (config -> refv << REFS) | (config -> res << ADLAR);
	// Start ADC Conversion
	REG(ADCSRA) |= (1 << ADSC);
	while(REG(ADCSRA) & (1 << ADSC));	// busy wait till the conversion is done
	switch(use_res)
	{
		case bit8:
			adch = REG(ADCH);
			REG(ADMUX) = 0;
			return (uint16_t) adch;
		case bit10:
			adcl = REG(ADCL);
			adch = REG(ADCH);
			REG(ADMUX) = 0;
			return (((uint16_t) adch) << 8 | (uint16_t) adcl);
		default:
			assert(0);
	}
	return 0;
}

#if USE_ONBOARD_TEMPERATURE_SENSOR
uint16_t platform_core_temperature()
{
	uint8_t adch, adcl;
	REG(ADMUX) |= (3 << REFS) | (1 << 3);
	REG(ADCSRA) |= (1 << ADSC);
	while(REG(ADCSRA) & (1 << ADSC));
	adcl = REG(ADCL);
	adch = REG(ADCH);
	REG(ADMUX) = 0;
	return ((((((uint16_t) adch) << 8 | (uint16_t) adcl)) - CTO) / CTK);
}
#endif

void platform_adc_ei()
{
	REG(ADCSRA) |= (1 << ADIE);
}

void platform_adc_ci()
{
	REG(ADCSRA) &= ~(1 << ADIE);
}

