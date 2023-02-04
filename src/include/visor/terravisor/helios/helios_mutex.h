/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: helios_mutex.h
 * Description		: HELIOS mutex declaration
 * Primary Author	: Dibyajyoti Samal [dibyajyoti.samal@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
/*****************************************************
 *	DEFINES
 *****************************************************/
#include <terravisor/helios/helios.h>
/*****************************************************
 *	TYPEDEFS
 *****************************************************/
typedef struct helios_mutex
{
	size_t	mutex_val;
	uint8_t	mutex_init;
	helios_sched_tcb_t * lock_task;
} helios_mutex_t;
/*****************************************************
 *	USER MACROS
 *****************************************************/
#define CC_MUTEX_INST(_Name)	_Name##_mutex_inst

#if HELIOS_DYNAMIC == HELIOS_FALSE
#define CC_MUTEX_DEF(_Name)	\
static helios_mutex_t _Name##_mutex = {	\
	.mutex_init = 0,		\
	.mutex_val = 0,		\
	.lock_task = HELIOS_NULL_PTR	\
};				\
helios_mutex_t * _Name##_mutex_inst = &_Name##_mutex
#else
#define CC_MUTEX_DEF(_Name)	helios_mutex_t * _Name##_mutex_inst = HELIOS_NULL_PTR
#endif
/*****************************************************
 *	USER FUNCTION DECLARATIONS
 *****************************************************/
/**
 * @brief 	Create a mutex
 * @note	The instance needs to be provided using CC_MUTEX_DEF macro
 *
 * @param mutex_ptr[in_out]	Instance pointer
 *
 * @return status_t
 */
status_t helios_mutex_create	(helios_mutex_t ** mutex_ptr);

/**
 * @brief 	Delete a mutex and de-initialise it
 *
 * @param mutex_ptr[in_out]	Instance pointer
 *
 * @return status_t
 */
status_t helios_mutex_delete 	(helios_mutex_t ** mutex_ptr);

/**
 * @brief 	Unlock the mutex
 *
 * @param mutex_ptr[in]		Instance pointer
 *
 * @return status_t
 */
status_t helios_mutex_unlock 	(helios_mutex_t * mutex_ptr);

/**
 * @brief 	Lock a mutex
 *
 * @param mutex_ptr[in]		Instance pointer
 * @param wait_ticks[in]	Timeout Wait ticks
 *
 * @return status_t
 */
status_t helios_mutex_lock 	(helios_mutex_t * mutex_ptr, size_t wait_ticks);

/**
 * @brief 	Get current mutex value
 *
 * @param mutex_ptr[in]		Instance pointer
 * @param val[out]		Value return
 *
 * @return status_t
 */

status_t helios_mutex_get_val 	(const helios_mutex_t * mutex_ptr, size_t * val);
