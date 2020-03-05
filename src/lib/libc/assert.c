#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <status.h>
#include <driver/console.h>

extern void plat_panic_handler();
void __assert(const char *func, unsigned int line)
{
	printf("< x > Assert: %s - %d\n", func, line);
	console_flush();
	plat_panic_handler();
}

void __assert_nodbg()
{
	console_flush();
	plat_panic_handler();
}
