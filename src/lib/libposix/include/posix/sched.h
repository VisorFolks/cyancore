/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: sched.h
 * Description		: Execution scheduling.
 * 			        : http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sched.h.html
 *
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _CC_POSIX_SCHED_H_

/**
 * @name Scheduling Policies
 */
/**@{ */
#define SCHED_OTHER    0    /**< Another scheduling policy. */
/**@} */

/**
 * @brief Scheduling parameters required for implementation of each supported
 * scheduling policy.
 */
typedef struct sched_param
{
    int sched_priority; /**< Process or thread execution scheduling priority. */
}sched_param_t;

/**
 * @brief Get priority limit (max).
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/sched_get_priority_max.html
 *
 * @note policy is ignored.
 *
 * @return the maximum priority value (0-based) system configuration allows.
 * <br>
 * e.g. if configMAX_PRIORITIES == 7, this function returns (configMAX_PRIORITIES - 1).
 * configMAX_PRIORITIES is configured in application FreeRTOSConfig.h file.
 */
int sched_get_priority_max( int policy );

/**
 * @brief Get priority limit (min).
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/sched_get_priority_min.html
 *
 * @note policy is ignored.
 */
int sched_get_priority_min( int policy );

/**
 * @brief Yield the processor.
 *
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/sched_yield.html
 *
 * @retval 0 - Upon successful completion
 */
int sched_yield( void );
