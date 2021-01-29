.global plat_panic_handler
.section .text.plat_panic_handler
.type plat_panic_handler, "function"
plat_panic_handler:
	call	arch_wfi
	rjmp	plat_panic_handler
