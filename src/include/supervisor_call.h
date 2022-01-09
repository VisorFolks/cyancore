/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: supervisor_call.h
 * Description		: This file consists of supervisor call IDs and prototypes
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _SUPER_CALL_H_

#include <stdint.h>
#include <status.h>

// Supervisor call IDs
typedef enum scall_id
{
	scall_id_generic				= 0x0000,
	scall_id_is_irq,
/* pthread related */
	scall_id_pthread_attr_destroy			= 0x1000,
	scall_id_pthread_attr_getdetachstate,
	scall_id_pthread_attr_getschedparam,
	scall_id_pthread_attr_getstacksize,
	scall_id_pthread_attr_init,
	scall_id_pthread_attr_setdetachstate,
	scall_id_pthread_attr_setschedparam,
	scall_id_pthread_attr_setschedpolicy,
	scall_id_pthread_attr_setstacksize,
	scall_id_pthread_barrier_destroy,
	scall_id_pthread_barrier_init,
	scall_id_pthread_barrier_wait,
	scall_id_pthread_create,
	scall_id_pthread_cond_broadcast,
	scall_id_pthread_cond_destroy,
	scall_id_pthread_cond_init,
	scall_id_pthread_cond_signal,
	scall_id_pthread_cond_timedwait,
	scall_id_pthread_equal,
	scall_id_pthread_exit,
	scall_id_pthread_getschedparam,
	scall_id_pthread_join,
	scall_id_pthread_mutex_destroy,
	scall_id_pthread_mutex_init,
	scall_id_pthread_mutex_timedlock,
	scall_id_pthread_mutex_unlock,
	scall_id_pthread_mutexattr_destroy,
	scall_id_pthread_mutexattr_gettype,
	scall_id_pthread_mutexattr_init,
	scall_id_pthread_mutexattr_settype,
	scall_id_pthread_self,
	scall_id_pthread_setschedparam,
	scall_id_pthread_delay_ticks,
/* mqueue related */
	scall_id_mq_close,
	scall_id_mq_setattr,
	scall_id_mq_getattr,
	scall_id_mq_open,
	scall_id_mq_receive,
	scall_id_mq_send,
	scall_id_mq_unlink,
/* semaphore related */
	scall_id_sem_init,
	scall_id_sem_destroy,
	scall_id_sem_getvalue,
	scall_id_sem_post,
	scall_id_sem_wait,
/* scheduler related */
	scall_id_sched_get_max_priority,
	scall_id_sched_get_min_priority,
	scall_id_sched_yield,

} scall_id_t;

typedef struct sret
{
	uintptr_t p;
	size_t size;
	status_t status;
} sret_t;

typedef struct scall
{
	scall_id_t id;
	sret_t (*callback)(unsigned int a0, unsigned int a1, unsigned int a2);
} scall_t;

#define INCLUDE_SCALL(_name, _id , _callback)		\
	const scall_t _name _SECTION(".scall") =	\
	{						\
		.id		= _id,			\
		.callback	= _callback		\
	}
