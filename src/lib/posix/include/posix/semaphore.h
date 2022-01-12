/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: semaphore.h
 * Description		: This file consists of posix semaphore related declarations
 * 			: http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/semaphore.h.html
 *
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _CC_POSIX_SEMAPHORE_H_

/* CC+POSIX includes. */
#include <posix/time.h>
#include <cc_posix_types.h>

/**
 * @brief Semaphore type.
 */
typedef PosixSemType_t sem_t;

/**
 * @brief Destroy an unnamed semaphore.
 *
 * @see http://pubs.opengroup.org/onlinepubs/9699919799/functions/sem_destroy.html
 *
 * @retval 0 - upon successful completion
 *
 * @note Semaphore is destroyed regardless of whether there is any thread currently blocked on this semaphore.
 */
int sem_destroy( sem_t * sem );

/**
 * @brief Get the value of a semaphore.
 *
 * @see http://pubs.opengroup.org/onlinepubs/9699919799/functions/sem_getvalue.html
 *
 * @retval 0 - Upon successful completion
 *
 * @note If sem is locked, then the object to which sval points is set to zero.
 */
int sem_getvalue( sem_t * sem,
                  int * sval );

/**
 * @brief Initialize an unnamed semaphore.
 *
 * @see http://pubs.opengroup.org/onlinepubs/9699919799/functions/sem_init.html
 *
 * @note pshared is ignored. Semaphores will always be considered "shared".
 *
 * @retval 0 - upon successful completion
 * @retval -1 - otherwise. System error variable errno is also set in this case.
 *
 * @sideeffect Possible errno values
 * <br>
 * EINVAL -  The value argument exceeds {SEM_VALUE_MAX}.
 * <br>
 * ENOSPC - A resource required to initialize the semaphore has been exhausted.
 */
int sem_init( sem_t * sem,
              int pshared,
              unsigned value );

/**
 * @brief Unlock a semaphore.
 *
 * @see http://pubs.opengroup.org/onlinepubs/9699919799/functions/sem_post.html
 *
 * @retval 0 - upon successful completion
 */
int sem_post( sem_t * sem );

/**
 * @brief Lock a semaphore with timeout.
 *
 * @see http://pubs.opengroup.org/onlinepubs/9699919799/functions/sem_timedwait.html
 *
 * @retval 0 - upon successful completion
 * @retval -1 - otherwise. System error variable errno is also set in this case.
 *
 * @sideeffect Possible errno values
 * <br>
 * EINVAL - parameter specified a nanoseconds field value less than zero or greater
 * than or equal to 1000 million
 * <br>
 * ETIMEDOUT - The semaphore could not be locked before the specified timeout expired.
 *
 * @note Deadlock detection is not implemented.
 */
int sem_timedwait( sem_t * sem,
                   const struct timespec * abstime );

/**
 * @brief Lock a semaphore if available.
 *
 * @see http://pubs.opengroup.org/onlinepubs/9699919799/functions/sem_trywait.html
 *
 * @retval 0 - upon successful completion
 * @retval -1 - otherwise. System error variable errno is also set in this case.
 *
 * @sideeffect Possible errno values
 * <br>
 * EAGAIN - The semaphore was already locked, so it cannot be immediately locked by the sem_trywait() operation.
 */
int sem_trywait( sem_t * sem );

/**
 * @brief Lock a semaphore.
 *
 * @see http://pubs.opengroup.org/onlinepubs/9699919799/functions/sem_wait.html
 *
 * @retval 0 - upon successful completion
 * @retval -1 - otherwise. System error variable errno is also set in this case.
 *
 * @note Deadlock detection is not implemented.
 */
int sem_wait( sem_t * sem );
