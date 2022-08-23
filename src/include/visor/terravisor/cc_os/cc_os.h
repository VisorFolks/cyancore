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

#include "status.h"
#include "stdint.h"

#if ccosconfig_CC_OS_USE_DYNAMIC == 0
#define	CC_DYNAMIC 0
#endif

#define ASSERT_IF_FALSE(con)	if(!(con)) return error_func_inval_arg

typedef status_t cc_os_err_t;

typedef void (* task_fn)(void * args);
typedef const char c_char;

/**
 * @brief	TASK infrastructure structure
 *
 */
typedef struct cc_os_task
{
	task_fn   task_fn;
	c_char	* name;
	size_t    priority;		//>> For waited tasks
	size_t 	* stack_ptr;
	size_t    stack_len;
}cc_os_task_t;

/**
 * @brief Function to declare a static task with a dedicated stack for the task
 * @brief Usage: CC_TASK_DEF(TASK_Name, task_func_pointer, priority(int), stack_len(int));
 *
 * @note  DO NOT use space in place of TASK_Name as it would result build errors.
 *
 */
#define CC_TASK_DEF(_NAME, _fn,  _PRI, STACK_LEN){	\
static size_t _NAME##_stack[STACK_LEN];			\
static const cc_os_task_t _NAME##_task = {		\
		.task_fn = _fn,				\
		.name = #_NAME,				\
		.priority = _PRI,			\
		.stack_ptr = _NAME##_stack,		\
		.stack_len = STACK_LEN			\
	};						\
}

/**
 * @brief Function to get the instance using its name of already declared task.
 * @brief Usage: cc_os_task_t * task = &(CC_GET_TASK_INST(TASK_Name));
 *
 * @note  DO NOT use space in place of TASK_Name as it would result build errors.
 *
 */
#define CC_GET_TASK_INST(_NAME)	_NAME##_task

/**
 * @brief A Function to add a task to the scheduler
 *
 * @param cc_os_task	 pointer to the TASK_instance; use CC_GET_TASK_INST(Name) to get the Defined Task
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_add_task	(cc_os_task_t * cc_os_task);

/**
 * @brief A function to delete a task from the scheduler
 *
 * @param name
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_del_task	(const char *name);

/**
 * @brief A Function to pause the task until call resume explicitly
 *
 * @param name
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_pause_task	(const char *name);

/**
 *
 * @brief A Function to resume paused task.
 * @note  Calling this function for already non-waiting task has no effect.
 *
 * @param name
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_resume_task	(const char *name);

/**
 * @brief A Function to put the task to a waiting state and yield
 *
 * @param ticks			Number of CC_OS Ticks
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_wait_task	(const size_t ticks);

/**
 * @brief A Function to invoke the kernel
 *
 * @return cc_os_err_t
 */
cc_os_err_t cc_os_run		(void);

#endif	/* __CC_OS__ */
