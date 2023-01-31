/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: helios_sem.h
 * Description		: CC OS semaphore declaration
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
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
typedef struct sem
{
	size_t	sem_val;
	uint8_t	sem_init;
}sem_t;
/*****************************************************
 *	USER MACROS
 *****************************************************/
#define CC_SEM_INST(_Name)	_Name##_sem_inst

#if HELIOS_DYNAMIC == false
#define CC_SEM_DEF(_Name)	\
static sem_t _Name##_sem = {	\
	.sem_init = 0,		\
	.sem_val = 0		\
};				\
sem_t * _Name##_sem_inst = &_Name##_sem
#else
#define CC_SEM_DEF(_Name)	\
sem_t * _Name##_sem_inst = HELIOS_NULL_PTR
#endif
/*****************************************************
 *	USER FUNCTION DECLARATIONS
 *****************************************************/
/**
 * @brief 	Create a semaphore and initialise it
 * @note	The instance needs to be provided using CC_SEM_DEF macro
 *
 * @param sem_ptr[in_out]	Instance pointer
 * @param init_val[in]		Initial value
 *
 * @return status_t
 */
status_t helios_sem_create	(sem_t ** sem_ptr, size_t init_val);

/**
 * @brief 	Delete a semaphore and de-initialise it
 *
 * @param sem_ptr[in_out]	Instance pointer
 *
 * @return status_t
 */
status_t helios_sem_delete 	(sem_t ** sem_ptr);

/**
 * @brief 	Decrement a semaphore value
 *
 * @param sem_ptr[in]		Instance pointer
 *
 * @return status_t
 */
status_t helios_sem_give 	(sem_t * sem_ptr);

/**
 * @brief 	Increment a semaphore value
 *
 * @param sem_ptr[in]		Instance pointer
 * @param wait_ticks[in]	Timeout Wait ticks
 *
 * @return status_t
 */
status_t helios_sem_take 	(sem_t * sem_ptr, size_t wait_ticks);

/**
 * @brief 	Get current semaphore value
 *
 * @param sem_ptr[in]		Instance pointer
 * @param val[out]		Value return
 *
 * @return status_t
 */

status_t helios_sem_get_val 	(const sem_t * sem_ptr, size_t * val);
