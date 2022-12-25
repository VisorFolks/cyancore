/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os.h
 * Description		: CC OS Kernel declaration
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#ifndef __CC_OS__
#define __CC_OS__

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include "status.h"
#include "stdlib.h"
#include "stdint.h"
#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/cc_os_sched.h>

/*****************************************************
 *	DEFINES
 *****************************************************/
#define CC_OS_FALSE			0
#define CC_OS_TRUE			1
#define CC_OS_DELAY_MAX			((size_t) -1)

#define	CC_OS_DYNAMIC 			ccosconfig_CC_OS_USE_DYNAMIC

#define CC_OS_ASSERT_IF_FALSE(con)	if(!(con)) return error_func_inval_arg

/*****************************************************
 *	TYPEDEFS
 *****************************************************/
typedef status_t cc_os_err_t;

typedef void * os_args;
typedef void (* task_fn)(os_args args);
typedef const char c_char;

/**
 * @brief	TASK infrastructure structure
 *
 */
typedef struct cc_os_task
{
	task_fn   task_fn;		///>> Task funcion
	os_args   args;			///>> Task Args ptr
	c_char	* name;			///>> String name of the task
	size_t    priority;		///>> For waited tasks
	size_t 	* stack_ptr;		///>> Stack pointer of the task
	size_t    stack_len;		///>> Stack lengths of the task
	cc_sched_tcb_t * task_tcb_ptr;	///>> For internal use only
}cc_os_task_t;

/*****************************************************
 *	MACROS
 *****************************************************/
/**
 * @brief Function to declare a static task with a dedicated stack for the task
 * @brief Usage: CC_TASK_DEF(TASK_Name, task_func_pointer, priority(int), stack_len(int));
 *
 * @note  DO NOT use space in place of TASK_Name as it would result build errors.
 *
 */
#define CC_TASK_DEF(_NAME, _fn,  _args, _PRI, STACK_LEN)	\
static size_t _NAME##_stack[STACK_LEN];				\
static cc_os_task_t _NAME##_task = {				\
		.args = _args,					\
		.task_fn = _fn,					\
		.name = #_NAME,					\
		.priority = _PRI,				\
		.stack_ptr = _NAME##_stack,			\
		.stack_len = STACK_LEN				\
	}							\

/**
 * @brief Function to get the instance using its name of already declared task.
 * @brief Usage: cc_os_task_t * task = &(CC_GET_TASK_INST(TASK_Name));
 *
 * @note  DO NOT use space in place of TASK_Name as it would result build errors.
 *
 */
#define CC_GET_TASK_INST(_NAME)	_NAME##_task

/*****************************************************
 *	USER FUNCTION DECLARATIONS
 *****************************************************/
/**
 * @brief A Function to add a task to the scheduler
 *
 * @param cc_os_task	 pointer to the TASK_instance; use CC_GET_TASK_INST(Name) to get the Defined Task
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_add_task(cc_os_task_t * cc_os_task);

/**
 * @brief A function to delete a task from the scheduler by instance
 *
 * @param cc_os_task	pointer to the TASK_instance; use CC_GET_TASK_INST(Name) to get the Defined Task;
 * 			Pass NULL to point to current task
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_del_task(cc_os_task_t * cc_os_task);

/**
 * @brief A Function to pause the task until call resume explicitly using its instance
 *
 * @param cc_os_task	pointer to the TASK_instance; use CC_GET_TASK_INST(Name) to get the Defined Task;
 * 			Pass NULL to point to current task
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_pause_task (cc_os_task_t * cc_os_task);

/**
 *
 * @brief A Function to resume paused task using its instance
 * @note  Calling this function for already non-waiting task has no effect.
 *
 * @param cc_os_task	pointer to the TASK_instance; use CC_GET_TASK_INST(Name) to get the Defined Task;
 * 			Pass NULL to point to current task
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_resume_task (cc_os_task_t * cc_os_task);

/**
 * @brief A Function to pause all the tasks except the current and the IDLE Task
 * @note	To resume all please use cc_os_resume_all_task() call
 *
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_pause_all_task (void);

/**
 * @brief A Function to resume all the tasks
 *
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_resume_all_task (void);

/**
 * @brief A function to set CC OS scheduler algorithm
 *
 * @return cc_os_err_t
 */
cc_os_err_t set_cc_os_sched_algo(cc_sched_algo_t sched_algo);

/**
 * @brief A Function to put the current task to a waiting state and yield
 * @note  To just Yeild set ticks to 0
 *
 * @param ticks			Number of CC_OS Ticks
 * @return None
 */
void cc_os_task_wait(const size_t ticks);

/**
 * @brief A Function to switch to next available task
 *
 * @param ticks			Number of CC_OS Ticks
 * @return None
 */
void cc_os_task_yield();

/**
 * @brief A Function to invoke the kernel
 *
 * @return cc_os_err_t
 */
void cc_os_run(void);


#endif	/* __CC_OS__ */
