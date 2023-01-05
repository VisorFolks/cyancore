/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_sched.h
 * Description		: CC OS Kernel scheduler declaration
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <status.h>

/*****************************************************
 *	DEFINES
 *****************************************************/
#define CC_OS_FALSE			0
#define CC_OS_TRUE			1
#define CC_OS_NULL_PTR			NULL
#define CC_OS_DELAY_MAX			((size_t) -1)

#define	CC_OS_DYNAMIC 			CC_OS_USE_DYNAMIC

#define CC_OS_ASSERT_IF_FALSE(con)	RET_ON_FAIL(con, error_func_inval_arg)

/*****************************************************
 *	TYPEDEFS
 *****************************************************/
typedef struct cc_sched_tcb cc_sched_tcb_t;
typedef struct cc_sched cc_sched_t;
typedef const char c_char;

typedef enum
{
	cc_sched_task_status_exit	= 0x00,			///> Initial State
	cc_sched_task_status_running	= 0x01,			///> Task currently running
	cc_sched_task_status_ready	= 0x02,			///> Task Ready to despatch
	cc_sched_task_status_wait	= 0x03,			///> Task in wait state
	cc_sched_task_status_max 	= 0xff,			///> Do Nt Use
} cc_sched_task_status_t;

typedef struct link
{
	cc_sched_tcb_t * prev;
	cc_sched_tcb_t * next;
}link_t;

typedef struct wres
{
	uintptr_t wait_on_resource;				///> Resource on hich the task is waiting on
	size_t 	  task_delay_ticks;				///> Time delay in ticks
}wres_t;

struct cc_sched_tcb
{
	c_char  * name;						///> Name of the Current Task
	uint8_t   priority;					///> Priority of the task
	uintptr_t stack_ptr;					///> Stack Pointer
	wres_t	  wait_res;					///> Wait Task resource
	link_t	  ready_link;					///> Ready Linked List Pointers
	link_t    wait_link;					///> Wait Linked List Pointers
	cc_sched_task_status_t task_status;			///> Current state of the task
};

typedef struct cc_sched_ctrl
{
	cc_sched_tcb_t 	* ready_list_head;
	cc_sched_tcb_t 	* curr_task;
	cc_sched_tcb_t 	* wait_list_head;
	cc_sched_tcb_t 	* task_max_prio;
	cc_sched_t 	* selected_sched;
}cc_sched_ctrl_t;

/**
 * @brief Prototype of scheduler algorithm function
 */
typedef void (* algo_fn)(cc_sched_ctrl_t * sched_ctrl);

typedef enum
{
	cc_sched_algo_round_robin	= 0x00,			///> Round Robin scheduling algorithm
	cc_sched_algo_priority_driven	= 0x01,			///> Priority driven Scheduling
	cc_sched_algo_max		= 0xff
}cc_sched_algo_t;

typedef struct cc_sched
{
	cc_sched_algo_t cc_selected_algo;			///> Selected Algorithm ID
	algo_fn algo_function;					///> Pointer to algorithm function
}cc_sched_t;
