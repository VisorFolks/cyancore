.global plat_panic_handler
.section .text.plat_panic_handler
.type plat_panic_handler, "function"
plat_panic_handler:
	SLEEP
	rjmp	plat_panic_handler
