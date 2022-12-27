/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_idle.c
 * Description		: CC OS IDLE Task definitions
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <terravisor/cc_os/cc_os.h>

/*****************************************************
 *	STATIC FUNCTION DECLARATION
 *****************************************************/
/**
 * @brief	This function cleans up the terminated task form the TCB list
 *
 * @param  ptr[in]		Pointer to the TCB being cleaned
 * @return cc_sched_tcb_t *	Pointer to the next TCB
 */
static cc_sched_tcb_t * __free_terminated_task(cc_sched_tcb_t * ptr)
{
	cc_sched_tcb_t * next_ptr = ptr->ready_link.next;
	if (ptr->ready_link.next->task_status == cc_sched_task_status_exit)
	{
		ptr->ready_link.prev->ready_link.next = ptr->ready_link.next;
		ptr->ready_link.next->ready_link.prev = ptr->ready_link.prev;

#if CC_OS_DYNAMIC == CC_OS_FALSE
		ptr->ready_link.next = CC_OS_NULL_PTR;
		ptr->ready_link.prev = CC_OS_NULL_PTR;
#else
		cc_os_free(ptr);
#endif
	}

	return next_ptr;
}

/*****************************************************
 *	USER FUNCTION DEFINATION
 *****************************************************/
void _cc_os_idle_task_fn(os_args args)
{
	cc_sched_ctrl_t * sched_ctrl = (cc_sched_ctrl_t *) args;
	static cc_sched_tcb_t * ptr = CC_OS_NULL_PTR;
	ptr = sched_ctrl->ready_list_head;
	while (CC_OS_TRUE)
	{
		/* Clean up task if terminated */
		ptr = __free_terminated_task(ptr);

#if ccosconfig_CC_OS_POWER_SAVE_EN
		/* Power Save code */

#endif
		/* Yield for next available task */
		cc_os_task_yield();
	}
}
