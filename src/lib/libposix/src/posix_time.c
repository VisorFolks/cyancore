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
