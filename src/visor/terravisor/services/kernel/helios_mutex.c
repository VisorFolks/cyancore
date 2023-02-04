/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: helios_mutex.c
 * Description		: HELIOS mutex function definitions
 * Primary Author	: Dibyajyoti Samal [dibyajyoti.samal@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <terravisor/helios/helios.h>

/*****************************************************
 *	GLOBAL/STATIC VARIABLE DECLARATIONS
 *****************************************************/
static const size_t init_val = 0;

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

status_t helios_mutex_create	(helios_mutex_t ** mutex_ptr)
{
#if HELIOS_DYNAMIC == false
	HELIOS_ASSERT_IF_FALSE((*mutex_ptr != HELIOS_NULL_PTR && (*mutex_ptr)->mutex_init == false));

	(*mutex_ptr)->lock_task = g_sched_ctrl.curr_task;
	(*mutex_ptr)->mutex_init = true;
	(*mutex_ptr)->mutex_val = init_val;
#else
	HELIOS_ASSERT_IF_FALSE(*mutex_ptr == HELIOS_NULL_PTR);
	*mutex_ptr = helios_malloc(sizeof(helios_mutex_t));
	if (*mutex_ptr == HELIOS_NULL_PTR)
	{
		HELIOS_ERR("Memory low for mutex create");
		return error_memory_low;
	}
	else
	{
		(*mutex_ptr)->lock_task = g_sched_ctrl.curr_task;
		(*mutex_ptr)->mutex_val = init_val;
		(*mutex_ptr)->mutex_init = true;
	}

#endif
	return success;
}

status_t helios_mutex_lock 	(helios_mutex_t * mutex_ptr, size_t wait_ticks)
{
	HELIOS_ASSERT_IF_FALSE((mutex_ptr != HELIOS_NULL_PTR && mutex_ptr->mutex_init != false));

	if (mutex_ptr->mutex_val == false)
	{
		if (wait_ticks == false) 	/* ||_IS_ISR */
		{
			HELIOS_ERR("Mutex already locked");
			return error_os_mutex_lock;
		}
		else
		{
			if (mutex_ptr->lock_task != g_sched_ctrl.curr_task) {
				g_sched_ctrl.curr_task->wait_res.wait_on_resource = (uintptr_t) mutex_ptr;
				helios_task_wait(wait_ticks);
			}
			else {
				mutex_ptr->mutex_val--; /* TODO: Check signage in case of mutex recursion */
			}
		}
	}
	else
	{
		mutex_ptr->mutex_val--;
	}
	return success;
}

status_t helios_mutex_unlock (helios_mutex_t * mutex_ptr)
{
	HELIOS_ASSERT_IF_FALSE((mutex_ptr != HELIOS_NULL_PTR && mutex_ptr->mutex_init != false));

	if (mutex_ptr->lock_task != g_sched_ctrl.curr_task) {
		HELIOS_ERR("Mutex locked by another task");
		return error_os_mutex_unlock;
	}
	else {
		mutex_ptr->mutex_val++;
	}
	return success;
}

status_t helios_mutex_delete (helios_mutex_t ** mutex_ptr)
{
	HELIOS_ASSERT_IF_FALSE((*mutex_ptr != HELIOS_NULL_PTR && (*mutex_ptr)->mutex_init != false));

	(*mutex_ptr)->mutex_init = false;

#if HELIOS_DYNAMIC == true
	helios_free(*mutex_ptr);
#endif

	return success;
}

status_t helios_mutex_get_val 	(const helios_mutex_t * mutex_ptr, size_t * val)
{
	HELIOS_ASSERT_IF_FALSE((mutex_ptr != HELIOS_NULL_PTR && mutex_ptr->mutex_init != false));
	HELIOS_ASSERT_IF_FALSE(val != HELIOS_NULL_PTR);

	*val = mutex_ptr->mutex_val;

	return success;
}
