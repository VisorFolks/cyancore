#pragma once
#include <platform.h>
#include <stdint.h>

typedef enum arch
{
	no_arch, avr, armv7, armv8, riscv, x86
} arch;

typedef struct shi
{
	arch architecture;
	uint8_t datawidth;
//--- UART
#if UART == 1
	uint8_t n_uart;
	unsigned int uart_base_addr[N_UART_MODULES];
#endif
//--- TIMER
//--- PWM
//--- ADC
#if ADC == 1
	uint8_t n_adc;
	unsigned int adc_base_addr[N_ADC_MODULES];
	unsigned int adc_interrupt_id[N_ADC_MODULES];
#endif
//--- SPI
//--- I2C

} shi;

#define UPDATE_SHI(X)		system_hardware_info = &(X)
#define FETCH_SHI(X)		(X)=system_hardware_info
#define SYSTEM_HARDWARE_INFO	shi * system_hardware_info
