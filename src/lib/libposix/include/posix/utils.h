/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: utils.h
 * Description		: Utility functions used by CC_POSIX
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define _CC_POSIX_UTILS_

/* C standard library includes. */
#include <stdbool.h>
#include <stdint.h>

/* CC+POSIX includes. */
#include <posix/time.h>

#define DELAY_MIN_TICK			        (1U)
#define DO_NOTHING
#define RST_VAL				        (0)
#define ASSERT_IF_FALSE(con, type)	        RET_ERR_IF_FALSE(con, -EINVAL, type)
#define RET_ERR_IF_FALSE(con, ret, type)	if(!(con)) return (type) ret
#define IS_ISR()			        true

/**
 * @brief Calculates the length of pcString, up to xMaxLength.
 *
 * @param[in] pcString The string to find the length of.
 * @param[in] xMaxLength The limit when searching for the end of pcString.
 *
 * @return 0 if pcString is NULL; otherwise, the length of pcString or xMaxLength,
 * whichever is smaller.
 */
size_t UTILS_strnlen( const char * const pcString,
                      size_t xMaxLength );

/**
 * @brief Calculates the number of ticks between now and a given timespec.
 *
 * @param[in] pxAbsoluteTime A time in the future, specified as seconds and
 * nanoseconds since CLOCK_REALTIME's 0.
 * @param[in] pxCurrentTime current time, specified as seconds and
 * nanoseconds.
 * @param[out] pxResult Where the result of the conversion is stored. The result
 * is rounded up for fractional ticks.
 *
 * @return 0 on success. Otherwise, ETIMEDOUT if pxAbsoluteTime is in the past,
 * or EINVAL for invalid parameters.
 */
int UTILS_AbsoluteTimespecToDeltaTicks( const struct timespec * const pxAbsoluteTime,
                                        const struct timespec * const pxCurrentTime,
                                        TickType_t * const pxResult );

/**
 * @brief Converts a struct timespec to Kernel ticks.
 *
 * @param[in] pxTimespec The timespec to convert.
 * @param[out] Where the result of the conversion is stored. The result is rounded
 * up for fractional ticks.
 *
 * @return 0 on success. Otherwise, EINVAL for invalid parameters.
 */
int UTILS_TimespecToTicks( const struct timespec * const pxTimespec,
                           TickType_t * const pxResult );

/**
 * @brief Converts an integer value to a timespec.
 *
 * @param[in] llSource The value to convert.
 * @param[out] pxDestination Where to store the converted value.
 *
 * @return No return value.
 */
void UTILS_NanosecondsToTimespec( int64_t llSource,
                                  struct timespec * const pxDestination );

/**
 * @brief Calculates pxResult = x + y.
 *
 * @param[in] x The first argument for addition.
 * @param[in] y The second argument for addition.
 * @param[out] pxResult Where the result of the calculation is stored.
 *
 * @return -1 if any argument was NULL; 1 if result is negative (overflow); otherwise, 0.
 */
int UTILS_TimespecAdd( const struct timespec * const x,
                       const struct timespec * const y,
                       struct timespec * const pxResult );

/**
 * @brief Calculates pxResult = x + ( struct timespec ) nanosec.
 *
 * @param[in] x The first argument for addition.
 * @param[in] llNanoseconds The second argument for addition.
 * @param[out] pxResult Where the result of the calculation is stored.
 *
 * @return -1 if pxResult or x was NULL; 1 if result is negative; otherwise, 0.
 */
int UTILS_TimespecAddNanoseconds( const struct timespec * const x,
                                  int64_t llNanoseconds,
                                  struct timespec * const pxResult );

/**
 * @brief Calculates pxResult = x - y. If the result is negative contents of
 * pResult are undefined
 *
 * @param[in] x The first argument for subtraction.
 * @param[in] y The second argument for subtraction.
 * @param[out] pxResult Where the result of the calculation is stored.
 *
 * @return -1 if any argument was NULL; 1 if result is negative; otherwise, 0.
 */
int UTILS_TimespecSubtract( const struct timespec * const x,
                            const struct timespec * const y,
                            struct timespec * const pxResult );

/**
 * @brief Compare  x == y.
 *
 * @param[in] x The first argument for comparison.
 * @param[in] y The second argument for comparison.
 *
 * @return 0 if x == y; 1 if x > y; -1 if x < y or any argument was NULL
 */
int UTILS_TimespecCompare( const struct timespec * const x,
                           const struct timespec * const y );

/**
 * @brief Checks that a timespec conforms to POSIX.
 *
 * A valid timespec must have 0 <= tv_nsec < 1000000000.
 *
 * @param[in] pxTimespec The timespec to validate.
 *
 * @return true if the pxTimespec is valid, false otherwise.
 */
bool UTILS_ValidateTimespec( const struct timespec * const pxTimespec );
/**
 * @brief Creates OS delay according to number of ticks provided
 *
 * @param[in] ticks Number of OS ticks to delay
 *
 * @return None
 */
void os_delay_ticks( const TickType_t ticks );
