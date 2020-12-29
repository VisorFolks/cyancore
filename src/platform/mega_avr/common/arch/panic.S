#include <asm.inc>

function plat_panic_handler
	call	arch_wfi
	rjmp	plat_panic_handler
