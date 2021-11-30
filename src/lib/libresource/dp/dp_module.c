/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: dp_module.c
 * Description		: This file contains sources of device properties - module
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <resource.h>

extern dp_t *dev_prop;

#define DP_CREATE_MODULE_FUNCTION(mod)			\
	module_t *dp_get_##mod##_info(uint8_t id)	\
	{						\
		return dev_prop->mod[id];		\
	}

#if UART == 1
DP_CREATE_MODULE_FUNCTION(uart)
#endif

#if ADC == 1
DP_CREATE_MODULE_FUNCTION(adc)
#endif

#if TIMER == 1
DP_CREATE_MODULE_FUNCTION(timer)
#endif

#if SPI == 1
DP_CREATE_MODULE_FUNCTION(spi)
#endif

#if I2C == 1
DP_CREATE_MODULE_FUNCTION(i2c)
#endif

#if WDT == 1
DP_CREATE_MODULE_FUNCTION(wdt)
#endif
