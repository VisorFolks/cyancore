/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: posix_utils.c
 * Description		: This file consists of posix utils call handles
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <supervisor/workers.h>
#include <posix/errno.h>
#include <posix/utils.h>
#include <posix/time.h>

size_t UTILS_strnlen( const char * const pcString, size_t xMaxLength )
{
	size_t len = 0;
	if (pcString != NULL)
	{
		while((len < xMaxLength) && (pcString[len] != '\0'))
		{
			len++;
		}
	}

	return len;
}
int UTILS_AbsoluteTimespecToDeltaTicks( const struct timespec * const pxAbsoluteTime,
					const struct timespec * const pxCurrentTime,
					TickType_t * const pxResult )
{
	int err_status = 0;
	struct timespec time_diff = { 0 };

	/* Check parameters. */
	if( ( pxAbsoluteTime == NULL ) || ( pxCurrentTime == NULL ) || ( pxResult == NULL ) )
	{
		err_status = -EINVAL;
	}

	/* Calculate the difference between the current time and absolute time. */
	if( err_status == 0 )
	{
		err_status = UTILS_TimespecSubtract( pxAbsoluteTime, pxCurrentTime, &time_diff );

		if( err_status == 1 )
		{
			/* pxAbsoluteTime was in the past. */
			err_status = -ETIMEDOUT;
		}
		else if( err_status == -1 )
		{
			/* error */
			err_status = -EINVAL;
		}
	}

	/* Convert the time difference to ticks. */
	if( err_status == 0 )
	{
		err_status = UTILS_TimespecToTicks( &time_diff, pxResult );
	}

	return err_status;
}

int UTILS_TimespecToTicks( const struct timespec * const pxTimespec,
			TickType_t * const pxResult )
{
	int err_staus = 0;
	int64_t total_ticks;
	long nano_secs;

	/* Check parameters. */
	if( ( pxTimespec == NULL ) || ( pxResult == NULL ) )
	{
		err_staus = -EINVAL;
	}
	else if( ( err_staus == 0 ) && ( UTILS_ValidateTimespec( pxTimespec ) == false ) )
	{
		err_staus = -EINVAL;
	}

	if( err_staus == 0 )
	{
		/* Convert timespec.tv_sec to ticks. */
		total_ticks = ( int64_t ) posixconfigTICK_RATE_HZ * ( pxTimespec->tv_sec );

		/* Convert timespec.tv_nsec to ticks. This value does not have to be checked
		 * for overflow because a valid timespec has 0 <= tv_nsec < 1000000000 and
		 * NANOSECONDS_PER_TICK > 1. */
		nano_secs = pxTimespec->tv_nsec / ( long ) NANOSECONDS_PER_TICK +	  		  /* Whole nanoseconds. */
			( long ) ( pxTimespec->tv_nsec % ( long ) NANOSECONDS_PER_TICK != 0 ); /* Add 1 to round up if needed. */

		/* Add the nanoseconds to the total ticks. */
		total_ticks += ( int64_t ) nano_secs;

		/* Check for overflow */
		if( total_ticks < 0 )
		{
			err_staus = -EINVAL;
		}
		else
		{
			/* check if TickType_t is 32 bit or 64 bit */
			uint32_t ulTickTypeSize = sizeof( TickType_t );

			/* check for downcast overflow */
			if( ulTickTypeSize == sizeof( uint32_t ) )
			{
				if( total_ticks > UINT_MAX )
				{
					err_staus = -EINVAL;
				}
			}
		}

		/* Write result. */
		*pxResult = ( TickType_t ) total_ticks;
	}

	return err_staus;
}

void UTILS_NanosecondsToTimespec( int64_t llSource,
				struct timespec * const pxDestination )
{
	long carry_sec;

	/* Convert to timespec. */
	pxDestination->tv_sec = ( time_t ) ( llSource / NANOSECONDS_PER_SECOND );
	pxDestination->tv_nsec = ( long ) ( llSource % NANOSECONDS_PER_SECOND );

	/* Subtract from tv_sec if tv_nsec < 0. */
	if( pxDestination->tv_nsec < 0L )
	{
		/* Compute the number of seconds to carry. */
		carry_sec = ( pxDestination->tv_nsec / ( long ) NANOSECONDS_PER_SECOND ) + 1L;

		pxDestination->tv_sec -= ( time_t ) ( carry_sec );
		pxDestination->tv_nsec += carry_sec * ( long ) NANOSECONDS_PER_SECOND;
	}
}

int UTILS_TimespecAdd( 	const struct timespec * const x,
			const struct timespec * const y,
			struct timespec * const pxResult )
{
	int64_t partial_sec;
	int err_status = 0;

	/* Check parameters. */
	if( ( pxResult == NULL ) || ( x == NULL ) || ( y == NULL ) )
	{
		err_status = -1;
	}

