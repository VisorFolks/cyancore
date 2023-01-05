/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_tasks.c
 * Description		: CC OS Kernel tasks related definations definations
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <arch.h>
#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/cc_os.h>

/*****************************************************
 *	DEFINES
 *****************************************************/
#define CC_OS_PRIORITY_MAX		255

/*****************************************************
 *	INTERNAL EXTERNS FUNCTIONS
 *****************************************************/
extern status_t _insert_after		(cc_sched_tcb_t ** ptr, cc_sched_tcb_t * new_node, uint8_t link_type);
extern status_t _insert_before		(cc_sched_tcb_t ** ptr, cc_sched_tcb_t * new_node, uint8_t link_type);
extern void _cc_sched_send_to_wait	(cc_sched_ctrl_t * sched_ctrl, cc_sched_tcb_t * ptr, const size_t ticks);
extern void _cc_sched_send_to_resume	(cc_sched_ctrl_t * sched_ctrl, cc_sched_tcb_t * ptr);

/*****************************************************
 *	GLOBAL EXTERNS VARIABLES
 *****************************************************/
extern void _cc_os_idle_task_fn(cc_os_args args);
extern cc_sched_t g_cc_sched_list [];
extern cc_sched_ctrl_t g_sched_ctrl;

/*****************************************************
 *	GLOBAL DECLARATIONS
 *****************************************************/
#if CC_OS_DYNAMIC == CC_OS_FALSE
extern cc_sched_tcb_t g_cc_os_tcb_list[];
#else
extern cc_sched_tcb_t *g_cc_os_tcb_list;
#endif

#if CC_OS_DYNAMIC == CC_OS_FALSE
uint8_t _cc_os_stack[CC_OS_IDLE_STACK_LEN];
#else
uint8_t * _cc_os_stack = CC_OS_NULL_PTR;
#endif
cc_os_task_t * cc_os_idle_task;
/*****************************************************
 *	STATIC FUNCTION DEFINATIONS
 *****************************************************/
void __cc_init_scheduler()
{
	return;
}
/*****************************************************
 *	USER FUNCTION DEFINATIONS
 *****************************************************/
status_t cc_os_add_task (
	cc_os_task_t * cc_os_task,
	const char* name,
	task_fn task_func,
	cc_os_args args,
	uint8_t priority,
	size_t stack_len,
	uintptr_t stack_ptr
	)
{
	CC_OS_ASSERT_IF_FALSE(cc_os_task == CC_OS_NULL_PTR);
	CC_OS_ASSERT_IF_FALSE(name != CC_OS_NULL_PTR);
#if CC_OS_DYNAMIC == CC_OS_FALSE
	CC_OS_ASSERT_IF_FALSE(stack_ptr != (uintptr_t) CC_OS_NULL_PTR);
#endif
	CC_OS_ASSERT_IF_FALSE(task_func != CC_OS_NULL_PTR);
	CC_OS_ASSERT_IF_FALSE(stack_len != CC_OS_FALSE);
	CC_OS_ASSERT_IF_FALSE(priority >= CC_OS_IDLE_TASK_PRIORITY);
	CC_OS_ASSERT_IF_FALSE(priority < CC_OS_PRIORITY_MAX);

	cc_os_pause_all_task();

	cc_sched_tcb_t * ptr = g_sched_ctrl.ready_list_head;

#if CC_OS_DYNAMIC == CC_OS_TRUE
	if (ptr == CC_OS_NULL_PTR)
	{
		/* First Dynamic task */
		ptr = (cc_sched_tcb_t *)cc_os_malloc(sizeof(cc_sched_tcb_t));
		if (ptr == CC_OS_NULL_PTR)
		{
			cc_os_resume_all_task();
			return error_memory_low;
		}
	}
#endif
	if ((ptr->ready_link.next == CC_OS_NULL_PTR )&& (ptr->ready_link.prev == CC_OS_NULL_PTR))
	{
		ptr->ready_link.next = ptr->ready_link.prev = g_sched_ctrl.ready_list_head;
	}

	else
	{
#if CC_OS_DYNAMIC == CC_OS_FALSE
		/* Static Task Allocation */
		for (size_t i = CC_OS_FALSE; i < CC_OS_MAX_THREAD; i++)
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
		if (ptr != CC_OS_NULL_PTR)
		{
#endif
			/* Fill tcb details */
			ptr->name	 = name;
			ptr->stack_ptr 	 = (uintptr_t) malloc(stack_len);
			if(ptr->stack_ptr == CC_OS_NULL_PTR)
			{
				cc_os_resume_all_task();
				return error_memory_low;
			}
			ptr->priority 	 = priority;
			ptr->task_func	 = task_func;
			ptr->args_ptr	 = (uintptr_t) args;
		}
		else
		{
			cc_os_resume_all_task();
			return error_memory_low;
		}
	}
	/* Insert Tasks in assending order of its priority */
	if (g_sched_ctrl.task_max_prio == CC_OS_NULL_PTR)
	{
		g_sched_ctrl.task_max_prio = ptr;
	}
	else if(g_sched_ctrl.task_max_prio->priority <= ptr->priority)
	{
		if(_insert_after(&(g_sched_ctrl.task_max_prio), ptr, CC_OS_FALSE) == success)
		{
			g_sched_ctrl.task_max_prio = ptr;
		}
		else
		{
			cc_os_resume_all_task();
			return error_os_task_overfow;
		}
	}
	else
	{
		cc_sched_tcb_t * comp_ptr = g_sched_ctrl.task_max_prio->ready_link.next;
		while (1)
		{
			if (comp_ptr->priority <= ptr->priority && (_insert_after(&comp_ptr, ptr, CC_OS_FALSE) == success))
			{
				break;
			}
			else
			{
				comp_ptr = comp_ptr->ready_link.next;
			}
		}
	}

	*cc_os_task = ptr;
	ptr->task_status = cc_sched_task_status_ready;

	cc_os_resume_all_task();
	return success;
}

