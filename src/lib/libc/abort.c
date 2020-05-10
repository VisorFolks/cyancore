#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

extern void plat_panic_handler();

void abort(void)
{
	plat_panic_handler();
loop:
	goto loop;
}
