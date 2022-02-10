/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: sys/types.h
 * Description		: Data types.
 *			: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_types.h.html
 *
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _CC_POSIX_TYPES_H_

/* C standard library includes. */
#include <stdint.h>

#include <cc_posix_config.h>
#include <posix/sched.h>

/**
 * @brief Used for system times in clock ticks or CLOCKS_PER_SEC.
 *
 * Enabled/disabled by posixconfigENABLE_CLOCK_T.
 */
#if !defined( posixconfigENABLE_CLOCK_T ) || ( posixconfigENABLE_CLOCK_T == 1 )
	typedef uint32_t	clock_t;
#endif

/**
 * @brief Used for clock ID type in the clock and timer functions.
 *
 * Enabled/disabled by posixconfigENABLE_CLOCKID_T.
 */
#if !defined( posixconfigENABLE_CLOCKID_T ) || ( posixconfigENABLE_CLOCKID_T == 1 )
	typedef int		clockid_t;
#endif

/**
 * @brief Used for some file attributes.
 *
 * Enabled/disabled by posixconfigENABLE_MODE_T.
 */
#if !defined( posixconfigENABLE_MODE_T ) || ( posixconfigENABLE_MODE_T == 1 )
	typedef int		mode_t;
#endif

/**
 * @brief Used for process IDs and process group IDs.
 *
 * Enabled/disabled by posixconfigENABLE_PID_T.
 */
#if !defined( posixconfigENABLE_PID_T ) || ( posixconfigENABLE_PID_T == 1 )
	typedef int		pid_t;
#endif

/**
 * @brief Used to identify a thread attribute object.
 *
 * Enabled/disabled by posixconfigENABLE_PTHREAD_ATTR_T.
 */
#if !defined( posixconfigENABLE_PTHREAD_ATTR_T ) || ( posixconfigENABLE_PTHREAD_ATTR_T == 1 )
	typedef struct pthread_attr
	{
		int		detach_state;
		int		policy;
		sched_param_t	sched_param;
		size_t		stacksize;
	}pthread_attr_t;
#endif

/**
 * @brief Used to identify a barrier.
 *
 * Enabled/disabled by posixconfigENABLE_PTHREAD_BARRIER_T.
 */
#if !defined( posixconfigENABLE_PTHREAD_BARRIER_T ) || ( posixconfigENABLE_PTHREAD_BARRIER_T == 1 )
	typedef struct pthread_barrier
	{
		/* pthread_barrier structure place holder */
	}pthread_barrier_t;
#endif

/**
 * @brief Used to define a barrier attributes object.
 */
	typedef void 		* pthread_barrierattr_t;

/**
 * @brief Used for condition variables.
 *
 * Enabled/disabled by posixconfigENABLE_PTHREAD_COND_T.
 */
#if !defined( posixconfigENABLE_PTHREAD_COND_T ) || ( posixconfigENABLE_PTHREAD_COND_T == 1 )
	typedef  struct  pthread_cond
	{
		/* pthread_cond structure place holder */
	}pthread_cond_t;
#endif

/**
 * @brief Used to identify a condition attribute object.
 *
 * Enabled/disabled by posixconfigENABLE_PTHREAD_CONDATTR_T.
 */
#if !defined( posixconfigENABLE_PTHREAD_CONDATTR_T ) || ( posixconfigENABLE_PTHREAD_CONDATTR_T == 1 )
	typedef void		* pthread_condattr_t;
#endif

/**
 * @brief Used for mutexes.
 *
 * Enabled/disabled by posixconfigENABLE_PTHREAD_MUTEX_T.
 */
#if !defined( posixconfigENABLE_PTHREAD_MUTEX_T ) || ( posixconfigENABLE_PTHREAD_MUTEX_T == 1 )
	typedef struct pthread_mutex
	{
		/* pthread_mutex structure place holder */
	}pthread_mutex_t;
#endif

/**
 * @brief Used to identify a mutex attribute object.
 *
 * Enabled/disabled by posixconfigENABLE_PTHREAD_MUTEXATTR_T.
 */
#if !defined( posixconfigENABLE_PTHREAD_MUTEXATTR_T ) || ( posixconfigENABLE_PTHREAD_MUTEXATTR_T == 1 )
	typedef struct pthread_mutexattr
	{
		/* pthread_mutexattr structure place holder */
	}pthread_mutexattr_t;
#endif

/**
 * @brief Used to identify a thread.
 *
 * Enabled/disabled by posixconfigENABLE_PTHREAD_T.
 */
#if !defined( posixconfigENABLE_PTHREAD_T ) || ( posixconfigENABLE_PTHREAD_T == 1 )
	typedef struct pthread
	{
		/* pthread structure place holder */
	}pthread_t;
#endif

/**
 * @brief Used for a count of bytes or an error indication.
 *
 * Enabled/disabled by posixconfigENABLE_SSIZE_T.
 */
#if !defined( posixconfigENABLE_SSIZE_T ) || ( posixconfigENABLE_SSIZE_T == 1 )
	typedef size_t			ssize_t;
#endif

/**
 * @brief Used for time in seconds.
 *
 * Enabled/disabled by posixconfigENABLE_TIME_T.
 */
#if !defined( posixconfigENABLE_TIME_T ) || ( posixconfigENABLE_TIME_T == 1 )
	typedef int64_t 		time_t;
#endif

/**
 * @brief Used for timer ID returned by timer_create().
 *
 * Enabled/disabled by posixconfigENABLE_TIMER_T.
 */
#if !defined( posixconfigENABLE_TIMER_T ) || ( posixconfigENABLE_TIMER_T == 1 )
	typedef void 			* timer_t;
#endif

/**
 * @brief Used for time in microseconds.
 *
 * Enabled/disabled by posixconfigENABLE_USECONDS_T.
 */
#if !defined( posixconfigENABLE_USECONDS_T ) || ( posixconfigENABLE_USECONDS_T == 1 )
	typedef unsigned long 		useconds_t;
#endif

/**
 * @brief Used for file sizes.
 *
 * Enabled/disabled by posixconfigENABLE_OFF_T.
 */
#if !defined( posixconfigENABLE_OFF_T ) || ( posixconfigENABLE_OFF_T == 1 )
	typedef long int 		off_t;
#endif

#if( posixconfigUSE_16_BIT_TICKS == 1 )
	typedef uint16_t TickType_t;
#else
	typedef size_t TickType_t;
#endif
#define posixconfigMAX_DELAY			(TickType_t)(~0)
