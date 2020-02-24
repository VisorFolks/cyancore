#include <arc/assert.h>
#include <arc/stdio.h>
#include <status.h>
#include <driver/console.h>

extern void plat_panic_handler();
void __assert(const char *file, unsigned int line, const char *assertion)
{
	aprintf("< x > Assert: %s - %d - %s\n", file, line, assertion);
	console_flush();
	plat_panic_handler();
}
