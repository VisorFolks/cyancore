#include <assert.h>

extern void arch_panic_handler();
static void (* int_handler[N_IRQ])(void) = {arch_panic_handler};

void register_interrupt_handler(unsigned int id, void (* handler)(void))
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
}
