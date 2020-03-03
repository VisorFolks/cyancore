#include <stdint.h>
#include <stdio.h>
#include <platform.h>
#include <status.h>
#include <dp.h>

dp_t *dev_prop;

status_t dp_init(dp_t *plat_dev_prop)
{
	status_t ret;

	if(plat_dev_prop)
	{
		dev_prop = plat_dev_prop;
		ret = success;
	}
	else
		ret = error_inval_arg;
	return ret;
}

cpu_t *dp_get_cpu_info(uint8_t id)
{
	return &dev_prop->core[id];
}

uint8_t dp_get_datawidth()
{
	return dev_prop->datawidth;
}

size_t dp_get_base_clock()
{
	return dev_prop->base_clock;
}

memory_t *dp_get_memory_info()
{
	return &dev_prop->memory;
}

#define DP_CREATE_MODULE_FUNCTION(mod)		\
	module_t *dp_get_##mod##_info()		\
	{					\
		return &dev_prop->mod;	\
	}

#if UART0
DP_CREATE_MODULE_FUNCTION(uart0)
#endif

#if ADC0
DP_CREATE_MODULE_FUNCTION(adc0)
#endif

#if TIMER0
DP_CREATE_MODULE_FUNCTION(timer0)
#endif

#if TIMER1
DP_CREATE_MODULE_FUNCTION(timer1)
#endif

#if TIMER2
DP_CREATE_MODULE_FUNCTION(timer2)
#endif

#if SPI0
DP_CREATE_MODULE_FUNCTION(spi0)
#endif

#if I2C0
DP_CREATE_MODULE_FUNCTION(i2c0)
#endif

#if WDT0
DP_CREATE_MODULE_FUNCTION(wdt0)
#endif
