#ifndef __CC_OS__
#define __CC_OS__

#include "status.h"
#include "stdint.h"

#define ASSERT_IF_FALSE(con)	if(!(con)){return error_func_inval_arg;}

typedef status_t cc_os_err_t;

typedef void (* task_fn)(void * args);

typedef struct cc_os_task
{
	task_fn   task_fn;
	char	* name;
	size_t    priority;		//>> For waited tasks
	void 	* stack_ptr;
	size_t    stack_len;
}cc_os_task_t;

cc_os_err_t cc_os_add_task	(cc_os_task_t * cc_os_task);
cc_os_err_t cc_os_del_task	(char * name);
cc_os_err_t cc_os_pause_task	(char * name);
cc_os_err_t cc_os_resume_task	(char * name);
cc_os_err_t cc_os_wait_task	(size_t ticks);
cc_os_err_t cc_os_run		(void);

#endif	/* __CC_OS__ */
