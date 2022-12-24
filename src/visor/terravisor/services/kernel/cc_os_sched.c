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
	CC_SCHED_ALGO(cc_sched_algo_round_robin, __cc_sched_algo_round_robin_fn),
	CC_SCHED_ALGO(cc_sched_algo_priority_driven, __cc_sched_algo_priority_driven_fn),
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
				ptr->task_status = cc_sched_task_status_ready;
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
	cc_sched_tcb_t * ptr = sched_ctrl->curr_task;

	__cc_sched_wait_list_adjustment(sched_ctrl);

	/* Context switch to next task */
	if (ptr->ready_link.next->task_status == cc_sched_task_status_ready)
	{
		__cc_sched_context_switch(ptr->ready_link.next);
	}
}

static void __cc_sched_algo_priority_driven_fn(cc_sched_ctrl_t * sched_ctrl)
{
	/* do waitlist adjustment */
	cc_sched_tcb_t * ptr = sched_ctrl->ready_list_head;

	__cc_sched_wait_list_adjustment(sched_ctrl);
	while (1)
	{
		if (ptr == sched_ctrl->ready_list_head)
		{
			break;
		}

	}

}
