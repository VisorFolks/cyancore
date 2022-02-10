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

}

int pthread_attr_getdetachstate( const pthread_attr_t * attr, int * detachstate )
{

}

int pthread_attr_getschedparam( const pthread_attr_t * attr, struct sched_param * param )
{

}

int pthread_attr_getstacksize( const pthread_attr_t * attr, size_t * stacksize )
{

}

int pthread_attr_init( pthread_attr_t * attr )
{

}

int pthread_attr_setdetachstate( pthread_attr_t * attr, int detachstate )
{

}

int pthread_attr_setschedparam( pthread_attr_t * attr, const struct sched_param * param )
{

}

int pthread_attr_setschedpolicy( pthread_attr_t * attr, int policy )
{

}

int pthread_attr_setstacksize( pthread_attr_t * attr, size_t stacksize )
{

}

int pthread_create( pthread_t * thread, const pthread_attr_t * attr, void *( *startroutine )( void * ), void * arg )
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
