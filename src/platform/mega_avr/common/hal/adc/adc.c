/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: adc.c
 * Description		: This file contains sources for mega-avr
 *			  HAL adc apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <status.h>
#include <mmio.h>
#include <platform.h>
#include <interrupt.h>
#include <hal/adc.h>
#include <device.h>
#include <arch.h>
#include "adc_private.h"

static inline void _adc_enable(adc_port_t *port)
{
	MMIO8(port->baddr + ADCSRA_OFFSET) |= (1 << ADEN);
}

static inline void _adc_disable(adc_port_t *port)
{
	MMIO8(port->baddr + ADCSRA_OFFSET) &= ~(1 << ADEN);
}

static inline status_t _adc_set_prescaler(adc_port_t *port)
{
	uint8_t pscale_value = 0;
	status_t ret = success;
	switch(port->fdiv)
	{
		case 2:
			pscale_value = fdiv2;
			break;
		case 4:
			pscale_value = fdiv4;
			break;
		case 8:
			pscale_value = fdiv8;
			break;
		case 16:
			pscale_value = fdiv16;
			break;
		case 32:
			pscale_value = fdiv32;
			break;
		case 64:
			pscale_value = fdiv64;
			break;
		case 128:
			pscale_value = fdiv128;
			break;
		default:
			ret = error_inval_arg;
	}
	MMIO8(port->baddr + ADCSRA_OFFSET) |= (pscale_value & 0x7);
	return ret;
}

static inline void _adc_start_conv(adc_port_t *port)
{
	MMIO8(port->baddr + ADCSRA_OFFSET) |= (1 << ADSC);
}

static inline status_t _adc_config_trigger(adc_port_t *port, adc_trig_t trigger)
{
	status_t ret = success;
	uint8_t trig_value = (uint8_t) trigger;
	ret |= (trig_value > 7) ? error_inval_arg : success;
	MMIO8(port->baddr + ADCSRB_OFFSET) |= ((trig_value & 0x07) << ADTS);
	MMIO8(port->baddr + ADCSRA_OFFSET) |= (1 << ADATE);
	return ret;
}

static inline status_t _adc_config_resolution(adc_port_t *port, uint8_t resolution)
{
	status_t ret = success;
	if(resolution == 8)
		MMIO8(port->baddr + ADMUX_OFFSET) = (1 << ADLAR);
	else if(resolution != 10)
		ret = error_inval_arg;
	return ret;
}

static inline status_t _adc_config_vref(adc_port_t *port, adc_ref_t vref)
{
	status_t ret = success;
	uint8_t value = 0;
	switch(vref)
	{
		case ref_ext:
			value = 0;
			break;
		case ref_avcc:
			value = 1;
			break;
		case ref_1_1:
			value = 3;
			break;
		default:
			ret = error_inval_arg;
	}
	if(ret == success)
		MMIO8(port->baddr + ADMUX_OFFSET) |= (value << REFS);
	return ret;
}

status_t adc_setup(adc_port_t *port)
{
	status_t ret = success;
	assert(port);
	ret |= platform_clk_en(port->clk_id);
	_adc_enable(port);
	ret |= _adc_set_prescaler(port);
	if(port->adc_handler)
	{
		ret |= link_interrupt(arch, port->adc_irq, port->adc_handler);
		ret |= adc_int_en(port);
	}
	return ret;
}

status_t adc_shutdown(adc_port_t *port)
{
	status_t ret = success;
	assert(port);
	ret |= adc_int_dis(port);
	_adc_disable(port);
	ret |= platform_clk_dis(port->clk_id);
	return ret;
}

bool adc_busy(adc_port_t *port)
{
	bool ret;
	assert(port);
	if(MMIO8(port->baddr + ADCSRA_OFFSET) & (1 << ADIE))
		ret = (MMIO8(port->baddr + ADCSRA_OFFSET) & (1 << ADSC)) ? true : false;
	else
		ret = (MMIO8(port->baddr + ADCSRA_OFFSET) & (1 << ADIF)) ? false : true;
	return ret;
}

status_t adc_int_en(adc_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + ADCSRA_OFFSET) |= (1 << ADIE);
	return success;
}

status_t adc_int_dis(adc_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + ADCSRA_OFFSET) &= ~(1 << ADIE);
	return success;
}

status_t adc_config_pin(adc_port_t *port, uint8_t pin, adc_trig_t trigger, uint8_t resolution, adc_ref_t vref)
{
	status_t ret = success;
	assert(port);
	if(pin > N_ADC_PINS)
		return error_inval_arg;
	ret |= _adc_config_vref(port, vref);
	ret |= _adc_config_resolution(port, resolution);
	ret |= _adc_config_trigger(port, trigger);
	MMIO8(port->baddr + ADMUX_OFFSET) |= (pin << MUX);
	return ret;
}

status_t adc_read(adc_port_t *port, uint16_t *adc_val)
{
	status_t ret = success;
	uint16_t temp;
	assert(port);
	assert(adc_val);
	if(MMIO8(port->baddr + ADMUX_OFFSET) & (1 << ADLAR))
	{
		*adc_val = MMIO8(port->baddr + ADCH_OFFSET);
	}
	else
	{
		*adc_val = MMIO8(port->baddr + ADCL_OFFSET);
		temp = MMIO8(port->baddr + ADCH_OFFSET);
		temp <<= 8;
		*adc_val |= temp;
	}
	MMIO8(port->baddr + ADMUX_OFFSET) &= ~((3 << REFS) | (1 << ADLAR));
	return ret;
}

status_t adc_temperature_convert(uint16_t raw_adc, float *temperature)
{
	status_t ret = success;
	unsigned long scaled_val = raw_adc * 1000;
	*temperature = ((float)(scaled_val - CTO) / CTK);
	return ret;
}
