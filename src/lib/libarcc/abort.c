#include <arc/stdlib.h>
#include <arc/stdio.h>

extern void plat_panic_handler();

void abort(void)
{
	aprintf("< x > Abort!");
	plat_panic_handler();
loop:
	goto loop;
}
