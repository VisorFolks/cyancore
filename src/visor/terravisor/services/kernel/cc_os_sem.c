/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_sem.c
 * Description		: CC OS Semaphore function definations
 * Primary Author	: Pranjal Chanda [pranjalchandaCC_OS_FALSE8@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <terravisor/cc_os/cc_os.h>

/*****************************************************
 *	GLOBAL/STATIC VARIABLE DECLARATIONS
 *****************************************************/

/*****************************************************
 *	GLOBAL EXTERNS
 *****************************************************/
extern cc_sched_ctrl_t g_sched_ctrl;
/*****************************************************
 *	STATIC FUNCTION DEFINATIONS
 *****************************************************/

/*****************************************************
 *	USER FUNCTION DEFINATIONS
 *****************************************************/

status_t cc_os_sem_create	(sem_t ** sem_ptr, size_t init_val)
{
#if CC_OS_DYNAMIC == CC_OS_FALSE
	CC_OS_ASSERT_IF_FALSE((*sem_ptr != CC_OS_NULL_PTR && (*sem_ptr)->sem_init == CC_OS_FALSE));
#else
	CC_OS_ASSERT_IF_FALSE(*sem_ptr == CC_OS_NULL_PTR);
	*sem_ptr = cc_os_malloc(sizeof(sem_t));
	if (*sem_ptr == CC_OS_NULL_PTR)
	{
		return error_memory_low;
	}
#endif
	(*sem_ptr)->sem_val = init_val;
	(*sem_ptr)->sem_init = CC_OS_TRUE;

	return success;
}
status_t cc_os_sem_take 	(sem_t * sem_ptr, size_t wait_ticks)
{
	CC_OS_ASSERT_IF_FALSE((sem_ptr != CC_OS_NULL_PTR && sem_ptr->sem_init != CC_OS_FALSE));

	if (sem_ptr->sem_val == CC_OS_FALSE)
	{
		if (wait_ticks == CC_OS_FALSE) 	/* ||_IS_ISR */
		{
			return error_os_sem_get;
		}
		else
		{	g_sched_ctrl.curr_task->wait_res.wait_on_resource = (uintptr_t) sem_ptr;
			cc_os_task_wait(wait_ticks);
		}
	}
	else
	{
		sem_ptr->sem_val--;
	}
	return success;
}
status_t cc_os_sem_give (sem_t * sem_ptr)
{
	CC_OS_ASSERT_IF_FALSE((sem_ptr != CC_OS_NULL_PTR && sem_ptr->sem_init != CC_OS_FALSE));

	sem_ptr->sem_val++;

	return success;
}
status_t cc_os_sem_delete (sem_t ** sem_ptr)
{
	CC_OS_ASSERT_IF_FALSE((*sem_ptr != CC_OS_NULL_PTR && (*sem_ptr)->sem_init != CC_OS_FALSE));

	(*sem_ptr)->sem_init = CC_OS_FALSE;

#if CC_OS_DYNAMIC == CC_OS_TRUE
	cc_os_free(*sem_ptr);
#endif

	return success;
}
status_t cc_os_sem_get_val 	(const sem_t * sem_ptr, size_t * val)
{
	CC_OS_ASSERT_IF_FALSE((sem_ptr != CC_OS_NULL_PTR && sem_ptr->sem_init != CC_OS_FALSE));
	CC_OS_ASSERT_IF_FALSE(val != CC_OS_NULL_PTR);

	*val = sem_ptr->sem_val;

	return success;
}
