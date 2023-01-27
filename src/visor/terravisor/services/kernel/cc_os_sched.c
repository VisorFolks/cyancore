/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_sched.c
 * Description		: CC OS Kernel scheduler definations
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <terravisor/cc_os/utils/cc_os_sched.h>
#include <arch.h>

/*****************************************************
 *	DEFINES
 *****************************************************/
#define CC_SCHED_ALGO(_id, _fn) {	\
	.cc_selected_algo = _id,	\
	.algo_function = _fn}

/*****************************************************
 *	STATIC FUNCTION DECLARATION
 *****************************************************/
static void __cc_sched_deadlock_adjustment_and_detection(const cc_sched_ctrl_t * sched_ctrl);
static void __cc_sched_wait_list_adjustment(cc_sched_ctrl_t * sched_ctrl);
static void __cc_sched_algo_round_robin_fn(cc_sched_ctrl_t * sched_ctrl);
static void __cc_sched_algo_priority_driven_fn(cc_sched_ctrl_t * sched_ctrl);

/*****************************************************
 *	GLOBAL DECLARATIONS
 *****************************************************/
#if !CC_OS_USE_DYNAMIC
cc_sched_tcb_t g_cc_os_tcb_list [CC_OS_MAX_THREAD];
#else
cc_sched_tcb_t * g_cc_os_tcb_list	= CC_OS_NULL_PTR;
#endif

cc_sched_t g_cc_sched_list [] =
{
	CC_SCHED_ALGO(cc_sched_algo_round_robin, 	__cc_sched_algo_round_robin_fn),
	CC_SCHED_ALGO(cc_sched_algo_priority_driven, 	__cc_sched_algo_priority_driven_fn),
};

cc_sched_ctrl_t g_sched_ctrl =
{
#if !CC_OS_USE_DYNAMIC
	.ready_list_head 	= &(g_cc_os_tcb_list[false]),
	.curr_task 		= &(g_cc_os_tcb_list[false]),
#else
	.ready_list_head 	= CC_OS_NULL_PTR,
	.curr_task 		= CC_OS_NULL_PTR,
#endif
	.wait_list_head		= CC_OS_NULL_PTR,
	.task_max_prio		= CC_OS_NULL_PTR,
	.selected_sched		= &(g_cc_sched_list[cc_sched_algo_round_robin])
};

/*****************************************************
 *	INTERNAL USED FUNCTIONS (NON-STATIC)
 *****************************************************/
status_t _insert_after(cc_sched_tcb_t ** ptr, cc_sched_tcb_t * new_node, uint8_t link_type)
{
	CC_OS_ASSERT_IF_FALSE(new_node != CC_OS_NULL_PTR);
	if (link_type == true)
	{
		/* Wait Link */
		if (*ptr == CC_OS_NULL_PTR)
		{
			*ptr = new_node;
			new_node->wait_link.next = new_node;
			new_node->wait_link.prev = new_node;
		}
		else
		{
			new_node->wait_link.next = (*ptr)->wait_link.next;
			new_node->wait_link.prev = *ptr;
			new_node->wait_link.next->wait_link.prev = new_node;
			(*ptr)->wait_link.next = new_node;
		}
	}
	else
	{
		/* Ready Link */
		if (*ptr == CC_OS_NULL_PTR)
		{
			*ptr = new_node;
			new_node->ready_link.next = new_node;
			new_node->ready_link.prev = new_node;
		}
		else
		{
			new_node->ready_link.next = (*ptr)->ready_link.next;
			new_node->ready_link.prev = *ptr;
			new_node->ready_link.next->ready_link.prev = new_node;
			(*ptr)->ready_link.next = new_node;
		}
	}
	return success;
}
status_t _insert_before(cc_sched_tcb_t ** ptr, cc_sched_tcb_t * new_node, uint8_t link_type)
{
	CC_OS_ASSERT_IF_FALSE(new_node != CC_OS_NULL_PTR);
	if (link_type == true)
	{
		/* Wait Link */
		if (*ptr == CC_OS_NULL_PTR)
		{
			*ptr = new_node;
			new_node->wait_link.next = new_node;
			new_node->wait_link.prev = new_node;
		}
		else
		{
			new_node->wait_link.next = *ptr;
			new_node->wait_link.prev = (*ptr)->wait_link.prev;
			(*ptr)->wait_link.prev = new_node;
			new_node->wait_link.prev->wait_link.next = new_node;
		}
	}
	else
	{
		/* Ready Link */
		if (*ptr == CC_OS_NULL_PTR)
		{
			*ptr = new_node;
			new_node->ready_link.next = new_node;
			new_node->ready_link.prev = new_node;
		}
		else
		{
			new_node->ready_link.next = *ptr;
			new_node->ready_link.prev = (*ptr)->ready_link.prev;
			(*ptr)->ready_link.prev = new_node;
			new_node->ready_link.prev->ready_link.next = new_node;
		}
	}
	return success;
}

