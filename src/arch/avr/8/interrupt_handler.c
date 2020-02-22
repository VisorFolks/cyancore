#include <platform.h>
#include <arc/stddef.h>
#include <arc/assert.h>

extern void plat_panic_handler(void);
static void (* int_handler[N_IRQ])(void) = {NULL};

void register_interrupt_handler(unsigned int id, void (* handler)(void))
{
	assert((id > 0) && (id <= N_IRQ));
	id --;
	int_handler[id] = handler;
}

void interrupt_handler(unsigned char id)
{
	void (*handler)(void) = NULL;
	assert((id > 0) && (id <= N_IRQ));
	id --;
	handler = int_handler[id];
	assert(handler);
	handler();
}
