#include <plat_mem.h>
#include <asm.inc>

.global stack_end
.global stack_start
object stack
stack_end:
	.space STACK_SIZE, 0
stack_start:
