/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: posix_mqueue.c
 * Description		: This file consists of posix message queue related call handles
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <string.h>
#include <supervisor/workers.h>
#include <posix/pthread.h>
#include <posix/mqueue.h>
#include <posix/errno.h>
#include <posix/utils.h>
#include <posix/fcntl.h>

#define DELAY_MIN_TICK			(1U)

size_t g_mq_id_ctr = RST_VAL;

pthread_mutex_t g_mq_mutex;
pthread_mutexattr_t g_mq_mutex_attr;

/*********************
 * Static Functions
 ********************/

static int s_find_queue_in_desc_list(const char * name, const mqd_section_t * p_mqd_section)
{
	(void)(name);
	(void)(p_mqd_section);
	return SUCCESS;
}

static int s_queue_write(mqd_t mqdes, const void * buff, size_t size, unsigned msg_prio)
{
	const mqd_section_t * p_mqd_section = (mqd_section_t *) mqdes;
	sret_t mq_sys_ret;

	RET_ERR_IF_FALSE((p_mqd_section->attr.mq_flags & O_RDONLY), -ENOTSUP, int);

	memcpy((void *)p_mqd_section->kernel_buff, buff, size);

	super_call(scall_id_mq_send, p_mqd_section->id, size, msg_prio, &mq_sys_ret);
	RET_ERR_IF_FALSE(mq_sys_ret.status == SUCCESS, -EBADF, int);

	return SUCCESS;
}

static int s_queue_read(mqd_t mqdes, void * buff, size_t size)
{
	const mqd_section_t * p_mqd_section = (mqd_section_t *) mqdes;
	sret_t mq_sys_ret;

	RET_ERR_IF_FALSE((p_mqd_section->attr.mq_flags & O_WRONLY), -ENOTSUP, int);

	super_call(scall_id_mq_receive, p_mqd_section->id, size, RST_VAL, &mq_sys_ret);
	RET_ERR_IF_FALSE(mq_sys_ret.status == SUCCESS, -EBADF, int);

	memcpy(buff, (void *) (p_mqd_section->kernel_buff), size);

	return SUCCESS;
}

static int s_mq_lock_init(void)
{
	pthread_mutexattr_init(&g_mq_mutex_attr);
	return pthread_mutex_init(&g_mq_mutex, &g_mq_mutex_attr);
}

static int s_mq_lock_deinit(void)
{
	pthread_mutexattr_destroy(&g_mq_mutex_attr);
	return pthread_mutex_destroy(&g_mq_mutex);
}

static int s_mq_acquire_lock(void)
{
	return pthread_mutex_lock(&g_mq_mutex);
}

static int s_mq_release_lock(void)
{
	return pthread_mutex_unlock(&g_mq_mutex);
}

/*********************
 * POSIX Functions
 ********************/

