/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_sched.c
 * Description		: CC OS Kernel scheduler definations
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <stdlib.h>
#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/cc_os_sched.h>

/*****************************************************
 *	DEFINES
 *****************************************************/
#define CC_SCHED_ALGO(_id, _fn) {	\
	.cc_selected_algo = _id,	\
	.algo_function = _fn}

/*****************************************************
 *	STATIC FUNCTION DECLARATION
 *****************************************************/
static void __cc_sched_algo_round_robin_fn(cc_sched_ctrl_t * sched_ctrl);
static void __cc_sched_algo_priority_driven_fn(cc_sched_ctrl_t * sched_ctrl);

/*****************************************************
 *	GLOBAL DECLARATIONS
 *****************************************************/
#if !ccosconfig_CC_OS_USE_DYNAMIC
cc_sched_tcb_t g_cc_os_tcb_list [ccosconfig_CC_OS_MAX_THREAD];
#else
cc_sched_tcb_t * g_cc_os_tcb_list	= NULL;
#endif

cc_sched_t g_cc_sched_list [] =
{
	CC_SCHED_ALGO(cc_sched_algo_round_robin, 	__cc_sched_algo_round_robin_fn),
	CC_SCHED_ALGO(cc_sched_algo_priority_driven, 	__cc_sched_algo_priority_driven_fn),
};

cc_sched_ctrl_t g_sched_ctrl =
{
#if !ccosconfig_CC_OS_USE_DYNAMIC
	.ready_list_head 	= &(g_cc_os_tcb_list[0]),
	.curr_task 		= &(g_cc_os_tcb_list[0]),
#else
	.ready_list_head 	= NULL,
	.curr_task 		= NULL,
#endif
	.wait_list_head		= NULL,
	.task_max_prio		= NULL,
	.selected_sched		= &(g_cc_sched_list[cc_sched_algo_round_robin])
};

/*****************************************************
 *	INTERNAL USED FUNCTIONS (NON-STATIC)
 *****************************************************/
void _insert_after(cc_sched_tcb_t * ptr, cc_sched_tcb_t * new_node, uint8_t link_type)
{
	switch (link_type)
	{
		case 0:
			/* Ready Link */
			if (ptr == NULL)
			{
				ptr = new_node;
				new_node->ready_link.next = new_node;
				new_node->ready_link.prev = new_node;
			}
			else
			{
				new_node->ready_link.next = ptr->ready_link.next;
				new_node->ready_link.prev = ptr;
				new_node->ready_link.next->ready_link.prev = new_node;
				ptr->ready_link.next = new_node;
			}
			break;
		case 1:
			/* Wait Link */
			if (ptr == NULL)
			{
				ptr = new_node;
				new_node->wait_link.next = new_node;
				new_node->wait_link.prev = new_node;
			}
			{
				new_node->wait_link.next = ptr->wait_link.next;
				new_node->wait_link.prev = ptr;
				new_node->wait_link.next->wait_link.prev = new_node;
				ptr->wait_link.next = new_node;
			}
			break;
		default:
			return;
	}
}
void _insert_before(cc_sched_tcb_t * ptr, cc_sched_tcb_t * new_node, uint8_t link_type)
{
	switch (link_type)
	{
		case 0:
			/* Ready Link */
			if (ptr == NULL)
			{
				ptr = new_node;
				new_node->ready_link.next = new_node;
				new_node->ready_link.prev = new_node;
			}
			{
				new_node->ready_link.next = ptr;
				new_node->ready_link.prev = ptr->ready_link.prev;
				ptr->ready_link.prev = new_node;
				new_node->ready_link.prev->ready_link.next = new_node;
			}
			break;
		case 1:
			/* Wait Link */
			if (ptr == NULL)
			{
				ptr = new_node;
				new_node->wait_link.next = new_node;
				new_node->wait_link.prev = new_node;
			}
			{
				new_node->wait_link.next = ptr;
				new_node->wait_link.prev = ptr->wait_link.prev;
				ptr->wait_link.prev = new_node;
				new_node->wait_link.prev->wait_link.next = new_node;
			}
			break;
		default:
			return;
	}
}

void _cc_sched_send_to_wait(cc_sched_ctrl_t * sched_ctrl, cc_sched_tcb_t * ptr, const size_t ticks)
{
	if (ptr->task_status == cc_sched_task_status_wait)
	{
		return;
	}
	_insert_before(sched_ctrl->wait_list_head, ptr, 1);

	ptr->task_delay_ticks = ticks;
	ptr->task_status = cc_sched_task_status_wait;
}

void _cc_sched_send_to_resume(cc_sched_ctrl_t * sched_ctrl, cc_sched_tcb_t * ptr)
{
	if (ptr->task_status == cc_sched_task_status_ready)
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
			sched_ctrl->wait_list_head = NULL;
		}
	}
	ptr->wait_link.prev->wait_link.next = ptr->wait_link.next;
	ptr->wait_link.next->wait_link.prev = ptr->wait_link.prev;
	ptr->wait_link.prev = NULL;
	ptr->wait_link.next = NULL;
	ptr->task_delay_ticks = 0;
	ptr->task_status = cc_sched_task_status_ready;
}

/*****************************************************
 *	STATIC FUNCTION DEFINATIONS
 *****************************************************/
static void __cc_sched_context_switch(cc_sched_tcb_t * next_task)
{
	next_task->task_status = cc_sched_task_status_running;
}

static void __cc_sched_wait_list_adjustment(cc_sched_ctrl_t * sched_ctrl)
{
	cc_sched_tcb_t * ptr;
	if(sched_ctrl->wait_list_head != NULL)
	{
		ptr = sched_ctrl->wait_list_head;
		/* Tasks present in wait list */
		while(1)
		{
			ptr->task_delay_ticks--;	/* Tick caliberations required */
			if(ptr->task_delay_ticks == 0)
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
	cc_sched_tcb_t * ptr = sched_ctrl->ready_list_head->ready_link.prev;

	__cc_sched_wait_list_adjustment(sched_ctrl);
	while (1)
	{
		if (ptr->task_status == cc_sched_task_status_ready)
		{
			break;
		}
		else
		{
			/* Iterate Backwards */
			ptr = ptr->wait_link.prev;
		}
		if (ptr == sched_ctrl->ready_list_head)
		{
			/* IDLE Task */
			_cc_sched_send_to_resume(&g_sched_ctrl, ptr);
			break;
		}
	}
	__cc_sched_context_switch(ptr);
}
