/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_posix_config.h
 * Description		: POSIX user config
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#ifndef posixconfigTICK_RATE_HZ
#define posixconfigTICK_RATE_HZ			(1000)
#endif

/*******************
 * PTHREAD configs
 *******************/
#ifndef posixconfigPTHREAD_MIN_STACK_SIZE
#define posixconfigPTHREAD_MIN_STACK_SIZE	(128)
#endif

/*******************
 * MQUEUE configs
 *******************/

/**
 * @brief MQUEUE max name length in bytes
 */
#ifndef posixconfigMQ_NAME_LEN_MAX
#define posixconfigMQ_NAME_LEN_MAX		(16)
#endif

/**
 * @brief MQUEUE max munber of queues allowed
 */
#ifndef posixconfigMQ_MAX_QUEUE
#define posixconfigMQ_MAX_QUEUE			(5)
#endif

/**
 * @brief MQUEUE Maximum number of messages in an mq at one time
 */
#ifndef posixconfigMQ_MAX_MESSAGES
#define posixconfigMQ_MAX_MESSAGES    		(10)
#endif

/**
 * @brief MQUEUE Maximum size (in bytes) of each message
 */
#ifndef posixconfigMQ_MAX_SIZE
#define posixconfigMQ_MAX_SIZE    		(128)
#endif
