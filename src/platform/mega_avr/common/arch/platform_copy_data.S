#include <plat_mem.h>

.global platform_copy_data
.section .text.platform_copy_data, "ax", @progbits
.type platform_copy_data, "function"
platform_copy_data:
	ldi	r17, hi8((V_DMEM_START + _data_size))
	ldi	r26, lo8(V_DMEM_START)
	ldi	r27, hi8(V_DMEM_START)
	ldi	r30, lo8(_data_start)
	ldi	r31, hi8(_data_start)
	rjmp	1f
2:
	lpm	r0, Z+
	st	X+, r0
1:
	cpi	r26, lo8((V_DMEM_START + _data_size))
	cpc	r27, r17
	brne	2b
	ldi	r24, 0
	ldi	r25, 0
	ret
