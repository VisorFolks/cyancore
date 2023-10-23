/*
 * CYANCORE LICENSE
 * Copyrights (C) 2023, Cyancore Team
 *
 * File Name		: vcall_id.h
 * Description		: This file consists of visor call IDs
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _VCALL_ID_H_

// Visor call IDs
typedef enum vcall_id
{
	fetch_sp			= 0x0001,
	fetch_dp			= 0x0002,
	set_sleep_mode			= 0x0003,
	fetch_clk			= 0x0004,
	config_clk			= 0x0005,
/* pthread related */
	pthread_barrier_destroy		= 0x1001,
	pthread_barrier_init,
	pthread_barrier_wait,
	pthread_create,
	pthread_cond_broadcast,
	pthread_cond_destroy,
	pthread_cond_init,
	pthread_cond_signal,
	pthread_cond_timedwait,
	pthread_equal,
	pthread_exit,
	pthread_getschedparam,
	pthread_join,
	pthread_mutex_destroy,
	pthread_mutex_init,
	pthread_mutex_timedlock,
	pthread_mutex_unlock,
	pthread_mutexattr_destroy,
	pthread_mutexattr_gettype,
	pthread_mutexattr_init,
	pthread_mutexattr_settype,
	pthread_self,
	pthread_setschedparam,
	pthread_delay_ticks,
/* mqueue related */
	mq_close			= 0x2001,
	mq_setattr,
	mq_getattr,
	mq_open,
	mq_receive,
	mq_send,
	mq_unlink,
/* semaphore related */
	sem_init,
	sem_destroy,
	sem_getvalue,
	sem_post,
	sem_wait,
/* scheduler related */
	sched_get_max_priority,
	sched_get_min_priority,
	sched_yield,
} vcall_id_t;
