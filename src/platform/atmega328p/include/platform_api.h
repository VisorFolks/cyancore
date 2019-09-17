#pragma once
#include <stdint.h>
#include <platform.h>

//===============< Peripheral APIs >===============//

/*
 * ADC API:
 * Ref: Arc/src/include/adc.h for datatypes
 * Note: adc_read wrapper should use adc_refv, adc_res and
 *       adc_read together and should take necessary args
 */
void platform_adc_setup(adc_prescale_clk);
void platform_adc_refv(adc_refv);
void platform_adc_res(adc_res);
uint16_t platform_adc_read(uint8_t);
#if USE_ONBOARD_TEMPERATURE_SENSOR
uint16_t platform_core_temperature();
#endif
void platform_adc_ei();
void platform_adc_ci();
