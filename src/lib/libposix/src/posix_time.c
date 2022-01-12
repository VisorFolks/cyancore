/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: posix_time.c
 * Description		: This file consists of posix time related call handles
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <posix/time.h>
#include <posix/unistd.h>
#include <posix/errno.h>

unsigned sleep( unsigned seconds )
{
	return (unsigned) usleep(MICROSECONDS_PER_SECOND * seconds);
}

int usleep( useconds_t usec )
{
        (void) usec;
        return SUCCESS;
}

clock_t clock( void )
{
        return (clock_t) 0;
}

int clock_getcpuclockid( pid_t pid, clockid_t * clock_id )
{
        (void)(pid);
        (void)(clock_id);
        return SUCCESS;
}

int clock_getres( clockid_t clock_id, struct timespec * res )
{
        (void)(clock_id);
        (void)(res);
        return SUCCESS;
}

int clock_gettime( clockid_t clock_id, struct timespec * tp )
{
        (void)(clock_id);
        (void)(tp);
        return SUCCESS;
}

int clock_nanosleep( clockid_t clock_id,
                     int flags,
                     const struct timespec * rqtp,
                     struct timespec * rmtp )
{
        (void)(clock_id);
        (void)(flags);
        (void)(rqtp);
        (void)(rmtp);
        return SUCCESS;
}

int clock_settime( clockid_t clock_id,
                   const struct timespec * tp )
{
        (void)(clock_id);
        (void)(tp);
        return SUCCESS;
}

int nanosleep( const struct timespec * rqtp,
               struct timespec * rmtp )
{
        (void)(rqtp);
        (void)(rmtp);
        return SUCCESS;
}

int timer_create( clockid_t clock_id,
                  struct sigevent * evp,
                  timer_t * timerid )
{
        (void)(clock_id);
        (void)(evp);
        (void)(timerid);
        return SUCCESS;
}

int timer_delete( timer_t timerid )
{
        (void)(timerid);
        return SUCCESS;
}

int timer_getoverrun( timer_t timerid )
{
        (void)(timerid);
        return SUCCESS;
}

int timer_gettime( timer_t timerid,
                   struct itimerspec * value )
{
        (void)(timerid);
        (void)(value);
        return SUCCESS;
}

int timer_settime( timer_t timerid,
                   int flags,
                   const struct itimerspec * value,
                   struct itimerspec * ovalue )
{
        (void)(timerid);
        (void)(flags);
        (void)(value);
        (void)(ovalue);
        return SUCCESS;
}
