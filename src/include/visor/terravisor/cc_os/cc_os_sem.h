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
 *	USER FUNCTION DECLARATIONS
 *****************************************************/
cc_os_err_t cc_os_sem_create	(sem_t * sem_ptr, size_t init_val);
cc_os_err_t cc_os_sem_take 	(sem_t * sem_ptr);
cc_os_err_t cc_os_sem_give 	(sem_t * sem_ptr);
cc_os_err_t cc_os_sem_delete 	(sem_t * sem_ptr);
cc_os_err_t cc_os_sem_get_val 	(sem_t * sem_ptr, size_t * val);
