#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/cc_os.h>
#include <terravisor/cc_os/cc_os_shed.h>

extern cc_shed_tcb_t * g_ready_list_head;

#if CC_DYNAMIC == 0
extern cc_shed_tcb_t g_cc_os_tcb_list[];
#else
extern cc_shed_tcb_t *g_cc_os_tcb_list;
#endif
extern cc_shed_tcb_t * g_curr_task;

cc_os_err_t cc_os_add_task (cc_os_task_t * cc_os_task)
{
	ASSERT_IF_FALSE(cc_os_task != NULL);
	ASSERT_IF_FALSE(cc_os_task->name != NULL);
	ASSERT_IF_FALSE(cc_os_task->stack_ptr != NULL);
	ASSERT_IF_FALSE(cc_os_task->task_fn != NULL);
	ASSERT_IF_FALSE(cc_os_task->stack_len != 0);

	cc_shed_tcb_t * ptr = g_ready_list_head;

#if CC_DYNAMIC == 1
	if (ptr == NULL)
	{
		/* First Dynamic task */
		ptr = (cc_shed_tcb_t *)cc_os_malloc(sizeof(cc_shed_tcb_t));
		if (ptr == NULL)
		{
			return error_os_task_overfow;
		}
	}
#endif
	if ((ptr->next_ready_tcb == NULL )&& (ptr->prev_ready_tcb == NULL))
	{
		ptr->next_ready_tcb = ptr->prev_ready_tcb = g_ready_list_head;
	}

	else
	{
#if CC_DYNAMIC == 0
		/* Static Task Allocation */
		for (size_t i = 0; i < ccosconfig_CC_OS_MAX_THREAD; i++)
		{
			/* Get an available node from global tcb list */
			if (g_cc_os_tcb_list[i].task_status == cc_shed_task_terminated)
			{
				ptr = &(g_cc_os_tcb_list[i]);
				break;
			}
		}
		if (ptr != g_ready_list_head)
		{
#else
		/* Dynamic Task Declaration */
		ptr = (cc_shed_tcb_t *)cc_os_malloc(sizeof(cc_shed_tcb_t));
		if (ptr != NULL)
		{
#endif
			/* Insert node at last */
			ptr->next_ready_tcb = g_ready_list_head;
			g_ready_list_head->prev_ready_tcb = ptr;
			ptr->prev_ready_tcb = g_ready_list_head->prev_ready_tcb;
			g_ready_list_head->prev_ready_tcb->next_ready_tcb = ptr;
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
	ptr->task_status = cc_shed_task_ready;
	return success;
}

cc_os_err_t cc_os_del_task (cc_os_task_t * cc_os_task)
{
	cc_shed_tcb_t * ptr = g_curr_task;
	if (cc_os_task != NULL)
	{
		ptr = cc_os_task;
	}
	/* Code to handle first node */
	if (ptr == g_ready_list_head)
	{
		if (ptr->next_ready_tcb != g_ready_list_head)
		{
			/* code for more than one node */
			g_ready_list_head = ptr->next_ready_tcb;
		}
		else
		{
			/* code for only one node */
			memset(g_ready_list_head, 0, sizeof(cc_shed_tcb_t));
			g_ready_list_head = &(g_cc_os_tcb_list[0]);
			return success;
		}

	}
	ptr->next_ready_tcb->prev_ready_tcb = ptr->prev_ready_tcb;
	ptr->prev_ready_tcb->next_ready_tcb = ptr->next_ready_tcb;

#if CC_DYNAMIC == 0
	/* Static task Reset */
	ptr->task_status   = cc_shed_task_terminated;
	ptr->next_ready_tcb = NULL;
	ptr->prev_ready_tcb = NULL;
#else
	/* Dynamic Task Deletion */
	/* TODO: Need to push to Terminated Queue so that the scheduler can free the task when not running */
#endif

	return success;
}

cc_os_err_t cc_os_pause_task (cc_os_task_t * cc_os_task)
{
	cc_shed_tcb_t * ptr = g_curr_task;
	if (cc_os_task != NULL)
	{
		ptr = cc_os_task;
	}
	ptr->task_status = cc_shed_task_wait;

	return success;
}

cc_os_err_t cc_os_resume_task (cc_os_task_t * cc_os_task)
{
	ASSERT_IF_FALSE(cc_os_task != NULL);

	cc_os_task->task_status = cc_shed_task_ready;

	return success;
}

cc_os_err_t cc_os_del_task_by_name (const char * name)
{
	cc_shed_tcb_t * ptr = g_curr_task;
	int name_found = 0;
	if (name != NULL)
	{
		/* code to delete node equal to name */
		ptr = g_ready_list_head;
		while(ptr->next_ready_tcb != g_ready_list_head)
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
		ptr = g_curr_task;
	}
	/* Code to handle first node */
	if (ptr == g_ready_list_head)
	{
		if (ptr->next_ready_tcb != g_ready_list_head)
		{
			/* code for more than one node */
			g_ready_list_head = ptr->next_ready_tcb;
		}
		else
		{
			/* code for only one node */
			memset(g_ready_list_head, 0, sizeof(cc_shed_tcb_t));
			g_ready_list_head = &(g_cc_os_tcb_list[0]);
			return success;
		}

	}
	ptr->next_ready_tcb->prev_ready_tcb = ptr->prev_ready_tcb;
	ptr->prev_ready_tcb->next_ready_tcb = ptr->next_ready_tcb;

#if CC_DYNAMIC == 0
	/* Static task Reset */
	ptr->task_status   = cc_shed_task_terminated;
	ptr->next_ready_tcb = NULL;
	ptr->prev_ready_tcb = NULL;
#else
	/* Dynamic Task Deletion */
	/* TODO: Need to push to Terminated Queue so that the scheduler can free the task when not running*/
#endif

	return success;
}

cc_os_err_t cc_os_pause_task_by_name (const char * name)
{
	cc_shed_tcb_t * ptr = g_curr_task;
	int name_found = 0;
	if (name != NULL)
	{
		/* code to pause node equal to name */
		ptr = g_ready_list_head;
		while(ptr->next_ready_tcb != g_ready_list_head)
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

	ptr->task_status = cc_shed_task_wait;

	return success;
}

cc_os_err_t cc_os_resume_task_by_name (const char * name)
{
	ASSERT_IF_FALSE(name != NULL);

	cc_shed_tcb_t * ptr = g_ready_list_head;
	int name_found = 0;

	/* code to resume node equal to name */
	while(ptr->next_ready_tcb != g_ready_list_head)
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

	ptr->task_status = cc_shed_task_ready;

	return success;
}

cc_os_err_t cc_os_wait_task (const size_t ticks)
{
	ASSERT_IF_FALSE(ticks > 0);

	cc_shed_tcb_t * ptr = g_ready_list_head;

	ptr->task_delay_ticks = ticks;
	ptr->task_status = cc_shed_task_wait;

	// Yield

	return success;
}

cc_os_err_t cc_os_run (void)
{
	/* OS Init code */
	while (1)
	{
		/* code to process OS */
	}

	return success;
}
