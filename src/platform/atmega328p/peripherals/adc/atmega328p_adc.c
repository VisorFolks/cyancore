#include <adc.h>
#include <assert.h>
#include <stdint.h>
#include <platform_api.h>

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

void platform_adc_setup(adc_prescale_clk ps)
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

void platform_adc_refv(adc_refv v)
{
	// Configure adc reference voltage
	switch(v)
	{
		case i1_1:
			REG(ADMUX) |= (3 << REFS);
			break;
		case ivref:
			REG(ADMUX) |= (0 << REFS);
			break;
		case aref:
			REG(ADMUX) |= (1 << REFS);
			break;
		default:
			assert(0);
	}
}

void platform_adc_res(adc_res res)
{
	use_res = res;
	// Configure res (left align)
	switch(res)
	{
		case bit8:
			REG(ADMUX) |= (1 << ADLAR);
			break;
		case bit10:
			REG(ADMUX) &= ~(1 << ADLAR);
			break;
		default:
			assert(0);
	}
}

uint16_t platform_adc_read(uint8_t pin)
{
	uint8_t adch, adcl;
	assert(pin <= 7);
	// Set pin number
	REG(ADMUX) |= (pin & 0x07);
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

