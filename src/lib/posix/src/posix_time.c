/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: posix_time.c
 * Description		: This file consists of posix time related call handles
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <lib/posix/include/time.h>
#include <lib/posix/include/unistd.h>
#include <lib/posix/include/errno.h>

unsigned sleep( unsigned seconds )
{
	return (unsigned) usleep(MICROSECONDS_PER_SECOND * seconds);
}

int usleep( useconds_t usec )
{
        TODO(usec);
}

clock_t clock( void )
{

}

int clock_getcpuclockid( pid_t pid, clockid_t * clock_id )
{
        TODO(pid);
        TODO(clock_id);
        return SUCCESS;
}

int clock_getres( clockid_t clock_id, struct timespec * res )
{
        TODO(clock_id);
        TODO(res);
        return SUCCESS;
}

int clock_gettime( clockid_t clock_id, struct timespec * tp )
{
        TODO(clock_id);
        TODO(tp);
        return SUCCESS;
}

int clock_nanosleep( clockid_t clock_id,
                     int flags,
                     const struct timespec * rqtp,
                     struct timespec * rmtp )
{
        TODO(clock_id);
        TODO(flags);
        TODO(rqtp);
        TODO(rmtp);
        return SUCCESS;
}

int clock_settime( clockid_t clock_id,
                   const struct timespec * tp )
{
        TODO(clock_id);
        TODO(tp);
        return SUCCESS;
}

int nanosleep( const struct timespec * rqtp,
               struct timespec * rmtp )
{
        TODO(rqtp);
        TODO(rmtp);
        return SUCCESS;
}

int timer_create( clockid_t clock_id,
                  struct sigevent * evp,
                  timer_t * timerid )
{
        TODO(clock_id);
        TODO(evp);
        TODO(timerid);
        return SUCCESS;
}

int timer_delete( timer_t timerid )
{
        TODO(timerid);
        return SUCCESS;
}

int timer_getoverrun( timer_t timerid )
{
        TODO(timerid);
        return SUCCESS;
}

int timer_gettime( timer_t timerid,
                   struct itimerspec * value )
{
        TODO(timerid);
        TODO(value);
        return SUCCESS;
}

int timer_settime( timer_t timerid,
                   int flags,
                   const struct itimerspec * value,
                   struct itimerspec * ovalue )
{
        TODO(timerid);
        TODO(flags);
        TODO(value);
        TODO(ovalue);
        return SUCCESS;
}
