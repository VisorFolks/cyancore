/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os.h
 * Description		: CC OS semaphore declaration
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
/*****************************************************
 *	DEFINES
 *****************************************************/
#include <terravisor/cc_os/cc_os.h>
/*****************************************************
 *	TYPEDEFS
 *****************************************************/
typedef struct sem
{
	uint8_t	sem_init;
	size_t	sem_val;
}sem_t;
/*****************************************************
 *	USER MACROS
 *****************************************************/
#define CC_SEM_INST(_Name)	_Name##_sem_inst

#if CC_OS_DYNAMIC == CC_OS_FALSE
#define CC_SEM_DEF(_Name)	\
static sem_t _Name##_sem = {	\
	.sem_init = 0,		\
	.sem_val = 0		\
};				\
static sem_t * _Name##_sem_inst = &_Name##_sem
#else
static sem_t * _Name##_sem_inst = CC_OS_NULL_PTR
#endif
/*****************************************************
 *	USER FUNCTION DECLARATIONS
 *****************************************************/
cc_os_err_t cc_os_sem_create	(sem_t ** sem_ptr, size_t init_val);
cc_os_err_t cc_os_sem_delete 	(sem_t ** sem_ptr);
cc_os_err_t cc_os_sem_give 	(sem_t * sem_ptr);
cc_os_err_t cc_os_sem_take 	(sem_t * sem_ptr, size_t wait_ticks);
cc_os_err_t cc_os_sem_get_val 	(const sem_t * sem_ptr, size_t * val);
