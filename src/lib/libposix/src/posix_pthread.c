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

/*********************
 * Static Functions
 ********************/
/*********************
 * POSIX Functions
 ********************/

int pthread_attr_destroy( pthread_attr_t * attr )
{
	ASSERT_IF_FALSE(attr != NULL, int);

	memset(attr, RST_VAL, sizeof(pthread_attr_t));

	return SUCCESS;
}

int pthread_attr_getdetachstate( const pthread_attr_t * attr, int * detachstate )
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(detachstate != NULL, int);

	*detachstate = attr->detach_state;
	return SUCCESS;
}

int pthread_attr_getschedparam( const pthread_attr_t * attr, sched_param_t * param )
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(param != NULL, int);

	memcpy(param, &(attr->sched_param), sizeof(sched_param_t));
	return SUCCESS;
}

int pthread_attr_getstacksize( const pthread_attr_t * attr , size_t * stacksize )
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(stacksize != NULL, int);

	*stacksize = attr->stacksize;
	return SUCCESS;
}

int pthread_attr_init( pthread_attr_t * attr )
{
	ASSERT_IF_FALSE(attr != NULL, int);

	memset(attr, RST_VAL, sizeof(pthread_attr_t));
	attr->stacksize = posixconfigPTHREAD_MIN_STACK_SIZE;

	return SUCCESS;
}

int pthread_attr_setdetachstate( pthread_attr_t * attr, int detachstate )
{
	ASSERT_IF_FALSE(attr != NULL, int);

	attr->detach_state = detachstate;
	return SUCCESS;
}

int pthread_attr_setschedparam( pthread_attr_t * attr, const sched_param_t * param )
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(param != NULL, int);

	memcpy(&(attr->sched_param), param, sizeof(sched_param_t));
	return SUCCESS;
}

int pthread_attr_setschedpolicy( pthread_attr_t * attr, int policy)
{
	ASSERT_IF_FALSE(attr != NULL, int);

	attr->policy = policy;
	return SUCCESS;
}

int pthread_attr_setstacksize( pthread_attr_t * attr, size_t stacksize)
{
	ASSERT_IF_FALSE(attr != NULL, int);
	ASSERT_IF_FALSE(stacksize >= posixconfigPTHREAD_MIN_STACK_SIZE, int);

	attr->stacksize = stacksize;
	return SUCCESS;
}
