#include <stddef.h>
#include <assert.h>
#include <arch.h>

void plat_panic_handler();

static void (* int_handler[N_IRQ])(void) = {[0 ... N_IRQ-1] = plat_panic_handler};

void arch_register_interrupt_handler(unsigned int id, void (* handler)(void))
{
	assert((id > 0) && (id <= N_IRQ));
	id --;
	int_handler[id] = handler;
}

void interrupt_handler(unsigned char id)
{
	void (*handler)(void);
	assert((id > 0) && (id <= N_IRQ));
	id --;
	handler = int_handler[id];
	assert(handler);
	handler();
	return;
}
