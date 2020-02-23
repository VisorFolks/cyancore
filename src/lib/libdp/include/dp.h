#pragma once

typedef enum int_trigger
{
	i_falling_edge,
	i_rising_edge,
	i_level
} int_trigger_t;

typedef struct cpu
{
	char name[10];
	uint16_t id;

} cpu_t;

typedef struct memory_info
{
	uintptr_t start;
	uintptr_t size;
} memory_t;

typedef struct module
{
	uint8_t id;
	uintptr_t baddr;
	uintptr_t stride;
	unsigned long clock;
	size_t interrupt_id;
	int_trigger_t interrupt_trigger;
} module_t;

typedef struct device_properties
{
	cpu_t core[N_CORES];
	uint8_t datawidth;
	size_t base_clock;
	memory_t memory;
#if UART0
	module_t uart0;
#endif
#if ADC0
	module_t adc0;
#endif
#if TIMER0
	module_t timer0;
#endif
#if TIMER1
	module_t timer1;
#endif
#if TIMER2
	module_t timer2;
#endif
#if SPI0
	module_t spi0;
#endif
#if I2C0
	module_t i2c0;
#endif
#if WDT0
	module_t wdt0;
#endif
} dp_t;

#define DP_PROTOTYPE_MODULE_FUNCTION(mod)	\
	module_t *dp_get_##mod##_info();

#if UART0
DP_PROTOTYPE_MODULE_FUNCTION(uart0)
#endif

#if ADC0
DP_PROTOTYPE_MODULE_FUNCTION(adc0)
#endif

#if TIMER0
DP_PROTOTYPE_MODULE_FUNCTION(timer0)
#endif

#if TIMER1
DP_PROTOTYPE_MODULE_FUNCTION(timer1)
#endif

#if TIMER2
DP_PROTOTYPE_MODULE_FUNCTION(timer2)
#endif

#if SPI0
DP_PROTOTYPE_MODULE_FUNCTION(spi0)
#endif

#if I2C0
DP_PROTOTYPE_MODULE_FUNCTION(i2c0)
#endif

#if WDT0
DP_PROTOTYPE_MODULE_FUNCTION(wdt0)
#endif
