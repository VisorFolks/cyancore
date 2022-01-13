/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: errno.h
 * Description		: System error numbers.
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _CC_POSIX_ERRNO_H_

#include <status.h>

/**
 * @name Definition of POSIX errnos.
 */
/**@{ */
#define	SUCCESS		success			/**< Operation success*/
#define EPERM		(-error_access)		/**< Operation not permitted. */
#define ENOENT		(-error_file_not_found)	/**< No such file or directory. */
#define EBADF		(-error_file_desc)	/**< Bad file descriptor. */
#define EAGAIN		(-error_device_inval)	/**< Resource unavailable, try again. */
#define ENOMEM		(-error_memory_low)	/**< Not enough space. */
#define EEXIST		(-error_file_exist)	/**< File exists. */
#define EBUSY		(-error_device_busy)	/**< Device or resource busy. */
#define EINVAL		(-error_func_inval_arg)	/**< Invalid argument. */
#define ENOSPC		(-error_file_no_space)	/**< No space left on device. */
#define ERANGE		(-error_math_large_val)	/**< Result too large. */
#define ENAMETOOLONG	(-error_file_long_name)	/**< File name too long. */
#define EDEADLK		(-error_os_deadlock)	/**< Resource deadlock would occur. */
#define EOVERFLOW	(-error_overflow)	/**< Value too large to be stored in data type. */
#define ENOSYS		(-error_func_inval)	/**< Function not supported. */
#define EMSGSIZE	(-error_mesg_long)	/**< Message too long. */
#define ENOTSUP		(-error_func_inval)	/**< Operation not supported. */
#define ETIMEDOUT	(-error_net_con_timeout)/**< Connection timed out. */
/**@} */

/**
 * @name System Variable
 *
 * @brief Define CC+POSIX errno, if enabled.
 * Set configUSE_POSIX_ERRNO to enable, and clear to disable.
 *
 * @{
 */
#if ( configUSE_POSIX_ERRNO == 1 )
#endif
/**@} */
