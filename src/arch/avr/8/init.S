/*
 * ============================================================
 * File		: init.c (AVR-8)
 * Author	: Akash Kollipara
 * ============================================================
 */

.global init
.section .text
.type init, "function"

init:
	ldi	r26, _stack_start
	out	0x3d, r26
	rjmp	bss_flush
	rjmp	arc
end:
	rjmp	end

bss_flush:
	ldi	r26, _bss_start
	ldi	r28, _bss_end
	cp	r26, r28
	brge	flush_end
	ldi	r16, 0x00
flush_loop:
	st	X+, r16
	cp	r28, r26
	brge	flush_loop
flush_end:
	ret

