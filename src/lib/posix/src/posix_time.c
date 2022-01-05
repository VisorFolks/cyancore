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

unsigned sleep( unsigned seconds )
{
	return (unsigned) usleep(MICROSECONDS_PER_SECOND * seconds);
}

int usleep( useconds_t usec )
{

}

clock_t clock( void )
{

}

int clock_getcpuclockid( pid_t pid, clockid_t * clock_id )
{

}

int clock_getres( clockid_t clock_id, struct timespec * res )
{

}

int clock_gettime( clockid_t clock_id, struct timespec * tp )
{

}

int clock_nanosleep( clockid_t clock_id,
                     int flags,
                     const struct timespec * rqtp,
                     struct timespec * rmtp )
{

}

int clock_settime( clockid_t clock_id,
                   const struct timespec * tp )
{

}

int nanosleep( const struct timespec * rqtp,
               struct timespec * rmtp )
{

}

int timer_create( clockid_t clockid,
                  struct sigevent * evp,
                  timer_t * timerid )
{

}

int timer_delete( timer_t timerid )
{

}

int timer_getoverrun( timer_t timerid )
{

}

int timer_gettime( timer_t timerid,
                   struct itimerspec * value )
{

}

int timer_settime( timer_t timerid,
                   int flags,
                   const struct itimerspec * value,
                   struct itimerspec * ovalue )
{

}
