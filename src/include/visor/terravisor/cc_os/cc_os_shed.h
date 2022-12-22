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
typedef struct cc_shed cc_sched_t;

typedef enum
{
	cc_shed_task_terminated	= 0x00,				///> Initial State
	cc_shed_task_ready,					///> Task Ready to despatch
	cc_shed_task_running,					///> Task currently running
	cc_shed_task_wait,					///> Task in wait state
	cc_shed_task_status_max = 0xff,				///> Do Nt Use
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

/**
 * @brief Prototype of scheduler algorithm function
*/
typedef void (* algo_fn)(cc_shed_tcb_t * cc_os_tcb_list);

typedef enum
{
	cc_shed_algo_round_robin	= 0x00,			///> Round Robin scheduling algorithm
	cc_shed_algo_priority_driven,				///> Priority driven Scheduling
	cc_shed_algo_max		= 0xff
}cc_shed_algo_t;

typedef struct cc_shed
{
	cc_shed_algo_t cc_selected_algo;			///> Selected Algorithm ID
	algo_fn algo_function;					///> Pointer to algorithm function
}cc_shed_t;


void cc_shed_algo_round_robin_fn(cc_shed_tcb_t * cc_os_tcb_list);
