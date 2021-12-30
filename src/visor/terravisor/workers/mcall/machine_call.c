/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: machine_call.c
 * Description		: This file contains sources of machine call handler
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <stddef.h>
#include <status.h>
#include <machine_call.h>
#include <platform.h>
#include <resource.h>

/* mcall Table start and end  defined in linker script mcall.ld.sx */
extern mcall_t _mcall_table_start;
extern mcall_t _mcall_table_end;

void machine_call(mcall_id_t id, unsigned int a0, unsigned int a1, unsigned int a2, mret_t *ret)
{
	/* mcall Table pointer */
	mcall_t *ptr;

	/* Assign "ret" parameters to default error case,
	 * on execution of the call, the ret will updated.
	 */
	ret->p = (uintptr_t) NULL;
	ret->size = 0;
	ret->status = error_mcall_code_inval;

	/* Assign the pointer to start of table */
	ptr = &_mcall_table_start;

	/* Run through the table till the end */
	while(ptr < & _mcall_table_end)
	{
		/* Check if the mcall ID matches */
		if(ptr->id == id)
		{
			/* Execute the callback function and update the "ret" */
			*ret = ptr->callback(a0, a1, a2);
			/* Stop parsing the table and return */
			break;
		}
		/* Increament location pointer */
		ptr++;
	}
	return;
}
