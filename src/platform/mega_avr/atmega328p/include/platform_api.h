#pragma once
#include <stdint.h>
#include <platform.h>
#include <adc.h>

//===============< Platform APIs >===============//
void platform_early_setup();
void platform_setup();

//===============< Peripheral APIs >===============//

/*
 * ADC API:
 * Ref: Arc/src/include/adc.h for datatypes
 * Note: adc_read wrapper should use adc_refv, adc_res and
 *       adc_read together and should take necessary args
 */
void platform_adc_enable(adc_prescale_clk);
uint8_t platform_adc_refv(adc_refv);
uint8_t platform_adc_res(adc_res);
uint16_t platform_adc_read(adc_config *);
#if USE_ONBOARD_TEMPERATURE_SENSOR
uint16_t platform_core_temperature();
#endif
void platform_adc_ei();
void platform_adc_ci();