status_t cc_os_del_task (cc_os_task_t cc_os_task)
{
	CC_OS_ASSERT_IF_FALSE(cc_os_task->task_func != &_cc_os_idle_task_fn);

	cc_sched_tcb_t * ptr = g_sched_ctrl.curr_task;

	if (cc_os_task != CC_OS_NULL_PTR)
	{
		ptr = cc_os_task;
	}
	/* Code to handle first node */
	if (ptr == g_sched_ctrl.ready_list_head)
	{
		/* IDLE Task can not be deleted */
		return error_os_invalid_op;
	}
	ptr->task_status   = cc_sched_task_status_exit;

	if (ptr == g_sched_ctrl.curr_task)
	{
		cc_os_task_yield();	/* Yeild */
	}

	return success;
}

status_t cc_os_pause_task (cc_os_task_t cc_os_task)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.curr_task;
	if (cc_os_task != CC_OS_NULL_PTR)
	{
		ptr = cc_os_task;
	}

	_cc_sched_send_to_wait(&g_sched_ctrl, ptr, CC_OS_DELAY_MAX);

	return success;
}

status_t cc_os_pause_all_task (void)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.ready_list_head->ready_link.next;

	while (ptr != g_sched_ctrl.ready_list_head)
	{
		if (ptr == g_sched_ctrl.curr_task)
		{
			continue;
		}

		_cc_sched_send_to_wait(&g_sched_ctrl, ptr, CC_OS_DELAY_MAX);
		ptr = ptr->ready_link.next;
	}

	return success;
}

status_t cc_os_resume_all_task (void)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.ready_list_head->ready_link.next;
	if (ptr != CC_OS_NULL_PTR)
	{
		while (ptr != g_sched_ctrl.ready_list_head)
		{
			if (ptr == g_sched_ctrl.curr_task)
			{
				continue;
			}
			_cc_sched_send_to_resume(&g_sched_ctrl, ptr);
			ptr = ptr->ready_link.next;
		}
	}
	else
	{
		return error_os_invalid_op;
	}

	return success;
}

status_t cc_os_resume_task (cc_os_task_t cc_os_task)
{
	CC_OS_ASSERT_IF_FALSE(cc_os_task != CC_OS_NULL_PTR);

	cc_sched_tcb_t * ptr = cc_os_task;

	_cc_sched_send_to_resume(&g_sched_ctrl, ptr);

	return success;
}

status_t cc_os_set_sched_algo(cc_sched_algo_t sched_algo)
{
	CC_OS_ASSERT_IF_FALSE(sched_algo != cc_sched_algo_max);

	g_sched_ctrl.selected_sched = &(g_cc_sched_list[sched_algo]);

	return success;
}

const char * cc_os_get_curr_task_name(void)
{
	return g_sched_ctrl.curr_task->name;
}

void cc_os_task_wait (const size_t ticks)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.curr_task;

	if (ticks > CC_OS_FALSE)
	{
		_cc_sched_send_to_wait(&g_sched_ctrl, ptr, ticks);
	}

	cc_os_task_yield();
}

void cc_os_task_yield()
{
	return;
}

void cc_os_run (void)
{
	/* OS Init code */
	/* Initialise IDLE Task */
	cc_os_add_task(cc_os_idle_task,
		CC_OS_IDLE_TASK_NAME,
		&_cc_os_idle_task_fn,
		&g_sched_ctrl,
		CC_OS_IDLE_TASK_PRIORITY,
		CC_OS_IDLE_STACK_LEN,
		(uintptr_t) _cc_os_stack);

	/* Initialise scheduler */
	__cc_init_scheduler();
	cc_os_task_yield(); /* Yeild */
	while (1)
	{
		/* Code shall not reach here */
		arch_wfi();
	}
}
