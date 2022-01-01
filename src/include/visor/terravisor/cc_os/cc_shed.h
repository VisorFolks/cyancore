#pragma once

#include "stdint.h"

typedef struct cc_shed_tcb cc_shed_tcb_t;

typedef enum
{
	cc_shed_task_terminated,
	cc_shed_task_ready,
	cc_shed_task_running,
	cc_shed_task_paused,
} cc_shed_task_status_t;

struct cc_shed_tcb
{
	char 	  name [CC_OS_TASK_NAME_LEN];
	size_t    priority;
	void    * stack_ptr;
	cc_shed_tcb_t * prev_shed_tcb;
	cc_shed_tcb_t * next_shed_tcb;
	cc_shed_task_status_t task_status;
};
