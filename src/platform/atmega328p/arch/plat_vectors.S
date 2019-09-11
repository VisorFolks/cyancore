.section .platvectors, "ax"
PlatVectors:
.org 0x00
#if USE_INT0
	rjmp	int0
#else
	rjmp	arch_panic_handler
#endif
#if USE_INT1
	rjmp	int1
#else
	rjmp	arch_panic_handler
#endif
#if USE_PCINT0
	rjmp	pcint0
#else
	rjmp	arch_panic_handler
#endif
#if USE_PCINT1
	rjmp	pcint1
#else
	rjmp	arch_panic_handler
#endif
#if USE_PCINT2
	rjmp	pcint2
#else
	rjmp	arch_panic_handler
#endif
#if USE_WDR
	rjmp	wdt
#else
	rjmp	arch_panic_handler
#endif
#if USE_T2CMPA
	rjmp	t2cmpa
#else
	rjmp	arch_panic_handler
#endif
#if USE_T2CMPB
	rjmp	t2cmpb
#else
	rjmp	arch_panic_handler
#endif
#if USE_T2OVF
	rjmp	t2ovf
#else
	rjmp	arch_panic_handler
#endif
#if USE_T2CAPT
	rjmp	t1capt
#else
	rjmp	arch_panic_handler
#endif
#if USE_T1CMPA
	rjmp	t1cmpa
#else
	rjmp	arch_panic_handler
#endif
#if USE_T1CMPB
	rjmp	t1cmpb
#else
	rjmp	arch_panic_handler
#endif
#if USE_T1OVF
	rjmp	t1ovf
#else
	rjmp	arch_panic_handler
#endif
#if USE_T0CMPA
	rjmp	t0cmpa
#else
	rjmp	arch_panic_handler
#endif
#if USE_T0CMPB
	rjmp	t0cmpb
#else
	rjmp	arch_panic_handler
#endif
#if USE_T0OVF
	rjmp	t0ovf
#else
	rjmp	arch_panic_handler
#endif
#if USE_SPI
	rjmp	spi
#else
	rjmp	arch_panic_handler
#endif
#if USE_UART_RX
	rjmp	uart_rx
#else
	rjmp	arch_panic_handler
#endif
#if USE_UART_UDRE
	rjmp	uart_udre
#else
	rjmp	arch_panic_handler
#endif
#if USE_UART_TX
	rjmp	uart_tx
#else
	rjmp	arch_panic_handler
#endif
#if USE_ADC
	rjmp	adc
#else
	rjmp	arch_panic_handler
#endif
#if USE_EE_READY
	rjmp	ee_ready
#else
	rjmp	arch_panic_handler
#endif
#if USE_A_COMP
	rjmp	a_comp
#else
	rjmp	arch_panic_handler
#endif
#if USE_TWI
	rjmp	twi
#else
	rjmp	arch_panic_handler
#endif
#if USE_SMP_READY
	rjmp	smp_ready
#else
	rjmp	arch_panic_handler
#endif
