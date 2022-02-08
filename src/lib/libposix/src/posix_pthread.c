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

int pthread_create( pthread_t * thread, const pthread_attr_t * attr, void *( *startroutine )( void * ), void * arg )
{

}

int pthread_cond_broadcast( pthread_cond_t * cond )
{

}

int pthread_cond_destroy( pthread_cond_t * cond )
{

}

int pthread_cond_init( pthread_cond_t * cond, const pthread_condattr_t * attr );
{

}

int pthread_cond_signal( pthread_cond_t * cond )
{

}

int pthread_cond_timedwait( pthread_cond_t * cond, pthread_mutex_t * mutex, const struct timespec * abstime )
{

}

int pthread_cond_wait( pthread_cond_t * cond, pthread_mutex_t * mutex )
{

}

int pthread_equal( pthread_t t1, pthread_t t2 )
{

}

void pthread_exit( void * value_ptr )
{
	
}

int pthread_getschedparam( pthread_t thread, int * policy, struct sched_param * param )
{

}

int pthread_join( pthread_t thread, void ** retval )
{

}
