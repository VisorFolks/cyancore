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
        timespec_t rqtp =
        {
                .tv_nsec = NANOSECONDS_PER_TICK * seconds,
                .tv_sec = seconds
        };
        return (unsigned)nanosleep(&rqtp, NULL);
}

int usleep( useconds_t usec )
{
        (void) usec;
        return SUCCESS;
}

int nanosleep(const timespec_t *rqtp, timespec_t *rmtp)
{
        (void) rqtp;
        (void) rmtp;
        return SUCCESS;
}