mqd_t mq_open( 	const char * name,
		int oflag,
		mode_t mode _UNUSED,
		const mq_attr_t * attr )
{
	mqd_section_t * p_mqd_section = NULL;
	sret_t mq_sys_ret;
	size_t name_len = UTILS_strnlen(name, posixconfigMQ_NAME_LEN_MAX);

	/* Check argument assertions */
	ASSERT_IF_FALSE(name != NULL, mqd_t);
	ASSERT_IF_FALSE( name_len < posixconfigMQ_NAME_LEN_MAX, mqd_t);

	/* Return ENOENT if element already exist */
	RET_ERR_IF_FALSE(s_find_queue_in_desc_list((const char *) name, NULL) == SUCCESS, -ENOENT, mqd_t);

	/* Return ENOENT if oflag is not equal to O_CREAT */
	RET_ERR_IF_FALSE( oflag & O_CREAT, -ENOENT, mqd_t);

	/* Initialise lock */
	p_mqd_section = (mqd_section_t *) s_mq_lock_init();
	RET_ERR_IF_FALSE(p_mqd_section == SUCCESS , p_mqd_section, mqd_t);

	/* Grab resource access else return EBUSY */
	RET_ERR_IF_FALSE( s_mq_acquire_lock() == SUCCESS, -EBUSY, mqd_t);

	if (attr != NULL)
	{
		/* Fill user attributes */
		memcpy(&(p_mqd_section->attr), attr, sizeof(mq_attr_t));
	}
	else
	{	/* Fill default attribute vals */
		p_mqd_section->attr.mq_maxmsg 	= posixconfigMQ_MAX_MESSAGES;
		p_mqd_section->attr.mq_msgsize 	= posixconfigMQ_MAX_SIZE;
	}

	p_mqd_section->attr.mq_flags = oflag;

	/* Perform super_call */
	super_call(scall_id_mq_open,
		(p_mqd_section->attr.mq_maxmsg * p_mqd_section->attr.mq_msgsize),
		RST_VAL,
		RST_VAL,
		&mq_sys_ret
		);
	if (mq_sys_ret.status != SUCCESS)
	{
		p_mqd_section = (mqd_section_t *) -ENOTSUP;
	}
	else
	{
		/* Get the queue ID from kernel handler as mq_sys_ret.size */
		p_mqd_section->id = mq_sys_ret.size;

		/* Get kernel buffer address */
		p_mqd_section->kernel_buff = mq_sys_ret.p;

		/* Set queue name as specified */
		memcpy(&(p_mqd_section->mq_name), name, name_len);
	}

	RET_ERR_IF_FALSE( s_mq_release_lock() == SUCCESS, -EBUSY, mqd_t);

	return (mqd_t) p_mqd_section;
}

int mq_close( mqd_t mqdes )
{
	int err = SUCCESS;
	sret_t mq_sys_ret;

	ASSERT_IF_FALSE(mqdes != NULL, ssize_t);

	/* Grab resource access else return EBUSY */
	RET_ERR_IF_FALSE( s_mq_acquire_lock() == SUCCESS, -EBUSY, int);

	/* Return ENOENT if element already exist */
	if (s_find_queue_in_desc_list(NULL, (mqd_section_t *) mqdes) == SUCCESS)
	{
		/* Reset attr values */
		memset(&((mqd_section_t *) mqdes)->attr, RST_VAL, sizeof(mq_attr_t));

		/* Perform Super Call */
		super_call(scall_id_mq_close, ((mqd_section_t *) mqdes)->id, RST_VAL, RST_VAL, &mq_sys_ret);
		if (mq_sys_ret.status != SUCCESS)
		{
			err = -ENOTSUP;
		}
		else
		{
			DO_NOTHING;
		}
	}
	else
	{
		err = -EBADF;
	}

	RET_ERR_IF_FALSE( s_mq_release_lock() == SUCCESS, -EBUSY, ssize_t);

	RET_ERR_IF_FALSE( s_mq_lock_deinit() == SUCCESS, err, ssize_t );

	return err;
}

int mq_getattr( mqd_t mqdes, mq_attr_t * attr )
{
	ASSERT_IF_FALSE(mqdes != NULL, ssize_t);

	memcpy(attr, &(((mqd_section_t *) mqdes)->attr), sizeof(mq_attr_t));

	return SUCCESS;
}

ssize_t mq_receive( mqd_t mqdes, char * msg_ptr, size_t msg_len, unsigned int * msg_prio )
{
	return mq_timedreceive( mqdes, msg_ptr, msg_len, msg_prio, NULL );
}

int mq_send( mqd_t mqdes, const char * msg_ptr, size_t msg_len, unsigned msg_prio )
{
	return mq_timedsend( mqdes, msg_ptr, msg_len, msg_prio, NULL );
}

