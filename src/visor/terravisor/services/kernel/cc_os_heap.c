/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os.h
 * Description		: CC OS Kernel definations
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

/*****************************************************
 *	INCLUDES
 *****************************************************/
#include <terravisor/cc_os/utils/cc_os_heap.h>

/*****************************************************
 *	GLOBAL DECLARATIONS
 *****************************************************/

/*****************************************************
 *	GLOBAL EXTERNS
 *****************************************************/

/*****************************************************
 *	STATIC FUNCTION DEFINATIONS
 *****************************************************/

/*****************************************************
 *	USER FUNCTION DEFINATIONS
 *****************************************************/
void * cc_os_malloc(size_t size _UNUSED)
{
	return NULL;
}
void * cc_os_free(void *addr _UNUSED )
{
	return NULL;
}
