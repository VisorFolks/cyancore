/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os.h
 * Description		: CC OS Kernel definations
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/cc_os.h>
#include <terravisor/cc_os/cc_os_sched.h>

/*****************************************************
 *	GLOBAL DECLARATIONS
 *****************************************************/
#if CC_DYNAMIC == 0
extern cc_sched_tcb_t g_cc_os_tcb_list[];
#else
extern cc_sched_tcb_t *g_cc_os_tcb_list;
#endif

/*****************************************************
 *	GLOBAL EXTERNS FUNCTIONS
 *****************************************************/
extern void CC_OS_IDLE_TASK(void * args);

/*****************************************************
 *	GLOBAL EXTERNS VARIABLES
 *****************************************************/
extern cc_sched_t *g_cc_sched;
extern cc_sched_t g_cc_sched_list [];
extern cc_sched_ctrl_t g_sched_ctrl;

/*****************************************************
 *	STATIC FUNCTION DEFINATIONS
 *****************************************************/
static void __cc_os_task_yeild()
{
	return;
}
/*****************************************************
 *	USER FUNCTION DEFINATIONS
 *****************************************************/
cc_os_err_t cc_os_add_task (cc_os_task_t * cc_os_task)
{
	ASSERT_IF_FALSE(cc_os_task != NULL);
	ASSERT_IF_FALSE(cc_os_task->name != NULL);
	ASSERT_IF_FALSE(cc_os_task->stack_ptr != NULL);
	ASSERT_IF_FALSE(cc_os_task->task_fn != NULL);
	ASSERT_IF_FALSE(cc_os_task->stack_len != 0);

	cc_sched_tcb_t * ptr = g_sched_ctrl.ready_list_head;

#if CC_DYNAMIC == 1
	if (ptr == NULL)
	{
		/* First Dynamic task */
		ptr = (cc_sched_tcb_t *)cc_os_malloc(sizeof(cc_sched_tcb_t));
		if (ptr == NULL)
		{
			return error_os_task_overfow;
		}
	}
#endif
	if ((ptr->ready_link.next == NULL )&& (ptr->ready_link.prev == NULL))
	{
		ptr->ready_link.next = ptr->ready_link.prev = g_sched_ctrl.ready_list_head;
	}

	else
	{
#if CC_DYNAMIC == 0
		/* Static Task Allocation */
		for (size_t i = 0; i < ccosconfig_CC_OS_MAX_THREAD; i++)
		{
			/* Get an available node from global tcb list */
			if (g_cc_os_tcb_list[i].task_status == cc_sched_task_status_exit)
			{
				ptr = &(g_cc_os_tcb_list[i]);
				break;
			}
		}
		if (ptr != g_sched_ctrl.ready_list_head)
		{
#else
		/* Dynamic Task Declaration */
		ptr = (cc_sched_tcb_t *)cc_os_malloc(sizeof(cc_sched_tcb_t));
		if (ptr != NULL)
		{
#endif
			/* Insert node at last */
			ptr->ready_link.next = g_sched_ctrl.ready_list_head;
			g_sched_ctrl.ready_list_head->ready_link.prev = ptr;
			ptr->ready_link.prev = g_sched_ctrl.ready_list_head->ready_link.prev;
			g_sched_ctrl.ready_list_head->ready_link.prev->ready_link.next = ptr;
		}
		else
		{
			return error_os_task_overfow;
		}
	}
	/* Fill tcb details */
	memcpy(ptr->name, cc_os_task->name, ccosconfig_CC_OS_TASK_NAME_LEN);
	ptr->stack_ptr 	 = cc_os_task->stack_ptr;
	ptr->priority 	 = cc_os_task->priority;
	if (g_sched_ctrl.task_max_prio == NULL)
	{
		g_sched_ctrl.task_max_prio = ptr;
	}
	else
	{
		if(g_sched_ctrl.task_max_prio->priority < ptr->priority)
		{
			g_sched_ctrl.task_max_prio = ptr;
		}
	}

	cc_os_task->task_tcb_ptr = ptr;
	ptr->task_status = cc_sched_task_status_ready;
	return success;
}

cc_os_err_t cc_os_del_task (cc_os_task_t * cc_os_task)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.curr_task;

	ASSERT_IF_FALSE(cc_os_task->task_fn != CC_OS_IDLE_TASK);

	if (cc_os_task != NULL)
	{
		ptr = cc_os_task->task_tcb_ptr;
	}
	/* Code to handle first node */
	if (ptr == g_sched_ctrl.ready_list_head)
	{
		if (ptr->ready_link.next != g_sched_ctrl.ready_list_head)
		{
			/* code for more than one node */
			g_sched_ctrl.ready_list_head = ptr->ready_link.next;
		}
		else
		{
			/* code for only one node */
			memset(g_sched_ctrl.ready_list_head, 0, sizeof(cc_sched_tcb_t));
			g_sched_ctrl.task_max_prio = NULL;
#if CC_DYNAMIC == 0
			g_sched_ctrl.ready_list_head = &(g_cc_os_tcb_list[0]);
#else
			g_sched_ctrl.ready_list_head = NULL;
#endif
			return success;
		}

	}
	ptr->task_status   = cc_sched_task_status_exit;

	if (ptr == g_sched_ctrl.curr_task)
	{
		/* Yeild */
	}

	return success;
}

