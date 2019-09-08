.global arch_panic_handler
.section .text
.type arch_panic_handler, "function"
arch_panic_handler:
	SLEEP
	rjmp	arch_panic_handler

