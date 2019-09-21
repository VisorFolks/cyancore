#pragma once
#include <stdint.h>

typedef enum adc_prescale_clk
{
	div_nill, div2, div4, div8, div16, div32, div64, div128
} adc_prescale_clk;

typedef enum adc_res
{
	bit8, bit10
} adc_res;

typedef enum adc_refv
{
	i1_1, ivref, aref
} adc_refv;

typedef struct adc_config
{
	uint8_t a_pin;
	uint8_t res;
	uint8_t refv;
} adc_config;

void adc_enable(adc_prescale_clk);
void adc_setup(adc_config *, adc_refv, adc_res);
uint16_t adc_read(adc_config *);
