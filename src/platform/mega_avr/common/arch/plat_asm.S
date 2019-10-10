.global plat_panic_handler
.section .text
.type plat_panic_handler, "function"
plat_panic_handler:
	SLEEP
	rjmp	plat_panic_handler
