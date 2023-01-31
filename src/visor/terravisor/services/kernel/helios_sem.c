/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: helios_sem.c
 * Description		: CC OS Semaphore function definations
 * Primary Author	: Pranjal Chanda [pranjalchandaHELIOS_FALSE8@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <terravisor/helios/helios.h>

/*****************************************************
 *	GLOBAL/STATIC VARIABLE DECLARATIONS
 *****************************************************/

/*****************************************************
 *	GLOBAL EXTERNS
 *****************************************************/
extern helios_sched_ctrl_t g_sched_ctrl;
/*****************************************************
 *	STATIC FUNCTION DEFINATIONS
 *****************************************************/

/*****************************************************
 *	USER FUNCTION DEFINATIONS
 *****************************************************/

status_t helios_sem_create	(sem_t ** sem_ptr, size_t init_val)
{
#if HELIOS_DYNAMIC == false
	HELIOS_ASSERT_IF_FALSE((*sem_ptr != HELIOS_NULL_PTR && (*sem_ptr)->sem_init == false));
#else
	HELIOS_ASSERT_IF_FALSE(*sem_ptr == HELIOS_NULL_PTR);
	*sem_ptr = helios_malloc(sizeof(sem_t));
	if (*sem_ptr == HELIOS_NULL_PTR)
	{
		return error_memory_low;
	}
#endif
	(*sem_ptr)->sem_val = init_val;
	(*sem_ptr)->sem_init = true;

	return success;
}
status_t helios_sem_take 	(sem_t * sem_ptr, size_t wait_ticks)
{
	HELIOS_ASSERT_IF_FALSE((sem_ptr != HELIOS_NULL_PTR && sem_ptr->sem_init != false));

	if (sem_ptr->sem_val == false)
	{
		if (wait_ticks == false) 	/* ||_IS_ISR */
		{
			return error_os_sem_get;
		}
		else
		{	g_sched_ctrl.curr_task->wait_res.wait_on_resource = (uintptr_t) sem_ptr;
			helios_task_wait(wait_ticks);
		}
	}
	else
	{
		sem_ptr->sem_val--;
	}
	return success;
}
status_t helios_sem_give (sem_t * sem_ptr)
{
	HELIOS_ASSERT_IF_FALSE((sem_ptr != HELIOS_NULL_PTR && sem_ptr->sem_init != false));

	sem_ptr->sem_val++;

	return success;
}
status_t helios_sem_delete (sem_t ** sem_ptr)
{
	HELIOS_ASSERT_IF_FALSE((*sem_ptr != HELIOS_NULL_PTR && (*sem_ptr)->sem_init != false));

	(*sem_ptr)->sem_init = false;

#if HELIOS_DYNAMIC == true
	helios_free(*sem_ptr);
#endif

	return success;
}
status_t helios_sem_get_val 	(const sem_t * sem_ptr, size_t * val)
{
	HELIOS_ASSERT_IF_FALSE((sem_ptr != HELIOS_NULL_PTR && sem_ptr->sem_init != false));
	HELIOS_ASSERT_IF_FALSE(val != HELIOS_NULL_PTR);

	*val = sem_ptr->sem_val;

	return success;
}
