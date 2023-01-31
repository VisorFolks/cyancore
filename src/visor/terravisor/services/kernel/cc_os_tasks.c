/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_tasks.c
 * Description		: CC OS Kernel tasks related definations definations
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <arch.h>
#include <terravisor/cc_os/cc_os.h>

/*****************************************************
 *	DEFINES
 *****************************************************/
#define CC_OS_PRIORITY_MAX 255

/*****************************************************
 *	INTERNAL EXTERNS FUNCTIONS
 *****************************************************/
extern status_t _cc_os_sched_insert_after(cc_sched_tcb_t **ptr, cc_sched_tcb_t *new_node, uint8_t link_type);
extern status_t _cc_os_sched_insert_before(cc_sched_tcb_t **ptr, cc_sched_tcb_t *new_node, uint8_t link_type);
extern void _cc_sched_send_to_wait(cc_sched_ctrl_t *sched_ctrl, cc_sched_tcb_t *ptr, const size_t ticks);
extern void _cc_sched_send_to_pause(cc_sched_ctrl_t * sched_ctrl, cc_sched_tcb_t * ptr);
extern void _cc_sched_send_to_resume(cc_sched_ctrl_t *sched_ctrl, cc_sched_tcb_t *ptr);
extern void _cc_sched_send_back_of_task_prio(cc_sched_tcb_t *node_ptr);
extern void _cc_os_scheduler_despatch(void);
extern void _cc_os_pre_sched(cc_os_args args);
/*****************************************************
 *	GLOBAL EXTERNS VARIABLES
 *****************************************************/
extern void _cc_os_idle_task_fn(cc_os_args args);
extern cc_sched_t g_cc_sched_list[];
extern cc_sched_ctrl_t g_sched_ctrl;

/*****************************************************
 *	GLOBAL DECLARATIONS
 *****************************************************/
#if CC_OS_DYNAMIC == false
extern cc_sched_tcb_t g_cc_os_tcb_list[];
#else
extern cc_sched_tcb_t *g_cc_os_tcb_list;
#endif

#if CC_OS_DYNAMIC == false
uint8_t _cc_os_stack[CC_OS_IDLE_TASK_STACK_LEN];
#else
uint8_t *_cc_os_stack = CC_OS_NULL_PTR;
#endif
cc_os_task_t cc_os_idle_task;
/*****************************************************
 *	STATIC VARIABLES
 *****************************************************/
static uint16_t __cc_os_task_id_gen = false;
/*****************************************************
 *	STATIC FUNCTION DEFINATIONS
 *****************************************************/
static void __cc_init_scheduler(void)
{
	g_sched_ctrl.cb_hooks_reg.pre_sched = &_cc_os_pre_sched;
	return;
}

static uint16_t __cc_os_task_id_generate()
{
	__cc_os_task_id_gen++;
	return __cc_os_task_id_gen;
}

static cc_sched_tcb_t * __cc_os_get_tcb_using_task_id(const uintptr_t task_id)
{
	cc_sched_tcb_t * ptr = g_sched_ctrl.ready_list_head;
	bool _is_id_found = false;
	while (ptr->ready_link.next != g_sched_ctrl.ready_list_head)
	{
		if (ptr->task_id == task_id)
		{
			_is_id_found = true;
			break;
		}
		ptr = ptr->ready_link.next;
	}
	if (_is_id_found == false)
	{
		ptr = CC_OS_NULL_PTR;
	}
	return ptr;
}

static status_t __cc_os_set_task_flag(cc_sched_tcb_t* cc_os_task, cc_task_flag_t task_flag, bool en)
{
	CC_OS_ASSERT_IF_FALSE( cc_os_task != CC_OS_NULL_PTR);

	if (en)
	{
		cc_os_task->task_flags |= (uint8_t)task_flag;
	}
	else
	{
		cc_os_task->task_flags &= (uint8_t)~task_flag;
	}
	return success;
}

static bool __cc_os_is_task_flag(const cc_sched_tcb_t *cc_os_task, cc_task_flag_t task_flag)
{
	if (cc_os_task != CC_OS_NULL_PTR)
	{
		return (cc_os_task->task_flags & task_flag) == false;
	}

	return false;
}

/*****************************************************
 *	USER FUNCTION DEFINATIONS
 *****************************************************/
