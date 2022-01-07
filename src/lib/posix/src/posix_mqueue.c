/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: posix_mqueue.c
 * Description		: This file consists of posix message queue related call handles
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <string.h>
#include <supervisor/workers.h>
#include <lib/posix/include/mqueue.h>
#include <lib/posix/include/errno.h>
#include <lib/posix/include/utils.h>
#include <lib/posix/include/fcntl.h>

#define DELAY_MIN_TICK			(1U)

sret_t g_mq_sys_ret;
size_t g_mq_id_ctr = 0;

static int s_find_queue_in_desc_list(char * name, mqd_section_t * p_mqd_section);
static int s_queue_desc_allocator(size_t index, mqd_section_t ** p_mqd_section);
static int s_queue_desc_deallocator(mqd_section_t ** p_mqd_section);
static int s_mqueue_delay(TickType_t ticks);
static int s_queue_write(mqd_t mqdes, const void * buff, size_t size);
static int s_queue_read (mqd_t mqdes, const void * buff, size_t size);
static int s_acquire_resource(void);
static int s_release_resource(void);

mqd_t mq_open( 	const char * name,
		int oflag,
		mode_t mode,
		mq_attr_t * attr )
{
	mqd_section_t * p_mqd_section = NULL;
	size_t index;

	/* Check argument assertions */
	ASSERT_IF_FALSE(name != NULL, mqd_t);
	ASSERT_IF_FALSE(UTILS_strnlen(name, posixconfigMQ_NAME_LEN_MAX) < posixconfigMQ_NAME_LEN_MAX, mqd_t);

	/* Return ENOENT if element already exist */
	RET_ERR_IF_FALSE(s_find_queue_in_desc_list(name, NULL) == SUCCESS, -ENOENT, mqd_t);

	/* Return ENOENT if oflag is not equal to O_CREAT */
	RET_ERR_IF_FALSE( oflag & O_CREAT, -ENOENT, mqd_t);

	/* Grab resource access else return EBUSY */
	RET_ERR_IF_FALSE( s_acquire_resource() == SUCCESS, -EBUSY, mqd_t);

	/* Find available slot in descriptor table else return ENOSPC */
	if(s_queue_desc_allocator(g_mq_id_ctr++, &p_mqd_section ) == SUCCESS)
	{
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
		super_call(scall_id_mq_open, p_mqd_section->attr.mq_maxmsg, p_mqd_section->attr.mq_msgsize, 0, &g_mq_sys_ret);
		if (g_mq_sys_ret.status != SUCCESS)
		{
			p_mqd_section = (mqd_section_t *) -ENOTSUP;
		}
		else
		{
			/* Set Kernel buffer ptr */
			p_mqd_section->kernel_buff = g_mq_sys_ret.p;

			/* Set queue name as specified */
			strcpy(&(p_mqd_section->mq_name), name );
		}
	}
	else
	{
		DO_NOTHING;
	}

	RET_ERR_IF_FALSE( s_release_resource() == SUCCESS, -EBUSY, mqd_t);

	return (mqd_t) p_mqd_section;
}

int mq_close( mqd_t mqdes )
{
	int err = SUCCESS;

	ASSERT_IF_FALSE(mqdes != NULL, ssize_t);

	/* Grab resource access else return EBUSY */
	RET_ERR_IF_FALSE( s_acquire_resource() == SUCCESS, -EBUSY, int);

	/* Return ENOENT if element already exist */
	if (s_find_queue_in_desc_list(NULL, (mqd_section_t *) mqdes) == SUCCESS)
	{
		/* Reset attr values */
		memset(&((mqd_section_t *) mqdes)->attr, RST_VAL, sizeof(mq_attr_t));

		/* Perform Super Call */
		super_call(scall_id_mq_close, ((mqd_section_t *) mqdes)->kernel_buff, 0, 0, &g_mq_sys_ret);
		if (g_mq_sys_ret.status != SUCCESS)
		{
			err = -ENOTSUP;
		}
		else
		{
			/* Deallocate the descriptor section from user space */
			err = s_queue_desc_deallocator((mqd_section_t **) &mqdes);
		}
	}
	else
	{
		err = -EBADF;
	}

	RET_ERR_IF_FALSE( s_release_resource() == SUCCESS, -EBUSY, ssize_t);

	return err;
}

int mq_getattr( mqd_t mqdes,
                mq_attr_t * attr )
{
	ASSERT_IF_FALSE(mqdes != NULL, ssize_t);

	memcpy(attr, &(((mqd_section_t *) mqdes)->attr), sizeof(mq_attr_t));

	return SUCCESS;
}

ssize_t mq_receive( mqd_t mqdes,
		    char * msg_ptr,
		    size_t msg_len,
		    unsigned int * msg_prio )
{
	return mq_timedreceive( mqdes, msg_ptr, msg_len, msg_prio, NULL );
}