void _cc_sched_send_to_wait(cc_sched_ctrl_t * sched_ctrl, cc_sched_tcb_t * ptr, const size_t ticks)
{
	if (ptr->task_status == cc_sched_task_status_wait)
	{
		return;
	}
	if(_insert_before(&(sched_ctrl->wait_list_head), ptr, true) == success)
	{
		ptr->wait_res.task_delay_ticks = ticks;
		ptr->task_status = cc_sched_task_status_wait;
	}
}

void _cc_sched_send_to_pause(cc_sched_ctrl_t * sched_ctrl, cc_sched_tcb_t * ptr)
{
	if (ptr->task_status == cc_sched_task_status_pause)
	{
		return;
	}
	if(_insert_before(&(sched_ctrl->wait_list_head), ptr, true) == success)
	{
		ptr->wait_res.task_delay_ticks = CC_OS_DELAY_MAX;
		ptr->task_status = cc_sched_task_status_pause;
	}
}

void _cc_sched_send_to_resume(cc_sched_ctrl_t * sched_ctrl, cc_sched_tcb_t * ptr)
{
	if (ptr->task_status < cc_sched_task_status_wait)
	{
		return;
	}

	if (ptr == sched_ctrl->wait_list_head)
	{
		/* First in the list */
		sched_ctrl->wait_list_head = ptr->wait_link.next;
		if (ptr->wait_link.next == ptr && ptr->wait_link.prev == ptr)
		{
			/* Last Wait task left */
			sched_ctrl->wait_list_head = CC_OS_NULL_PTR;
		}
	}
	ptr->wait_link.prev->wait_link.next = ptr->wait_link.next;
	ptr->wait_link.next->wait_link.prev = ptr->wait_link.prev;
	ptr->wait_link.prev = CC_OS_NULL_PTR;
	ptr->wait_link.next = CC_OS_NULL_PTR;
	ptr->wait_res.task_delay_ticks = false;
	ptr->task_status = cc_sched_task_status_ready;
}

void _cc_os_pre_sched(cc_os_args args)
{
	cc_sched_ctrl_t * sched_ctrl = (cc_sched_ctrl_t *) args;

	__cc_sched_wait_list_adjustment(sched_ctrl);
	__cc_sched_deadlock_adjustment_and_detection(sched_ctrl);
}

void _cc_os_scheduler_despatch(void)
{
	if (g_sched_ctrl.cb_hooks_reg.pre_sched != NULL)
	{
		/* Call Pre_sched Function */
		g_sched_ctrl.cb_hooks_reg.pre_sched((cc_os_args) &g_sched_ctrl);
	}
	else
	{
		/* A System Error case */
		arch_panic_handler();
	}

	if (g_sched_ctrl.selected_sched != NULL)
	{
		/* Call the scheduler */
		g_sched_ctrl.selected_sched->algo_function(&g_sched_ctrl);
	}
	else
	{
		/* A System Error case */
		arch_panic_handler();
	}

}
/*****************************************************
 *	STATIC FUNCTION DEFINATIONS
 *****************************************************/