cc_os_err_t cc_os_pause_task (cc_os_task_t * cc_os_task)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.curr_task;
	if (cc_os_task != NULL)
	{
		ptr = cc_os_task->task_tcb_ptr;
	}
	ptr->task_status = cc_sched_task_status_wait;

	return success;
}

cc_os_err_t cc_os_resume_task (cc_os_task_t * cc_os_task)
{
	ASSERT_IF_FALSE(cc_os_task != NULL);

	cc_os_task->task_tcb_ptr->task_status = cc_sched_task_status_ready;

	return success;
}

cc_os_err_t cc_os_del_task_by_name (const char * name)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.curr_task;
	int name_found = 0;
	if (name != NULL)
	{
		/* code to delete node equal to name */
		ptr = g_sched_ctrl.ready_list_head;
		while(ptr->ready_link.next != g_sched_ctrl.ready_list_head)
		{
			if(strcmp(ptr->name, name) == 0)
			{
				name_found = 1;
				break;
			}
		}
		if (!name_found)
		{
			return error_func_inval_arg;
		}
	}
	else
	{
		ptr = g_sched_ctrl.curr_task;
	}
	/* Code to handle first node */
	if (ptr == g_sched_ctrl.ready_list_head)
	{
		if (ptr->ready_link.next != g_sched_ctrl.ready_list_head)
		{
			/* code for more than one node */
			g_sched_ctrl.ready_list_head = ptr->ready_link.next;
		}
		else
		{
			/* code for only one node */
			memset(g_sched_ctrl.ready_list_head, 0, sizeof(cc_sched_tcb_t));
			g_sched_ctrl.ready_list_head = &(g_cc_os_tcb_list[0]);
			return success;
		}

	}
	ptr->ready_link.next->ready_link.prev = ptr->ready_link.prev;
	ptr->ready_link.prev->ready_link.next = ptr->ready_link.next;

#if CC_DYNAMIC == 0
	/* Static task Reset */
	ptr->task_status   = cc_sched_task_status_exit;
	ptr->ready_link.next = NULL;
	ptr->ready_link.prev = NULL;
#else
	/* Dynamic Task Deletion */
	/* TODO: Need to push to Terminated Queue so that the scheduler can free the task when not running*/
#endif

	return success;
}

cc_os_err_t cc_os_pause_task_by_name (const char * name)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.curr_task;
	int name_found = 0;
	if (name != NULL)
	{
		/* code to pause node equal to name */
		ptr = g_sched_ctrl.ready_list_head;
		while(ptr->ready_link.next != g_sched_ctrl.ready_list_head)
		{
			if(strcmp(ptr->name, name) == 0)
			{
				name_found = 1;
				break;
			}
		}
		if (!name_found)
		{
			return error_func_inval_arg;
		}
	}

	ptr->task_status = cc_sched_task_status_wait;

	return success;
}

cc_os_err_t cc_os_resume_task_by_name (const char * name)
{
	ASSERT_IF_FALSE(name != NULL);

	cc_sched_tcb_t * ptr = g_sched_ctrl.ready_list_head;
	int name_found = 0;

	/* code to resume node equal to name */
	while(ptr->ready_link.next != g_sched_ctrl.ready_list_head)
	{
		if(strcmp(ptr->name, name) == 0)
		{
			name_found = 1;
			break;
		}
	}
	if (!name_found)
	{
		return error_func_inval_arg;
	}

	ptr->task_status = cc_sched_task_status_ready;

	return success;
}

cc_os_err_t cc_os_task_wait (const size_t ticks)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.curr_task;

	if (ticks > 0)
	{
		/* Put into wait state only if wait count is more than 0 */
		if (g_sched_ctrl.wait_list_head == NULL)
		{
			/* First Wait list node */
			g_sched_ctrl.wait_list_head = ptr;
			ptr->wait_link.next = ptr;
			ptr->wait_link.prev = ptr;
		}
		else
		{
			ptr->wait_link.next = g_sched_ctrl.wait_list_head;
			ptr->wait_link.prev = g_sched_ctrl.wait_list_head->wait_link.prev;
			g_sched_ctrl.wait_list_head->wait_link.prev->wait_link.next = ptr;
			g_sched_ctrl.wait_list_head->wait_link.prev = ptr;
		}

		ptr->task_delay_ticks = ticks;
		ptr->task_status = cc_sched_task_status_wait;
	}

	__cc_os_task_yeild();

	return success;
}

cc_os_err_t set_cc_os_sched_algo(cc_sched_algo_t sched_algo)
{
	ASSERT_IF_FALSE(sched_algo != cc_sched_algo_max);

	g_sched_ctrl.selected_sched = &(g_cc_sched_list[sched_algo]);

	return success;
}

cc_os_err_t cc_os_run (void)
{
	/* OS Init code */
	/* Initialise scheduler */

	/* Initialise IDLE Task */
	CC_TASK_DEF(
		cc_os_idle,				/* Name of the instance */
		CC_OS_IDLE_TASK,			/* Function pointer */
		&g_sched_ctrl,				/* Task Args*/
		ccosconfig_CC_OS_TASK_PRIORITY,		/* Task Priority */
		ccosconfig_CC_OS_TASK_STACK_LEN		/* Stack Length of IDLE Task */
		);
	cc_os_add_task(&CC_GET_TASK_INST(cc_os_idle));

	return success;
}