int mq_send( mqd_t mqdes,
	     const char * msg_ptr,
	     size_t msg_len,
	     unsigned msg_prio )
{
	return mq_timedsend( mqdes, msg_ptr, msg_len, msg_prio, NULL );
}

ssize_t mq_timedreceive( mqd_t mqdes,
			 char * msg_ptr,
			 size_t msg_len,
			 unsigned * msg_prio _UNUSED,
			 const timespec_t * abstime )
{
	ASSERT_IF_FALSE(mqdes != NULL, ssize_t);
	ASSERT_IF_FALSE(msg_ptr != NULL, ssize_t);
	ASSERT_IF_FALSE(msg_len > 0, ssize_t);

	ssize_t err = SUCCESS;
	TickType_t abs_ticks;

	if (abstime == NULL)
	{
		abs_ticks = s_is_irq() ? RST_VAL : posxconfigMAX_DELAY;
	}

	else
	{
		ASSERT_IF_FALSE (UTILS_TimespecToTicks(abstime, &abs_ticks) == SUCCESS, ssize_t);
	}

	/* Grab resource access else return EBUSY */
	RET_ERR_IF_FALSE( s_acquire_resource() == SUCCESS, -EBUSY, ssize_t);

	if (s_find_queue_in_desc_list(NULL, (mqd_section_t *) mqdes) == SUCCESS)
	{
		do
		{
			/* Try to read queue from kernel */
			if (s_queue_read(mqdes, msg_ptr, msg_len) == SUCCESS)
			{
				break;
			}
			else
			{
				if (((mqd_section_t *) mqdes)->attr.mq_flags & O_NONBLOCK)
				{
					err = -ENOSPC;
					break;
				}
				else
				{
					s_mqueue_delay(DELAY_MIN_TICK);
					abs_ticks--;

					if (abs_ticks == 0)
					{
						err = -ETIMEDOUT;
					}
					else
					{
						DO_NOTHING;
					}
				}
			}
		}while(abs_ticks > 0);
	}
	else
	{
		err = -EBADF;
	}

	RET_ERR_IF_FALSE( s_release_resource() == SUCCESS, -EBUSY, ssize_t);

	return err;
}

int mq_timedsend( mqd_t mqdes,
		  const char * msg_ptr,
		  size_t msg_len,
		  unsigned msg_prio,
		  const struct timespec * abstime )
{
	ASSERT_IF_FALSE(mqdes != NULL, int);
	ASSERT_IF_FALSE(msg_ptr != NULL, int);
	ASSERT_IF_FALSE(msg_len > 0, int);

	TODO(mq_timedsend);

	return SUCCESS;
}

int mq_unlink( const char * name )
{
	TODO(mq_unlink);
	return SUCCESS;
}

/************************************************************/

static int s_find_queue_in_desc_list(char * name, mqd_section_t * p_mqd_section)
{
	TODO(s_find_queue_in_desc_list);
	return SUCCESS;
}

static int s_queue_desc_allocator(size_t index, mqd_section_t ** p_mqd_section)
{
	TODO(s_queue_desc_allocator);
	return SUCCESS;
}

static int s_queue_desc_deallocator(mqd_section_t ** p_mqd_section)
{
	TODO(s_queue_desc_deallocator);
	return SUCCESS;
}

static int s_queue_write(mqd_t mqdes, const void * buff, size_t size)
{
	mqd_section_t * p_mqd_section = (mqd_section_t *) mqdes;

	RET_ERR_IF_FALSE((p_mqd_section->attr.mq_flags & O_RDONLY), -ENOTSUP, int);

	memcpy(p_mqd_section->kernel_buff, buff, size);
	return SUCCESS;
}

static int s_queue_read(mqd_t mqdes, const void * buff, size_t size)
{
	mqd_section_t * p_mqd_section = (mqd_section_t *) mqdes;

	RET_ERR_IF_FALSE((p_mqd_section->attr.mq_flags & O_WRONLY), -ENOTSUP, int);

	super_call(scall_id_mq_receive, p_mqd_section->kernel_buff, size, 0, &g_mq_sys_ret);
	RET_ERR_IF_FALSE(g_mq_sys_ret.status == SUCCESS, -EBADF, int);

	memcpy(buff, (void *) (g_mq_sys_ret.p), size);

	return SUCCESS;
}

static int s_mqueue_delay(TickType_t ticks)
{
	super_call(scall_id_pthread_delay_ticks, ticks, 0, 0, &g_mq_sys_ret);
	RET_ERR_IF_FALSE(g_mq_sys_ret.status == SUCCESS, EAGAIN, int);

	return SUCCESS;
}

static int s_acquire_resource(void)
{
	TODO(s_acquire_resource);
	return SUCCESS;
}

static int s_release_resource(void)
{
	TODO(s_release_resource);
	return SUCCESS;
}

static bool s_is_irq(void)
{
	super_call(scall_id_is_irq, 0, 0, 0, &g_mq_sys_ret);
	return g_mq_sys_ret.status == SUCCESS;
}
