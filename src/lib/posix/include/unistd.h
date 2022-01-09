/**
 * @file unistd.h
 * @brief Standard symbolic constants and types
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html
 */

#ifndef _CC_POSIX_UNISTD_H_
#define _CC_POSIX_UNISTD_H_

#include "posix/include/sys/types.h"

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

#endif /* ifndef _CC_POSIX_UNISTD_H_ */
