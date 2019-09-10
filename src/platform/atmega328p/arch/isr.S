#define SREG	0x3f

.global plat_panic_handler
.section .text
.type plat_panic_handler, "function"
plat_panic_handler:
	SLEEP
	rjmp	plat_panic_handler

.macro CONTEXT_SAVE
	push	r1
	push	r0
	in	r0, SREG
	push	r0
	push	r2
	push	r3
	push	r4
	push	r5
	push	r6
	push	r7
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15
	push	r16
	push	r17
	push	r18
	push	r19
	push	r20
	push	r21
	push	r22
	push	r23
	push	r24
	push	r25
	push	r26
	push	r27
	push	r28
	push	r29
	push	r30
	push	r31
.endm

.macro CONTEXT_RESTORE
	pop	r31
	pop	r30
	pop	r29
	pop	r28
	pop	r27
	pop	r26
	pop	r25
	pop	r24
	pop	r23
	pop	r22
	pop	r21
	pop	r20
	pop	r19
	pop	r18
	pop	r17
	pop	r16
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	r7
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	pop	r2
	pop	r0
	out	SREG, r0
	pop	r0
	pop	r1
	reti
.endm

#if USE_INT0
.global int0
.section .text
.type int0, "function"
int0:
	CONTEXT_SAVE
	jmp	int0_handler
	CONTEXT_RESTORE
#endif

#if USE_INT1
.global int1
.section .text
.type int1, "function"
int1:
	CONTEXT_SAVE
	jmp	int1_handler
	CONTEXT_RESTORE
#endif

#if USE_PCINT0
.global pcint0
.section .text
.type pcint0, "function"
pcint0:
	CONTEXT_SAVE
	jmp	pcint0_handler
	CONTEXT_RESTORE
#endif

#if USE_PCINT1
.global pcint1
.section .text
.type pcint1, "function"
pcint1:
	CONTEXT_SAVE
	jmp	pcint1_handler
	CONTEXT_RESTORE
#endif

#if USE_PCINT2
.global pcint2
.section .text
.type pcint2, "function"
pcint2:
	CONTEXT_SAVE
	jmp	pcint2_handler
	CONTEXT_RESTORE
#endif

#if USE_WDR
.global wdr
.section .text
.type wdr, "function"
wdr:
	CONTEXT_SAVE
	jmp	wdr_handler
	CONTEXT_RESTORE
#endif

#if USE_T2CMPA
.global t2cmpa
.section .text
.type t2cmpa, "function"
t2cmpa:
	CONTEXT_SAVE
	jmp	t2cmpa_handler
	CONTEXT_RESTORE
#endif
#if USE_T2CMPB
.global t2cmpb
.section .text
.type t2cmpb, "function"
t2cmpb:
	CONTEXT_SAVE
	jmp	t2cmpb_handler
	CONTEXT_RESTORE
#endif

#if USE_T2OVF
.global t2ovf
.section .text
.type t2ovf, "function"
t2ovf:
	CONTEXT_SAVE
	jmp	t2ovf_handler
	CONTEXT_RESTORE
#endif

#if USE_T2CAPT
.global t2capt
.section .text
.type t2capt, "function"
t2capt:
	CONTEXT_SAVE
	jmp	t2capt_handler
	CONTEXT_RESTORE
#endif

#if USE_T1CMPA
.global t1cmpa
.section .text
.type t1cmpa, "function"
t1cmpa:
	CONTEXT_SAVE
	jmp	t1cmpa_handler
	CONTEXT_RESTORE
#endif

#if USE_T1CMPB
.global t1cmpb
.section .text
.type t1cmpb, "function"
t1cmpb:
	CONTEXT_SAVE
	jmp	t1cmpb_handler
	CONTEXT_RESTORE
#endif

#if USE_T1OVF
.global t1ovf
.section .text
.type t1ovf, "function"
t1ovf:
	CONTEXT_SAVE
	jmp	t1ovf_handler
	CONTEXT_RESTORE
#endif

#if USE_T0CMPA
.global t0cmpa
.section .text
.type t0cmpa, "function"
t0cmpa:
	CONTEXT_SAVE
	jmp	t0cmpa_handler
	CONTEXT_RESTORE
#endif

#if USE_T0CMPB
.global t0cmpb
.section .text
.type t0cmpb, "function"
t0cmpb:
	CONTEXT_SAVE
	jmp	t0cmpb_handler
	CONTEXT_RESTORE
#endif

#if USE_T0OVF
.global t0ovf
.section .text
.type t0ovf, "function"
t0ovf:
	CONTEXT_SAVE
	jmp	t0ovf_handler
	CONTEXT_RESTORE
#endif

#if USE_SPI
.global spi
.section .text
.type spi, "function"
spi:
	CONTEXT_SAVE
	jmp	spi_handler
	CONTEXT_RESTORE
#endif

#if USE_UART_RX
.global uart_rx
.section .text
.type uart_rx, "function"
uart_rx:
	CONTEXT_SAVE
	jmp	uart_rx_handler
	CONTEXT_RESTORE
#endif

#if USE_UART_UDRE
.global uart_udre
.section .text
.type uart_udre, "function"
uart_udre:
	CONTEXT_SAVE
	jmp	uart_udre_handler
	CONTEXT_RESTORE
#endif

#if USE_UART_TX
.global uart_tx
.section .text
.type uart_tx, "function"
uart_tx:
	CONTEXT_SAVE
	jmp	uart_tx_handler
	CONTEXT_RESTORE
#endif

#if USE_ADC
.global adc
.section .text
.type adc, "function"
adc:
	CONTEXT_SAVE
	jmp	adc_handler
	CONTEXT_RESTORE
#endif

#if USE_EE_READY
.global ee_ready
.section .text
.type ee_ready, "function"
ee_ready:
	CONTEXT_SAVE
	jmp	ee_ready_handler
	CONTEXT_RESTORE
#endif

#if USE_A_COMP
.global a_comp
.section .text
.type a_comp, "function"
a_comp:
	CONTEXT_SAVE
	jmp	a_comp_handler
	CONTEXT_RESTORE
#endif

#if USE_TWI
.global twi
.section .text
.type twi, "function"
twi:
	CONTEXT_SAVE
	jmp	twi_handler
	CONTEXT_RESTORE
#endif

#if USE_SMP_READY
.global smp_ready
.section .text
.type smp_ready, "function"
smp_ready:
	CONTEXT_SAVE
	jmp	smp_ready_handler
	CONTEXT_RESTORE
#endif
