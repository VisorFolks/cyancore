/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: supervisory_call.c
 * Description		: This file contains sources of supervisory call handler
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <status.h>
#include <supervisor_call.h>
#include <platform.h>
#include <resource.h>

/* mcall Table start and end  defined in linker script mcall.ld.sx */
extern scall_t _scall_table_start;
extern scall_t _scall_table_end;

void super_call(scall_id_t id, call_arg_t a0, call_arg_t a1, call_arg_t a2, sret_t *ret)
{
	/* mcall Table pointer */
	scall_t *ptr;

	/* Assign "ret" parameters to default error case,
	 * on execution of the call, the ret will updated.
	 */
	ret->p = (uintptr_t) NULL;
	ret->size = 0;
	ret->status = error_scall_code_inval;

	/* Assign the pointer to start of table */
	ptr = &_scall_table_start;

	/* Run through the table till the end */
	while(ptr <= & _scall_table_end)
	{
		/* Check if the mcall ID matches */
		if(ptr->id == id)
		{
			/* Execute the callback function and update the "ret" */
			if (ptr->callback != NULL)
			{
				*ret = ptr->callback(a0, a1, a2);
			}
			/* Stop parsing the table and return */
			break;
		}
		/* Increament location pointer */
		ptr++;
	}
	return;
}
