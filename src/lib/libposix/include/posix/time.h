/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: time.h
 * Description		: Time types
 *                  : http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/time.h.html
 *
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _CC_POSIX_TIME_H_

/* CC+POSIX includes. */
#include <posix/sys/types.h>
#include <posix/signal.h>

/**
 * @name Unit conversion constants.
 */
/**@{ */
#define MICROSECONDS_PER_SECOND    ( 1000000LL )                                   /**< Microseconds per second. */
#define NANOSECONDS_PER_SECOND     ( 1000000000LL )                                /**< Nanoseconds per second. */
#define NANOSECONDS_PER_TICK       ( NANOSECONDS_PER_SECOND / posixconfigTICK_RATE_HZ ) /**< Nanoseconds per Kernel tick. */
/**@} */

/**
 * @name Clock identifiers.
 */
/**@{ */
#define CLOCK_REALTIME     0     /**< The identifier of the system-wide clock measuring real time. */
#define CLOCK_MONOTONIC    1     /**< The identifier for the system-wide monotonic clock.*/
/**@} */

/**
 * @name A number used to convert the value returned by the clock() function into seconds.
 */
/**@{ */
#define CLOCKS_PER_SEC    ( ( clock_t ) posixconfigTICK_RATE_HZ )
/**@} */

/**
 * @name Flag indicating time is absolute.
 *
 * For functions taking timer objects, this refers to the clock associated with the timer.
 */
/**@{ */
#define TIMER_ABSTIME    0x01
/**@} */

#if !defined( posixconfigENABLE_TIMESPEC ) || ( posixconfigENABLE_TIMESPEC == 1 )

/**
 * @brief represents an elapsed time
 */
    typedef struct timespec
    {
        time_t tv_sec; /**< Seconds. */
        long tv_nsec;  /**< Nanoseconds. */
    }timespec_t;
#endif

#if !defined( posixconfigENABLE_ITIMERSPEC ) || ( posixconfigENABLE_ITIMERSPEC == 1 )

/**
 * @brief timer
 */
    typedef struct itimerspec
    {
        timespec_t it_interval; /**< Timer period. */
        timespec_t it_value;    /**< Timer expiration. */
    }itimerspec_t;
#endif

/**
 * @brief Report CPU time used.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/clock.html
 *
 * @return  The number of Kernel ticks since the scheduler
 * was started minus the ticks spent in the idle task.
 *
 * @note This function does NOT report the number of ticks spent by the calling thread.
 */
clock_t clock( void );

/**
 * @brief Access a process CPU-time clock.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_getcpuclockid.html
 *
 * @retval EPERM
 *
 * @note This function is currently unsupported.
 *
 */
int clock_getcpuclockid( pid_t pid,
                         clockid_t * clock_id );

/**
 * @brief Returns the resolution of a clock.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_getres.html
 *
 * @note clock_id is ignored
 * @note This function stores the resolution of the Kernel tick count in the object res points to.
 *
 * @retval 0 - Upon successful execution
 */
int clock_getres( clockid_t clock_id,
                  timespec_t * res );

/**
 * @brief Returns the current value for the specified clock, clock_id.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_gettime.html
 *
 * @note clock_id is ignored
 * @note  this function does not check for overflows of time_t.
 *
 * @retval 0 - Upon successful completion.
 */
int clock_gettime( clockid_t clock_id,
                   timespec_t * tp );

/**
 * @brief High resolution sleep with specifiable clock.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_nanosleep.html
 *
 * @note clock_id is ignored, as this function uses the Kernel tick count as its clock.
 * @note flags is ignored, if INCLUDE_vTaskDelayUntil is 0. i.e. the Kernel function vTaskDelayUntil isn't available.
 * @note rmtp is also ignored, as signals are not implemented.
 *
 * @retval 0 - Upon successful completion.
 * @retval EINVAL - The rqtp argument specified a nanosecond value less than zero or greater than or equal to 1000 million.
 */
int clock_nanosleep( clockid_t clock_id,
                     int flags,
                     const timespec_t * rqtp,
                     timespec_t * rmtp );

/**
 * @brief Sets the time for the specified clock.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_settime.html
 *
 * @retval -1 with errno set to EPERM.
 *
 * @note This function is currently unsupported, as Kernel does not provide a function to modify the tick count.
 */
int clock_settime( clockid_t clock_id,
                   const timespec_t * tp );

/**
 * @brief High resolution sleep.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/nanosleep.html
 *
 * @note rmtp is ignored, as signals are not implemented.
 *
 * @retval 0 - Upon successful completion.
 * @retval -1 - The rqtp argument is invalid OR the rqtp argument specified a nanosecond value less than zero or greater than or equal to 1000 million.
 *
 */
int nanosleep( const timespec_t * rqtp,
               const timespec_t * rmtp );

/**
 * @brief Create a per-process timer.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/timer_create.html
 *
 * @note clock_id is ignored, as this function used the Kernel tick count as its clock.
 * @note evp.sigev_notify must be set to SIGEV_THREAD, since signals are currently not supported.
 *
 * @retval 0 - Upon successful completion, with location referenced by timerid updated.
 * @retval -1 - If an error occurs. errno is also set.
 *
 * @sideeffect Possible errno values
 * <br>
 * ENOTSUP - If evp is NULL OR evp->sigen_notify == SIGEV_SIGNAL.
 * <br>
 * EAGAIN - The system lacks sufficient signal queuing resources to honor the request.
 */
int timer_create( clockid_t clockid,
                  struct sigevent * evp,
                  timer_t * timerid );

/**
 * @brief Delete a per-process timer.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/timer_delete.html
 *
 * @retval 0 - Upon successful completion.
 */
int timer_delete( timer_t timerid );

/**
 * @brief Get the timer overrun count.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/timer_getoverrun.html
 *
 * @retval 0 - Always return 0, since signals are not supported.
 */
int timer_getoverrun( timer_t timerid );

/**
 * @brief Get the amount of time until the timer expires.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/timer_gettime.html
 *
 * @retval 0 - Upon successful completion.
 */
int timer_gettime( timer_t timerid,
                   itimerspec_t * value );

/**
 * @brief Set the time until the next expiration of the timer.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/timer_settime.html
 *
 * @retval 0 - Upon successful completion.
 * @retval -1 - An error occurred, errno is also set.
 *
 * @sideeffect Possible errno values
 * <br>
 * EINVAL - A value structure specified a nanosecond value less than zero or greater than or equal to 1000 million,
 * AND the it_value member of that structure did not specify zero seconds and nanoseconds.
 */
int timer_settime( timer_t timerid,
                   int flags,
                   const itimerspec_t * value,
                   itimerspec_t * ovalue );