static void __cc_sched_context_switch(cc_sched_tcb_t * next_task)
{
	next_task->task_status = cc_sched_task_status_running;
}

static void __cc_sched_deadlock_adjustment_and_detection(const cc_sched_ctrl_t * sched_ctrl _UNUSED)
{
#if CC_OS_ANTI_DEADLOCK
	cc_sched_tcb_t * ptr = sched_ctrl->ready_list_head;
	static cc_sched_anti_deadlock_t anti_deadlock_notify;
	while (ptr != CC_OS_NULL_PTR)
	{
		if (ptr->task_status != cc_sched_task_status_pause)
		{
			ptr->task_wd_ticks--;
		}
		if ((ptr->task_wd_ticks == false) && (sched_ctrl->cb_hooks_reg.deadlock_notify != CC_OS_NULL_PTR))
		{
			/* Create notification params */
			anti_deadlock_notify.name = ptr->name;
			anti_deadlock_notify.task_func = ptr->task_func;

			if (ptr->task_status != cc_sched_task_status_exit)
			{
				ptr->task_status = cc_sched_task_status_exit;
			}
			/* Notify the user that the task pointed by ptr is dead and has been terminated */
			sched_ctrl->cb_hooks_reg.deadlock_notify((cc_os_args) &anti_deadlock_notify);
		}
		if (ptr->ready_link.next == sched_ctrl->ready_list_head)
		{
			break;
		}
	}
#else
	return;
#endif /* CC_OS_ANTI_DEADLOCK */
}
static void __cc_sched_wait_list_adjustment(cc_sched_ctrl_t * sched_ctrl)
{
	cc_sched_tcb_t * ptr = sched_ctrl->wait_list_head;
	const int * wait_res = (int *)ptr->wait_res.wait_on_resource;
	while(ptr != CC_OS_NULL_PTR)
	{
		if (ptr->task_status == cc_sched_task_status_wait)
		{
			ptr->wait_res.task_delay_ticks--;	/* Tick caliberations required */

			if ((wait_res != CC_OS_NULL_PTR) && *wait_res > false)
			{
				/* The resource is available can can go to ready state */
				ptr->wait_res.task_delay_ticks = false;
				ptr->wait_res.wait_on_resource = false;
			}
			if(ptr->wait_res.task_delay_ticks == false)
			{
				_cc_sched_send_to_resume(sched_ctrl, ptr);
			}
			if (ptr->wait_link.next == sched_ctrl->wait_list_head)
			{
				break;
			}
			else
			{
				ptr = ptr->wait_link.next;
			}
		}
	}
}

/*****************************************************
 *	SCHEDULER ALGORITHMS
 *****************************************************/
static void __cc_sched_algo_round_robin_fn(cc_sched_ctrl_t * sched_ctrl)
{
	/* do waitlist adjustment */
	cc_sched_tcb_t * ptr = sched_ctrl->curr_task->ready_link.next;

	__cc_sched_wait_list_adjustment(sched_ctrl);

	if (ptr == sched_ctrl->ready_list_head)
	{
		/* IDLE Task */
		_cc_sched_send_to_resume(&g_sched_ctrl, ptr);
	}
	/* Context switch to next task */
	if (ptr->task_status == cc_sched_task_status_ready)
	{
		__cc_sched_context_switch(ptr->ready_link.next);
	}
}

static void __cc_sched_algo_priority_driven_fn(cc_sched_ctrl_t * sched_ctrl)
{
	/* do waitlist adjustment */
	__cc_sched_wait_list_adjustment(sched_ctrl);

	cc_sched_tcb_t * ptr = sched_ctrl->ready_list_head->ready_link.prev;
	if(ptr != CC_OS_NULL_PTR)
	{
		while (ptr->task_status != cc_sched_task_status_ready)
		{
			ptr = ptr->wait_link.prev;
			if (ptr == sched_ctrl->ready_list_head)
			{
				/* IDLE Task */
				_cc_sched_send_to_resume(&g_sched_ctrl, ptr);
				break;
			}
		}
		__cc_sched_context_switch(ptr);
	}
}
