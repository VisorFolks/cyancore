/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_task_idle.c
 * Description		: CC OS IDLE Task definitions
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <terravisor/cc_os/cc_os.h>
#include <arch.h>

/*****************************************************
 *	EXTERN FUNCTION DECLARATION
 *****************************************************/
extern status_t _cc_sched_node_detach(cc_sched_tcb_t *node_ptr, uint8_t link_type);

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
		_cc_sched_node_detach(ptr, false);

#if CC_OS_DYNAMIC == true
		cc_os_free((void *)ptr->stack_ptr);
		cc_os_free(ptr);
#endif
	}

	return next_ptr;
}

#if CC_OS_POWER_SAVE_EN
static void __cc_power_save_callback(void)
{
	arch_wfi();
}
#endif
/*****************************************************
 *	USER FUNCTION DEFINATION
 *****************************************************/
void _cc_os_idle_task_fn(cc_os_args args)
{
	static cc_sched_tcb_t * ptr  = CC_OS_NULL_PTR;
	cc_sched_ctrl_t * sched_ctrl = (cc_sched_ctrl_t *) args;
	ptr = sched_ctrl->ready_list_head;
#if CC_OS_POWER_SAVE_EN
	if (sched_ctrl->cb_hooks_reg.sleep_cb == CC_OS_NULL_PTR)
	{
		sched_ctrl->cb_hooks_reg.sleep_cb = __cc_power_save_callback;
	}
#endif
	while (true)
	{
		/* Clean up task if terminated */
		ptr = __free_terminated_task(ptr);

#if CC_OS_POWER_SAVE_EN
		/* Power Save code */
		if (sched_ctrl->cb_hooks_reg.pre_sleep_cb != CC_OS_NULL_PTR)
		{
			sched_ctrl->cb_hooks_reg.pre_sleep_cb();
		}
		if (sched_ctrl->cb_hooks_reg.sleep_cb != CC_OS_NULL_PTR)
		{
			sched_ctrl->cb_hooks_reg.sleep_cb();
		}
		if (sched_ctrl->cb_hooks_reg.post_sleep_cb != CC_OS_NULL_PTR)
		{
			sched_ctrl->cb_hooks_reg.post_sleep_cb();
		}
#endif
		/* Yield for next available task */
		cc_os_task_yield();
	}
}
