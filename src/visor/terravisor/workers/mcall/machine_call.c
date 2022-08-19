/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019-2022, Cyancore Team
 *
 * File Name		: machine_call.c
 * Description		: This file contains sources of machine call handler
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <syslog.h>
#include <machine_call.h>
#include <platform.h>
#include <resource.h>

/* mcall Table start and end  defined in linker script mcall.ld.sx */
extern mcall_t _ecall_table_start;
extern mcall_t _ecall_table_end;

typedef void (*mcb_t)(call_arg_t, call_arg_t, call_arg_t, mret_t *);
static mcb_t get_callback_from_table(mcall_t *start, mcall_t *end, mcall_id_t id)
{
	mcall_t *ptr = start;
	while(ptr < end)
	{
		if(ptr->id == id)
			return (ptr->callback != NULL) ? ptr->callback : NULL;
		ptr++;
	}
	return (mcb_t) 0;
}

void machine_call(mcall_id_t id, call_arg_t a0, call_arg_t a1, call_arg_t a2, mret_t *ret)
{
	sysdbg4("MCall: id=%p, a0=%p, a1=%p, a2=%p\n", id, a0, a1, a2);
	/* Callback function pointer */
	mcb_t cb;

	/* Assign "ret" parameters to default error case,
	 * on execution of the call, the ret will updated.
	 */
	ret->p = (uintptr_t) 0;
	ret->size = 0;
	ret->status = error_mcall_code_inval;

	cb = get_callback_from_table(&_ecall_table_start, &_ecall_table_end, id);
	if(cb != 0)
		cb(a0, a1, a2, ret);
	return;
}
