#include <stdint.h>
#include <string.h>
#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/cc_os.h>
#include <terravisor/cc_os/cc_shed.h>

extern cc_shed_tcb_t * g_list_head;
extern cc_shed_tcb_t g_cc_os_tcb_list[];
extern cc_shed_tcb_t * g_curr_task;

cc_os_err_t cc_os_add_task (cc_os_task_t * cc_os_task)
{
	ASSERT_IF_FALSE(cc_os_task != NULL);
	ASSERT_IF_FALSE(cc_os_task->name != NULL);
	ASSERT_IF_FALSE(cc_os_task->stack_ptr != NULL);
	ASSERT_IF_FALSE(cc_os_task->task_fn != NULL);
	ASSERT_IF_FALSE(cc_os_task->stack_len != 0);

	cc_shed_tcb_t * ptr = g_list_head;

	if ((ptr->next_shed_tcb == NULL )&& (ptr->prev_shed_tcb == NULL))
	{
		ptr->next_shed_tcb = ptr->prev_shed_tcb = g_list_head;
	}

	else
	{
		for (size_t i = 0; i < CC_OS_MAX_THREAD; i++)
		{
			/* Get an available node from global tcb list */
			if (g_cc_os_tcb_list[i].task_status == cc_shed_task_terminated)
			{
				ptr = &(g_cc_os_tcb_list[i]);
				break;
			}
		}
		if (ptr != g_list_head)
		{
			/* Insert node at last */
			ptr->next_shed_tcb = g_list_head;
			g_list_head->prev_shed_tcb = ptr;
			ptr->prev_shed_tcb = g_list_head->prev_shed_tcb;
			g_list_head->prev_shed_tcb->next_shed_tcb = ptr;
		}
		else
		{
			return error_os_task_overfow;
		}

	}
	/* Fill tcb details */
	memcpy(ptr->name, cc_os_task->name, CC_OS_TASK_NAME_LEN);
	ptr->stack_ptr 	 = cc_os_task->stack_ptr;
	ptr->priority 	 = cc_os_task->priority;
	ptr->task_status = cc_shed_task_ready;

	return success;
}

cc_os_err_t cc_os_del_task (char * name)
{
	cc_shed_tcb_t * ptr = g_curr_task;
	int name_found = 0;
	if (name != NULL)
	{
		/* code to delete node equal to name */
		ptr = g_list_head;
		while(ptr->next_shed_tcb != g_list_head)
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

	/* Code to handle first node */
	if (ptr == g_list_head)
	{
		if (ptr->next_shed_tcb != g_list_head)
		{
			/* code for more than one node */
			g_list_head = ptr->next_shed_tcb;
		}
		else
		{
			/* code for only one node */
			memset(g_list_head, 0, sizeof(cc_shed_tcb_t));
			g_list_head = &(g_cc_os_tcb_list[0]);
			return success;
		}

	}

	ptr->next_shed_tcb->prev_shed_tcb = ptr->prev_shed_tcb;
	ptr->prev_shed_tcb->next_shed_tcb = ptr->next_shed_tcb;
	ptr->task_status   = cc_shed_task_terminated;
	ptr->next_shed_tcb = NULL;
	ptr->prev_shed_tcb = NULL;

	return success;
}

cc_os_err_t cc_os_pause_task (char * name)
{
	cc_shed_tcb_t * ptr = g_curr_task;
	int name_found = 0;
	if (name != NULL)
	{
		/* code to pause node equal to name */
		ptr = g_list_head;
		while(ptr->next_shed_tcb != g_list_head)
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

	ptr->task_status = cc_shed_task_paused;

	return success;
}

cc_os_err_t cc_os_resume_task (char * name)
{
	ASSERT_IF_FALSE(name != NULL);

	cc_shed_tcb_t * ptr = g_list_head;
	int name_found = 0;

	/* code to resume node equal to name */
	while(ptr->next_shed_tcb != g_list_head)
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

cc_os_err_t cc_os_wait_task (size_t ticks _UNUSED)
{
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
