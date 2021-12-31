#pragma once

#include "stdint.h"

typedef struct cc_shed_tcb cc_shed_tcb_t;

typedef enum
{
	CC_SHED_TASK_READY,
	CC_SHED_TASK_RUNNING,
	CC_SHED_TASK_PAUSED,
} cc_shed_task_status_t;

struct cc_shed_tcb
{
	int8_t 	* i8_name;
	int8_t    i8_priority;
	int32_t * i32_sp;
	cc_shed_tcb_t * next_shed_tcb;
	cc_shed_task_status_t task_status;
};