status_t cc_os_add_task(
    cc_os_task_t *cc_os_task,
    const char *name,
    task_fn_t task_func,
    cc_os_args args,
    uint8_t priority,
    size_t stack_len,
#if CC_OS_DYNAMIC
    uintptr_t stack_ptr _UNUSED
#else
    uintptr_t stack_ptr
#endif /* CC_OS_DYNAMIC */
)
{
	CC_OS_ASSERT_IF_FALSE(*cc_os_task == (uintptr_t)CC_OS_NULL_PTR);
	CC_OS_ASSERT_IF_FALSE(name != CC_OS_NULL_PTR);
#if CC_OS_DYNAMIC == false
	CC_OS_ASSERT_IF_FALSE(stack_ptr != (uintptr_t)CC_OS_NULL_PTR);
#endif
	CC_OS_ASSERT_IF_FALSE(task_func != CC_OS_NULL_PTR);
	CC_OS_ASSERT_IF_FALSE(stack_len != false);
	CC_OS_ASSERT_IF_FALSE(priority >= CC_OS_IDLE_TASK_PRIORITY);
	CC_OS_ASSERT_IF_FALSE(priority < CC_OS_PRIORITY_MAX);

	cc_os_pause_all_task();

	cc_sched_tcb_t *ptr = CC_OS_NULL_PTR;

#if CC_OS_DYNAMIC == false
	/* Static Task Allocation */
	for (size_t i = false; i < CC_OS_MAX_THREAD; i++)
	{
		/* Get an available node from global tcb list */
		if (g_cc_os_tcb_list[i].task_status == cc_sched_task_status_exit)
		{
			ptr = &(g_cc_os_tcb_list[i]);
			break;
		}
	}
	if (ptr != g_sched_ctrl.ready_list_head)
	{
		ptr->stack_ptr = stack_ptr;
#else
	/* Dynamic Task Declaration */
	ptr = (cc_sched_tcb_t *)cc_os_malloc(sizeof(cc_sched_tcb_t));
	if (ptr != CC_OS_NULL_PTR)
	{
		ptr->stack_ptr = (uintptr_t)malloc(stack_len);
		if (ptr->stack_ptr == (uintptr_t)CC_OS_NULL_PTR)
		{
			cc_os_resume_all_task();
			return error_memory_low;
		}
#endif /* CC_OS_DYNAMIC */
	}
	else
	{
		cc_os_resume_all_task();
		return error_memory_low;
	}
	/* Fill tcb details */
	ptr->name = name;
	ptr->priority = priority;
	ptr->task_func = task_func;
	ptr->args_ptr = (uintptr_t)args;
#if CC_OS_ANTI_DEADLOCK
	ptr->task_wd_ticks = SIZE_MAX;
#endif /* CC_OS_ANTI_DEADLOCK */
	if (g_sched_ctrl.ready_list_head == CC_OS_NULL_PTR)
	{
		ptr->ready_link.next = ptr->ready_link.prev = g_sched_ctrl.ready_list_head = ptr;
	}
	/* Insert Tasks in assending order of its priority */
	_cc_sched_send_back_of_task_prio(ptr);
	ptr->task_status = cc_sched_task_status_ready;
	ptr->task_id = __cc_os_task_id_generate();
	*cc_os_task = ptr->task_id;
	cc_os_resume_all_task();
	return success;
}

status_t cc_os_del_task(cc_os_task_t cc_os_task)
{
	cc_sched_tcb_t * ptr = __cc_os_get_tcb_using_task_id(cc_os_task);

	if (ptr == CC_OS_NULL_PTR)
	{
		ptr = g_sched_ctrl.curr_task;
	}
	CC_OS_ASSERT_IF_FALSE(ptr->task_func != &_cc_os_idle_task_fn);
	/* Code to handle first node */
	if (ptr == g_sched_ctrl.ready_list_head)
	{
		/* IDLE Task can not be deleted */
		return error_os_invalid_op;
	}
	ptr->task_status = cc_sched_task_status_exit;

	if (ptr == g_sched_ctrl.curr_task)
	{
		cc_os_task_yield(); /* Yeild */
	}

	return success;
}

status_t cc_os_pause_task(cc_os_task_t cc_os_task)
{
	cc_sched_tcb_t *ptr = __cc_os_get_tcb_using_task_id(cc_os_task);
	if (ptr == CC_OS_NULL_PTR)
	{
		ptr = g_sched_ctrl.curr_task;
	}

	_cc_sched_send_to_pause(&g_sched_ctrl, ptr);

	return success;
}

status_t cc_os_pause_all_task(void)
{
	cc_sched_tcb_t *ptr = g_sched_ctrl.ready_list_head;
	if(ptr != CC_OS_NULL_PTR)
	{
		while (true)
		{
			if (ptr == g_sched_ctrl.curr_task)
			{
				/* Do not pause the current task */
				continue;
			}

			_cc_sched_send_to_pause(&g_sched_ctrl, ptr);
			ptr = ptr->ready_link.next;

			if(ptr == g_sched_ctrl.ready_list_head)
			{
				break;
			}
		}
	}

	return success;
}

status_t cc_os_resume_all_task(void)
{
	cc_sched_tcb_t *ptr = g_sched_ctrl.ready_list_head;
	if (ptr != CC_OS_NULL_PTR)
	{
		while (true)
		{
			ptr = ptr->ready_link.next;
			_cc_sched_send_to_resume(&g_sched_ctrl, ptr);
			if (ptr == g_sched_ctrl.ready_list_head)
			{
				break;
			}
		}
	}
	else
	{
		return error_os_invalid_op;
	}

	return success;
}

status_t cc_os_resume_task(cc_os_task_t cc_os_task)
{
	cc_sched_tcb_t *ptr = __cc_os_get_tcb_using_task_id(cc_os_task);
	CC_OS_ASSERT_IF_FALSE(ptr != CC_OS_NULL_PTR);

	if (ptr->task_status != cc_sched_task_status_pause)
	{
		_cc_sched_send_to_resume(&g_sched_ctrl, ptr);
	}
	else
	{
		return error_os_invalid_op;
	}
	return success;
}

status_t cc_os_set_sched_algo(cc_sched_algo_t sched_algo)
{
	CC_OS_ASSERT_IF_FALSE(sched_algo != cc_sched_algo_max);

	g_sched_ctrl.selected_sched = &(g_cc_sched_list[sched_algo]);

	return success;
}

status_t cc_os_task_anti_deadlock_enable_and_feed(size_t task_wd_ticks _UNUSED)
{
#if CC_OS_ANTI_DEADLOCK
	CC_OS_ASSERT_IF_FALSE((task_wd_ticks > false) && (task_wd_ticks < SIZE_MAX));

	cc_sched_tcb_t *ptr = g_sched_ctrl.curr_task;
	if (__cc_os_is_task_flag(ptr, cc_task_flag_set_anti_deadlock))
	{
		__cc_os_set_task_flag(ptr, cc_task_flag_set_anti_deadlock, true);
	}

	ptr->task_wd_ticks = task_wd_ticks;
	return success;
#else
	cc_sched_tcb_t *ptr = g_sched_ctrl.curr_task;
	if (__cc_os_is_task_flag(ptr, cc_task_flag_set_anti_deadlock))
	{
		__cc_os_set_task_flag(ptr, cc_task_flag_set_anti_deadlock, false);
	}
	return error_func_inval;
#endif /* CC_OS_ANTI_DEADLOCK */
}

status_t cc_os_task_anti_deadlock_disable(void)
{
	cc_sched_tcb_t *ptr = g_sched_ctrl.curr_task;

	if (__cc_os_is_task_flag(ptr, cc_task_flag_set_anti_deadlock))
	{
		__cc_os_set_task_flag(ptr, cc_task_flag_set_anti_deadlock, false);
	}

#if CC_OS_ANTI_DEADLOCK
	ptr->task_wd_ticks = SIZE_MAX;
	return success;
#else
	return error_func_inval;
#endif /* CC_OS_ANTI_DEADLOCK */
}
status_t cc_os_set_callback(const cc_sched_cb_t cb_type, const cc_cb_hook_t cb_func _UNUSED)
{
	status_t ret = success;
	switch (cb_type)
	{
	case cc_sched_cb_power_post_sleep:
#if CC_OS_POWER_SAVE_EN
		g_sched_ctrl.cb_hooks_reg.post_sleep_cb = cb_func;
		break;
#endif
	case cc_sched_cb_power_pre_sleep:
#if CC_OS_POWER_SAVE_EN
		g_sched_ctrl.cb_hooks_reg.pre_sleep_cb = cb_func;
		break;
#endif
	case cc_sched_cb_power_sleep:
#if CC_OS_POWER_SAVE_EN
		g_sched_ctrl.cb_hooks_reg.power_sleep = cb_func;
		break;
#endif
	case cc_sched_cb_deadlock_notify:
#if CC_OS_ANTI_DEADLOCK
		g_sched_ctrl.cb_hooks_reg.deadlock_notify = cb_func;
		break;
#endif
	case cc_sched_cb_max:
		ret = error_func_inval;
		break;
	}
	return ret;
}

const char *cc_os_get_curr_task_name(void)
{
	return g_sched_ctrl.curr_task->name;
}

const char *cc_os_get_task_name(cc_os_task_t cc_os_task)
{
	const cc_sched_tcb_t *ptr = __cc_os_get_tcb_using_task_id(cc_os_task);
	if(ptr != CC_OS_NULL_PTR)
	{
		return ptr->name;
	}
	return CC_OS_NULL_PTR;
}

void cc_os_task_wait(const size_t ticks)
{
	cc_sched_tcb_t *ptr = g_sched_ctrl.curr_task;

	if (ticks > false)
	{
		_cc_sched_send_to_wait(&g_sched_ctrl, ptr, ticks);
	}

	cc_os_task_yield();
}

void cc_os_task_yield()
{
	_cc_os_scheduler_despatch();
	return;
}

void cc_os_run(void)
{
	/* OS Init code */
	/* Initialise IDLE Task */
	cc_os_add_task(&cc_os_idle_task,
		       CC_OS_IDLE_TASK_NAME,
		       &_cc_os_idle_task_fn,
		       &g_sched_ctrl,
		       CC_OS_IDLE_TASK_PRIORITY,
		       CC_OS_IDLE_TASK_STACK_LEN,
		       (uintptr_t)_cc_os_stack);

	/* Initialise scheduler */
	__cc_init_scheduler();
	cc_os_task_yield(); /* Yeild */
	while (true)
	{
		/* Code shall not reach here */
		arch_wfi();
	}
}
