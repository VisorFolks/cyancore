/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: posix_semaphore.c
 * Description		: This file consists of posix semaphore related call handles
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <string.h>
#include <supervisor/workers.h>
#include <posix/semaphore.h>
#include <posix/errno.h>
#include <posix/utils.h>

/*********************
 * Static Functions
 ********************/
static int s_sem_wait( sem_t * sem )
{
	sret_t sem_sys_ret;
	ASSERT_IF_FALSE(sem == NULL, int);

	super_call(scall_id_sem_wait, (unsigned int) *sem, RST_VAL, RST_VAL, &sem_sys_ret);

	return sem_sys_ret.status;
}

/*********************
 * POSIX Functions
 ********************/
int sem_destroy( sem_t * sem )
{
	sret_t sem_sys_ret;
	ASSERT_IF_FALSE(sem == NULL, int);

	super_call(scall_id_sem_destroy, (unsigned int) *sem, RST_VAL, RST_VAL, &sem_sys_ret);
	RET_ERR_IF_FALSE(sem_sys_ret.status == SUCCESS, sem_sys_ret.status, int);

	*sem = (sem_t) NULL;

	return SUCCESS;
}

int sem_getvalue( sem_t * sem,
                  int * sval )
{
	sret_t sem_sys_ret;
	ASSERT_IF_FALSE(sem == NULL, int);

	super_call(scall_id_sem_getvalue, (unsigned int) *sem, RST_VAL, RST_VAL, &sem_sys_ret);
	RET_ERR_IF_FALSE(sem_sys_ret.status == SUCCESS, sem_sys_ret.status, int);

	*sval = (int) sem_sys_ret.p;

	return SUCCESS;
}

int sem_init( sem_t * sem,
              int pshared _UNUSED,
              unsigned value )
{
	sret_t sem_sys_ret;
	ASSERT_IF_FALSE(sem == NULL, int);

	super_call(scall_id_sem_init, value, RST_VAL, RST_VAL, &sem_sys_ret);
	RET_ERR_IF_FALSE(sem_sys_ret.status == SUCCESS, sem_sys_ret.status, int);

	*sem = (sem_t) sem_sys_ret.p;

	return SUCCESS;
}

int sem_post( sem_t * sem )
{
	sret_t sem_sys_ret;
	ASSERT_IF_FALSE(sem == NULL, int);

	super_call(scall_id_sem_post, (unsigned int) *sem, RST_VAL, RST_VAL, &sem_sys_ret);

	return sem_sys_ret.status;
}

int sem_timedwait( sem_t * sem,
                   const struct timespec * abstime )
{
	ASSERT_IF_FALSE(sem == NULL, int);

	int err = SUCCESS;
	TickType_t abs_ticks;

	if (abstime == NULL)
	{
		abs_ticks = IS_ISR() ? RST_VAL : posixconfigMAX_DELAY;
	}

	else
	{
		ASSERT_IF_FALSE ( UTILS_TimespecToTicks(abstime, &abs_ticks) == SUCCESS, ssize_t );
	}

	do
	{
		if (s_sem_wait(sem) == SUCCESS)
		{
			break;
		}
		else
		{
			if (abs_ticks == RST_VAL)
			{
				err = -ETIMEDOUT;
			}
			else
			{
				os_delay_ticks((const TickType_t)DELAY_MIN_TICK);
				abs_ticks--;
			}
		}

	}while(abs_ticks > RST_VAL);

	return err;
}

int sem_trywait( sem_t * sem )
{
	return sem_timedwait(sem, RST_VAL);
}

int sem_wait( sem_t * sem )
{
	return sem_timedwait(sem, NULL);
}
