/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: unistd.h
 * Description		: Standard symbolic constants and types
 * 			: http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html
 *
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include "posix/sys/types.h"

#define _CC_POSIX_UNISTD_H_

/**
 * @brief Suspend execution for an interval of time.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/sleep.html
 *
 * @param[in] seconds The number of seconds to suspend execution.
 *
 * @retval 0 - Upon successful completion.
 *
 * @note Return value of a positive number is not yet supported.
 */
unsigned sleep( unsigned seconds );

/**
 * @brief Suspend execution for microsecond intervals.
 *
 * This is a useful, non-POSIX function.
 * @param[in] usec The number of microseconds to suspend execution.
 *
 * @retval 0 - Upon successful completion.
 */
int usleep( useconds_t usec );
