.section .platvectors, "ax"
PlatVectors:
.org 0x00
#if USE_INT0
	jmp	int0
#else
	jmp	arch_panic_handler
#endif
#if USE_INT1
	jmp	int1
#else
	jmp	arch_panic_handler
#endif
#if USE_PCINT0
	jmp	pcint0
#else
	jmp	arch_panic_handler
#endif
#if USE_PCINT1
	jmp	pcint1
#else
	jmp	arch_panic_handler
#endif
#if USE_PCINT2
	jmp	pcint2
#else
	jmp	arch_panic_handler
#endif
#if USE_WDR
	jmp	wdt
#else
	jmp	arch_panic_handler
#endif
#if USE_T2CMPA
	jmp	t2cmpa
#else
	jmp	arch_panic_handler
#endif
#if USE_T2CMPB
	jmp	t2cmpb
#else
	jmp	arch_panic_handler
#endif
#if USE_T2OVF
	jmp	t2ovf
#else
	jmp	arch_panic_handler
#endif
#if USE_T2CAPT
	jmp	t1capt
#else
	jmp	arch_panic_handler
#endif
#if USE_T1CMPA
	jmp	t1cmpa
#else
	jmp	arch_panic_handler
#endif
#if USE_T1CMPB
	jmp	t1cmpb
#else
	jmp	arch_panic_handler
#endif
#if USE_T1OVF
	jmp	t1ovf
#else
	jmp	arch_panic_handler
#endif
#if USE_T0CMPA
	jmp	t0cmpa
#else
	jmp	arch_panic_handler
#endif
#if USE_T0CMPB
	jmp	t0cmpb
#else
	jmp	arch_panic_handler
#endif
#if USE_T0OVF
	jmp	t0ovf
#else
	jmp	arch_panic_handler
#endif
#if USE_SPI
	jmp	spi
#else
	jmp	arch_panic_handler
#endif
#if USE_UART_RX
	jmp	uart_rx
#else
	jmp	arch_panic_handler
#endif
#if USE_UART_UDRE
	jmp	uart_udre
#else
	jmp	arch_panic_handler
#endif
#if USE_UART_TX
	jmp	uart_tx
#else
	jmp	arch_panic_handler
#endif
#if USE_ADC
	jmp	adc
#else
	jmp	arch_panic_handler
#endif
#if USE_EE_READY
	jmp	ee_ready
#else
	jmp	arch_panic_handler
#endif
#if USE_A_COMP
	jmp	a_comp
#else
	jmp	arch_panic_handler
#endif
#if USE_TWI
	jmp	twi
#else
	jmp	arch_panic_handler
#endif
#if USE_SMP_READY
	jmp	smp_ready
#else
	jmp	arch_panic_handler
#endif
