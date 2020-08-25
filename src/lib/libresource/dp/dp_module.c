#include <stdint.h>
#include <status.h>
#include <resource.h>

extern dp_t *dev_prop;

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