	if( err_status == 0 )
	{
		/* Perform addition. */
		pxResult->tv_nsec = x->tv_nsec + y->tv_nsec;

		/* check for overflow in case nsec value was invalid */
		if( pxResult->tv_nsec < 0 )
		{
			err_status = 1;
		}
		else
		{
			partial_sec = ( pxResult->tv_nsec ) / NANOSECONDS_PER_SECOND;
			pxResult->tv_nsec = ( pxResult->tv_nsec ) % NANOSECONDS_PER_SECOND;
			pxResult->tv_sec = x->tv_sec + y->tv_sec + partial_sec;

			/* check for overflow */
			if( pxResult->tv_sec < 0 )
			{
				err_status = 1;
			}
		}
	}

	return err_status;
}

int UTILS_TimespecAddNanoseconds( const struct timespec * const x,
				int64_t lnano_secs,
				struct timespec * const pxResult )
{
	int64_t total_sec;
	int err_status = 0;

	/* Check parameters. */
	if( ( pxResult == NULL ) || ( x == NULL ) )
	{
		err_status = -1;
	}

	if( err_status == 0 )
	{
		/* add nano seconds */
		total_sec = x->tv_nsec + lnano_secs;

		/* check for nano seconds overflow */
		if( total_sec < 0 )
		{
			err_status = 1;
		}
		else
		{
			pxResult->tv_nsec = total_sec % NANOSECONDS_PER_SECOND;
			pxResult->tv_sec = x->tv_sec + ( total_sec / NANOSECONDS_PER_SECOND );

			/* check for seconds overflow */
			if( pxResult->tv_sec < 0 )
			{
				err_status = 1;
			}
		}
	}

	return err_status;
}

int UTILS_TimespecSubtract( const struct timespec * const x,
			const struct timespec * const y,
			struct timespec * const pxResult )
{
	int comp;
	int err_status = 0;

	/* Check parameters. */
	if( ( pxResult == NULL ) || ( x == NULL ) || ( y == NULL ) )
	{
		err_status = -1;
	}

	if( err_status == 0 )
	{
		comp = UTILS_TimespecCompare( x, y );

		/* if x < y then result would be negative, return 1 */
		if( comp == -1 )
		{
			err_status = 1;
		}
		else if( comp == 0 )
		{
			/* if times are the same return zero */
			pxResult->tv_sec = 0;
			pxResult->tv_nsec = 0;
		}
		else
		{
			/* If x > y Perform subtraction. */
			pxResult->tv_sec = x->tv_sec - y->tv_sec;
			pxResult->tv_nsec = x->tv_nsec - y->tv_nsec;

			/* check if nano seconds value needs to borrow */
			if( pxResult->tv_nsec < 0 )
			{
				/* Based on comparison, tv_sec > 0 */
				pxResult->tv_sec--;
				pxResult->tv_nsec += ( long ) NANOSECONDS_PER_SECOND;
			}

			/* if nano second is negative after borrow, it is an overflow error */
			if( pxResult->tv_nsec < 0 )
			{
				err_status = -1;
			}
		}
	}

	return err_status;
}

int UTILS_TimespecCompare( const struct timespec * const x,
			const struct timespec * const y )
{
	int err_status = 0;

	/* Check parameters */
	if( ( x == NULL ) && ( y == NULL ) )
	{
		err_status = 0;
	}
	else if( y == NULL )
	{
		err_status = 1;
	}
	else if( x == NULL )
	{
		err_status = -1;
	}
	else if( x->tv_sec > y->tv_sec )
	{
		err_status = 1;
	}
	else if( x->tv_sec < y->tv_sec )
	{
		err_status = -1;
	}
	else
	{
		/* seconds are equal compare nano seconds */
		if( x->tv_nsec > y->tv_nsec )
		{
			err_status = 1;
		}
		else if( x->tv_nsec < y->tv_nsec )
		{
			err_status = -1;
		}
		else
		{
			err_status = 0;
		}
	}

	return err_status;
}

bool UTILS_ValidateTimespec( const struct timespec * const pxTimespec )
{
	bool ret = false;

	if( pxTimespec != NULL )
	{
		/* Verify 0 <= tv_nsec < 1000000000. */
		if( ( pxTimespec->tv_nsec >= 0 ) &&
			( pxTimespec->tv_nsec < NANOSECONDS_PER_SECOND ) )
		{
			ret = true;
		}
	}

	return ret;
}

void os_delay_ticks( const TickType_t ticks )
{
	sret_t sys_ret;

	super_call(scall_id_pthread_delay_ticks, ticks, RST_VAL, RST_VAL, &sys_ret);
	RET_ERR_IF_FALSE(sys_ret.status == SUCCESS, EAGAIN, void);
}
