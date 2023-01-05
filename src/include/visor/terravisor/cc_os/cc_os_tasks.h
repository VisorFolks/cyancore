/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_task.h
 * Description		: CC OS Kernel Tasks declaration
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
/*****************************************************
 *	INCLUDES
 *****************************************************/

#include "status.h"
#include "stdlib.h"
#include "stdint.h"
#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/utils/cc_os_sched.h>

/*****************************************************
 *	TYPEDEFS
 *****************************************************/
/**
 * @brief	TASK infrastructure
 *
 */
typedef cc_sched_tcb_t * cc_os_task_t;

/*****************************************************
 *	MACROS
 *****************************************************/

/*****************************************************
 *	USER FUNCTION DECLARATIONS
 *****************************************************/
/**
 * @brief A Function to add a task to the scheduler
 *
 *
 * @param cc_os_task[out]	Pointer to the TASK_instance
 * @param name[in]		Conatant Name string provided by the user
 * @param task_func[in]		Pointer to the task function
 * @param args[in]		Pointer to the argument variable provided to the task
 * @param priority[in]		Task Priority: 1->255
 * @param stack_len[in]		Task stack length
 * @param stack_ptr[in]		Pointer to static stack for static allocation only.
 *
 * @return status_t
 */
status_t cc_os_add_task (
	cc_os_task_t * cc_os_task, const char* name,
	task_fn task_func, cc_os_args args,
	uint8_t priority,size_t stack_len,
	uintptr_t stack_ptr);

/**
 * @brief A function to delete a task from the scheduler by instance
 *
 * @param cc_os_task[in]	pointer to the TASK_instance;
 * 				Pass NULL to point to current task
 * @return status_t
 */
status_t cc_os_del_task(cc_os_task_t cc_os_task);

/**
 * @brief A Function to pause the task until call resume explicitly using its instance
 *
 * @param cc_os_task[in]	pointer to the TASK_instance;
 * 				Pass NULL to point to current task
 * @return status_t
 */
status_t cc_os_pause_task(cc_os_task_t cc_os_task);

/**
 *
 * @brief A Function to resume paused task using its instance
 * @note  Calling this function for already non-waiting task has no effect.
 *
 * @param cc_os_task[in]	pointer to the TASK_instance;
 * 				Pass NULL to point to current task
 * @return status_t
 */
status_t cc_os_resume_task(cc_os_task_t cc_os_task);

/**
 * @brief A Function to pause all the tasks except the current and the IDLE Task
 * @note	To resume all please use cc_os_resume_all_task() call
 *
 * @return status_t
 */
status_t cc_os_pause_all_task(void);

/**
 * @brief A Function to resume all the tasks
 *
 * @return status_t
 */
status_t cc_os_resume_all_task(void);

/**
 * @brief A function to set CC OS scheduler algorithm
 *
 * @param sched_algo[in]	The algorithm that needs to be selected to
 * @return status_t
 */
status_t cc_os_set_sched_algo(cc_sched_algo_t sched_algo);

/**
 * @brief Get name of current running task
 *
 * @param None
 * @return Pointer to the current task name
 */
const char * cc_os_get_curr_task_name(void);
/**
 * @brief A Function to put the current task to a waiting state and yield
 * @note  To just Yeild set ticks to 0
 *
 * @param ticks[in]		Number of CC_OS Ticks
 * @return None
 */
void cc_os_task_wait(const size_t ticks);

/**
 * @brief A Function to switch to next available task
 *
 * @return None
 */
void cc_os_task_yield(void);

/**
 * @brief A Function to invoke the kernel
 *
 * @return status_t
 */
void cc_os_run(void);
