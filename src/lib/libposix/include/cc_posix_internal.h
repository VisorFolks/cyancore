/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: cc_posix_internal.h
 * Description		: Internal typedefs
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>
#include <cc_posix_config.h>

/**
 * @file cc_posix_internal.h
 * @brief Internal structs and initializers for CC+POSIX.
 */

/**
 * @brief Mutex attribute object.
 */
#if posixconfigENABLE_PTHREAD_MUTEXATTR_T == 1
    typedef struct pthread_mutexattr_internal
    {
        int iType; /**< Mutex type. */
    } pthread_mutexattr_internal_t;
#endif

#if posixconfigENABLE_PTHREAD_MUTEX_T == 1

/**
 * @brief Mutex.
 */
    typedef struct pthread_mutex_internal
    {
        BaseType_t xIsInitialized;          /**< Set to pdTRUE if this mutex is initialized, pdFALSE otherwise. */
        StaticSemaphore_t xMutex;           /**< Kernel mutex. */
        TaskHandle_t xTaskOwner;            /**< Owner; used for deadlock detection and permission checks. */
        pthread_mutexattr_internal_t xAttr; /**< Mutex attributes. */
    } pthread_mutex_internal_t;

/**
 * @brief Compile-time initializer of pthread_mutex_internal_t.
 */
    #define FREERTOS_POSIX_MUTEX_INITIALIZER \
    ( ( ( pthread_mutex_internal_t )         \
    {                                        \
        .xIsInitialized = pdFALSE,           \
        .xMutex = { { 0 } },                 \
        .xTaskOwner = NULL,                  \
        .xAttr = { .iType = 0 }              \
    }                                        \
        )                                    \
    )
#endif /* if posixconfigENABLE_PTHREAD_MUTEX_T == 1 */

#if posixconfigENABLE_PTHREAD_COND_T == 1

/**
 * @brief Condition variable.
 */
    typedef struct pthread_cond_internal
    {
        BaseType_t xIsInitialized;            /**< Set to pdTRUE if this condition variable is initialized, pdFALSE otherwise. */
        StaticSemaphore_t xCondWaitSemaphore; /**< Threads block on this semaphore in pthread_cond_wait. */
        unsigned iWaitingThreads;             /**< The number of threads currently waiting on this condition variable. */
    } pthread_cond_internal_t;

/**
 * @brief Compile-time initializer of pthread_cond_internal_t.
 */

    #define FREERTOS_POSIX_COND_INITIALIZER \
    ( ( ( pthread_cond_internal_t )         \
    {                                       \
        .xIsInitialized = pdFALSE,          \
        .xCondWaitSemaphore = { { 0 } },    \
        .iWaitingThreads = 0                \
    }                                       \
        )                                   \
    )

#endif /* if posixconfigENABLE_PTHREAD_COND_T == 1 */

#if posixconfigENABLE_SEM_T == 1

/**
 * @brief Semaphore type.
 */
    typedef struct
    {
        StaticSemaphore_t xSemaphore; /**< Kernel semaphore. */
        int value;                    /**< POSIX semaphore count. */
    } sem_internal_t;
#endif /* if posixconfigENABLE_SEM_T == 1 */

#if posixconfigENABLE_PTHREAD_BARRIER_T == 1

/**
 * @brief Barrier object.
 */
    typedef struct pthread_barrier_internal
    {
        unsigned uThreadCount;                   /**< Current number of threads that have entered barrier. */
        unsigned uThreshold;                     /**< The count argument of pthread_barrier_init. */
        StaticSemaphore_t xThreadCountSemaphore; /**< Prevents more than uThreshold threads from exiting pthread_barrier_wait at once. */
        StaticEventGroup_t xBarrierEventGroup;   /**< Kernel event group that blocks to wait on threads entering barrier. */
    } pthread_barrier_internal_t;
#endif /* if posixconfigENABLE_PTHREAD_BARRIER_T == 1 */
