/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: posix_pthread.c
 * Description		: This file consists of posix pthread related call handles
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <string.h>
#include <supervisor/workers.h>
#include <posix/pthread.h>
#include <posix/errno.h>
#include <posix/utils.h>

pthread_mutex_t g_pthread_mutex;
pthread_mutexattr_t g_pthread_mutex_attr;

/*********************
 * Static Functions
 ********************/
static int s_pthread_acquire_lock(void)
{
	return pthread_mutex_lock(&g_pthread_mutex);
}

static int s_pthread_release_lock(void)
{
	return pthread_mutex_unlock(&g_pthread_mutex);
}
/*********************
 * POSIX Functions
 ********************/

int pthread_attr_destroy(pthread_attr_t *attr)
{
	ASSERT_IF_FALSE(attr != NULL, int);

	memset(attr, RST_VAL, sizeof(pthread_attr_t));

	return SUCCESS;
}

int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate)
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(detachstate != NULL, int);

	*detachstate = attr->detach_state;
	return SUCCESS;
}

int pthread_attr_getschedparam(const pthread_attr_t *attr, sched_param_t *param)
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(param != NULL, int);

	memcpy(param, &(attr->sched_param), sizeof(sched_param_t));
	return SUCCESS;
}

int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize)
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(stacksize != NULL, int);

	*stacksize = attr->stacksize;
	return SUCCESS;
}

int pthread_attr_init(pthread_attr_t *attr)
{
	ASSERT_IF_FALSE(attr != NULL, int);

	memset(attr, RST_VAL, sizeof(pthread_attr_t));
	attr->stacksize = posixconfigPTHREAD_MIN_STACK_SIZE;

	return SUCCESS;
}

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate)
{
	ASSERT_IF_FALSE(attr != NULL, int);

	attr->detach_state = detachstate;
	return SUCCESS;
}

int pthread_attr_setschedparam(pthread_attr_t *attr, const sched_param_t *param)
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(param != NULL, int);

	memcpy(&(attr->sched_param), param, sizeof(sched_param_t));
	return SUCCESS;
}

int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy)
{
	ASSERT_IF_FALSE(attr != NULL, int);

	attr->policy = policy;
	return SUCCESS;
}

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(stacksize >= posixconfigPTHREAD_MIN_STACK_SIZE, int);

	attr->stacksize = stacksize;
	return SUCCESS;
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*startroutine)(void *), void *arg)
{
	sret_t pthread_sys_ret =
	{
		.status = SUCCESS
	};

	int err = SUCCESS;

	ASSERT_IF_FALSE(thread != NULL, int);
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(attr->stacksize >= posixconfigPTHREAD_MIN_STACK_SIZE, int);

	thread->attr = (pthread_attr_t *)attr;

	/* Grab resource access else return EBUSY */
	RET_ERR_IF_FALSE(s_pthread_acquire_lock() == SUCCESS, -EBUSY, int);

	super_call(scall_id_pthread_create, (call_arg_t) startroutine, (call_arg_t) arg, thread->attr->stacksize, &pthread_sys_ret);
	if (pthread_sys_ret.status != SUCCESS)
	{
		err = -EAGAIN;
	}
	else
	{
		thread->fn = startroutine;

		/* Get the PID */
		thread->pid = pthread_sys_ret.size;
	}

	/* Release resource access else return EBUSY */
	RET_ERR_IF_FALSE(s_pthread_release_lock() == SUCCESS, -EBUSY, int);

	return err;
}

int pthread_equal(pthread_t t1, pthread_t t2)
{
	return memcmp(&t1, &t2, sizeof(pthread_t));
}

void pthread_exit( const void *value_ptr _UNUSED)
{
	sret_t pthread_sys_ret =
	{
		.status = SUCCESS
	};

	/* Grab resource access else return EBUSY */
	s_pthread_acquire_lock();

	super_call(scall_id_pthread_exit, RST_VAL, RST_VAL, RST_VAL, &pthread_sys_ret);

	/* Release resource access else return EBUSY */
	s_pthread_release_lock();
}
