/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: cc_posix_types.h
 * Description		: POSIX typedefs
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <cc_posix_internal.h>

/*
 * sys/types.h defines a POSIX type when posixconfigENABLE_PTHREAD_<TYPE>_T
 * is not defined AND when posixconfigENABLE_PTHREAD_<TYPE>_T is set to 1.
 * cc_posix_internal.h defines internal type ONLY when
 * posixconfigENABLE_PTHREAD_<TYPE>_T is set to 1.
 * #else part below is to have a type defined, so the code compiles, when
 * posixconfigENABLE_PTHREAD_<TYPE>_T is not defined.
 */
#if posixconfigENABLE_PTHREAD_MUTEX_T == 1
    typedef pthread_mutex_internal_t   PthreadMutexType_t;
#else
    typedef void                       * PthreadMutexType_t;
#endif

#if posixconfigENABLE_PTHREAD_COND_T == 1
    typedef pthread_cond_internal_t    PthreadCondType_t;
#else
    typedef void                       * PthreadCondType_t;
#endif

#if posixconfigENABLE_SEM_T == 1
#endif

#if posixconfigENABLE_PTHREAD_MUTEXATTR_T == 1
    typedef struct pthread_mutexattr
    {
        uint32_t ulpthreadMutexAttrStorage;
    } PthreadMutexAttrType_t;
#else
    typedef void * PthreadMutexAttrType_t;
#endif

#if posixconfigENABLE_PTHREAD_ATTR_T == 1
    typedef struct pthread_attr
    {
        uint32_t ulpthreadAttrStorage;
    } PthreadAttrType_t;
#else
    typedef void                       * PthreadAttrType_t;
#endif

#if posixconfigENABLE_PTHREAD_BARRIER_T == 1
    typedef pthread_barrier_internal_t PthreadBarrierType_t;
#else
    typedef void                       * PthreadBarrierType_t;
#endif

#if( posixconfigUSE_16_BIT_TICKS == 1 )
	typedef uint16_t TickType_t;
#else
	typedef size_t TickType_t;
#endif
#define posixconfigMAX_DELAY			(TickType_t)(~0)
