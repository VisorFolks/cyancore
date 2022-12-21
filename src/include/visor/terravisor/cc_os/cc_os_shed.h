/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_shed.h
 * Description		: CC OS Kernel scheduler declaration
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include "stdint.h"

typedef struct cc_shed_tcb cc_shed_tcb_t;

typedef enum
{
	cc_shed_task_terminated,				///> Initial State
	cc_shed_task_ready,					///> Task Ready to despatch
	cc_shed_task_running,					///> Task currently running
	cc_shed_task_wait,					///> Task in wait state
} cc_shed_task_status_t;

struct cc_shed_tcb
{
	char 	  name [ccosconfig_CC_OS_TASK_NAME_LEN];	///> Name of the Current Task
	size_t    priority;					///> Priority of the task
	void    * stack_ptr;					///> Stack Pointer
	size_t 	  task_delay_ticks;				///> Time delay in ticks
	cc_shed_tcb_t * prev_ready_tcb;				///> Previous task pointer
	cc_shed_tcb_t * next_ready_tcb;				///> Next task pointer
	cc_shed_task_status_t task_status;			///> Current state of the task
};
