#ifndef __CC_OS__
#define __CC_OS__

#include "stdint.h"

typedef enum cc_os_err
{
	CC_OS_SUCCESS,
	CC_OS_FAIL
}cc_os_err_t;

typedef void (* task_fn)(void * args);

typedef struct cc_os_task
{
	task_fn   task_fn;
	int8_t	* i8_name;
	int8_t    i8_priority;		//>> For waited tasks
	int32_t * i32_stack_ptr;
	size_t	  s_stack_len;
}cc_os_task_t;

cc_os_err_t cc_os_add_task	(cc_os_task_t * cc_os_task);
cc_os_err_t cc_os_del_task	(int8_t * i8_name);
cc_os_err_t cc_os_pause_task	(int8_t * i8_name);
cc_os_err_t cc_os_resume_task	(int8_t * i8_name);
cc_os_err_t cc_os_wait_task	(uint16_t ticks);
cc_os_err_t cc_os_run		(void);

#endif	/* __CC_OS__ */