ssize_t mq_timedreceive( mqd_t mqdes, char * msg_ptr, size_t msg_len, unsigned * msg_prio _UNUSED, const timespec_t * abstime )
{
	ASSERT_IF_FALSE(mqdes != NULL, ssize_t);
	ASSERT_IF_FALSE(msg_ptr != NULL, ssize_t);
	ASSERT_IF_FALSE(msg_len > RST_VAL, ssize_t);

	*msg_prio = RST_VAL;

	ssize_t err = SUCCESS;
	TickType_t abs_ticks;

	if (abstime == NULL)
	{
		abs_ticks = IS_ISR() ? RST_VAL : posixconfigMAX_DELAY;
	}

	else
	{
		ASSERT_IF_FALSE ( UTILS_TimespecToTicks(abstime, &abs_ticks) == SUCCESS, ssize_t );
	}

	/* Grab resource access else return EBUSY */
	RET_ERR_IF_FALSE( s_mq_acquire_lock() == SUCCESS, -EBUSY, ssize_t);

	/* Check the availability of the Queue entry */
	if (s_find_queue_in_desc_list(NULL, (mqd_section_t *) mqdes) != SUCCESS)
	{
		err = -EBADF;
		goto EXIT_MQ_TIMED_RECEIVE;
	}
	do
	{
		/* Try to read queue from kernel */
		if (s_queue_read(mqdes, msg_ptr, msg_len) == SUCCESS)
		{
			break;
		}
		else if (((mqd_section_t *) mqdes)->attr.mq_flags & O_NONBLOCK)
		{
			abs_ticks = RST_VAL;
		}
		if (abs_ticks == RST_VAL)
		{
			err = -ETIMEDOUT;
		}
		else
		{
			os_delay_ticks(DELAY_MIN_TICK);
			abs_ticks--;
		}
	}while(abs_ticks > RST_VAL);

EXIT_MQ_TIMED_RECEIVE:
	RET_ERR_IF_FALSE( s_mq_release_lock() == SUCCESS, -EBUSY, ssize_t );

	return err;
}

int mq_timedsend( mqd_t mqdes, const char * msg_ptr, size_t msg_len, unsigned msg_prio, const struct timespec * abstime )
{
	ASSERT_IF_FALSE(mqdes != NULL, int);
	ASSERT_IF_FALSE(msg_ptr != NULL, int);
	ASSERT_IF_FALSE(msg_len > RST_VAL, int);

	ssize_t err = SUCCESS;
	TickType_t abs_ticks;

	if (abstime == NULL)
	{
		abs_ticks = IS_ISR() ? RST_VAL : posixconfigMAX_DELAY;
	}

	else
	{
		ASSERT_IF_FALSE (UTILS_TimespecToTicks(abstime, &abs_ticks) == SUCCESS, ssize_t);
	}

	/* Grab resource access else return EBUSY */
	RET_ERR_IF_FALSE( s_mq_acquire_lock() == SUCCESS, -EBUSY, ssize_t);

	/* Check the availability of the Queue entry */
	if (s_find_queue_in_desc_list(NULL, (mqd_section_t *) mqdes) != SUCCESS)
	{
		err = -EBADF;
		goto EXIT_MQ_TIMED_SEND;
	}
	do
	{
		/* Try to send to kernel queue buffer */
		if (s_queue_write(mqdes, msg_ptr, msg_len, msg_prio) == SUCCESS)
		{
			break;
		}
		else if (((mqd_section_t *) mqdes)->attr.mq_flags & O_NONBLOCK)
		{
			abs_ticks = RST_VAL;
		}
		if (abs_ticks == RST_VAL)
		{
			err = -ETIMEDOUT;
		}
		else
		{
			os_delay_ticks(DELAY_MIN_TICK);
			abs_ticks--;
		}
	}while(abs_ticks > RST_VAL);

EXIT_MQ_TIMED_SEND:
	RET_ERR_IF_FALSE( s_mq_release_lock() == SUCCESS, -EBUSY, ssize_t );

	return err;
}

int mq_unlink( const char * name _UNUSED)
{
	return SUCCESS;
}
