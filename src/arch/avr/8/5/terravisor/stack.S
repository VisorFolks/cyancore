#include <plat_mem.h>

.global stack_end
.global stack_start
.type stack_end, "object"
.section .stack
stack_end:
	.space STACK_SIZE, 0
stack_start:
