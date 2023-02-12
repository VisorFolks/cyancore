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
static const int init_val = 1;

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
	HELIOS_ASSERT_IF_FALSE(*mutex_ptr != HELIOS_NULL_PTR);
	HELIOS_ASSERT_IF_FALSE((*mutex_ptr)->mutex_init == false);

	/* Initialize values of the mutex struct */
	(*mutex_ptr)->lock_task = g_sched_ctrl.curr_task;
	(*mutex_ptr)->mutex_init = true;
	(*mutex_ptr)->mutex_val = init_val;
#else
	HELIOS_ASSERT_IF_FALSE(*mutex_ptr == HELIOS_NULL_PTR);
	*mutex_ptr = helios_malloc(sizeof(helios_mutex_t));
	if (*mutex_ptr == HELIOS_NULL_PTR)
	{
		HELIOS_ERR("Memory low for mutex creation");
		return error_memory_low;
	}
	else
	{
		/* Initialize values of the mutex struct */
		(*mutex_ptr)->lock_task = g_sched_ctrl.curr_task;
		(*mutex_ptr)->mutex_val = init_val;
		(*mutex_ptr)->mutex_init = true;
	}

#endif
	return success;
}

status_t helios_mutex_lock 	(helios_mutex_t * mutex_ptr, size_t wait_ticks)
{
	HELIOS_ASSERT_IF_FALSE(mutex_ptr != HELIOS_NULL_PTR);
	HELIOS_ASSERT_IF_FALSE(mutex_ptr->mutex_init != false);

	bool lock_flag = false;

	if (mutex_ptr->mutex_val != init_val)
	{
		if (wait_ticks == false) 	/* ||_IS_ISR */
		{
			HELIOS_ERR("Mutex already locked");
			return error_os_mutex_lock;
		}
		else
		{
			/* If not locked, check if another task has acquired the resource. */
			if (mutex_ptr->lock_task != g_sched_ctrl.curr_task) {
				g_sched_ctrl.curr_task->wait_res.wait_on_resource = (uintptr_t) mutex_ptr;
				helios_task_wait(wait_ticks);
			}
			else {
				/* If current task requests for lock again, allow locking recursively. */
				lock_flag = true;
			}
		}
	}
	else
	{
		/* If no mutex acquired yet, only let the current task acquire lock. */
		if (mutex_ptr->lock_task != g_sched_ctrl.curr_task) {
			HELIOS_ERR("Mutex initialized by another task");
			return error_os_mutex_lock;
		}
		else {
			lock_flag = true;
		}
	}

	if (lock_flag) {
		/* Decrement and lock the mutex */
		mutex_ptr->mutex_val--;
	}
	return success;
}

status_t helios_mutex_unlock (helios_mutex_t * mutex_ptr)
{
	HELIOS_ASSERT_IF_FALSE(mutex_ptr != HELIOS_NULL_PTR);
	HELIOS_ASSERT_IF_FALSE(mutex_ptr->mutex_init != false);

	if (mutex_ptr->lock_task != g_sched_ctrl.curr_task) {
		HELIOS_ERR("Mutex locked by another task");
		return error_os_mutex_unlock;
	}
	else {
		/* Unlock mutex only if current task requests it. */
		mutex_ptr->mutex_val++;
	}
	return success;
}

status_t helios_mutex_delete (helios_mutex_t ** mutex_ptr)
{
	HELIOS_ASSERT_IF_FALSE(*mutex_ptr != HELIOS_NULL_PTR);
	HELIOS_ASSERT_IF_FALSE((*mutex_ptr)->mutex_init != false);

	(*mutex_ptr)->mutex_init = false;

#if HELIOS_DYNAMIC == true
	helios_free(*mutex_ptr);
#endif

	return success;
}

status_t helios_mutex_get_val 	(const helios_mutex_t * mutex_ptr, int * val)
{
	HELIOS_ASSERT_IF_FALSE(mutex_ptr != HELIOS_NULL_PTR);
	HELIOS_ASSERT_IF_FALSE(mutex_ptr->mutex_init != false);
	HELIOS_ASSERT_IF_FALSE(val != HELIOS_NULL_PTR);

	*val = mutex_ptr->mutex_val;

	return success;
}
