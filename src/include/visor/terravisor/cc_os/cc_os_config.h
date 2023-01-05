/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: cc_os_config.h
 * Description		: CC OS Kernel configurations
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

/**
 * @brief	Shall CC_OS use dynamic resource allocation
 * @note	Possible values : 1/0
 */
#ifndef CC_OS_USE_DYNAMIC
#define CC_OS_USE_DYNAMIC		1
#endif

/**
 * @brief	Heap size to be allocated to CC_OS
 * @note	Possible values : Depends on available RAM
 */
#ifndef CC_OS_HEAP_SIZE
#define CC_OS_HEAP_SIZE			1024
#endif

/**
 * @brief	Maximum number of threads allowed in static resource allocation
 * @note	The number of allowed threads are dependent of available RAM space.
 * 		User may have to keep it optimised so as to use as low BSS section
 * 		to be used as possible for the application being created.
 */
#ifndef CC_OS_MAX_THREAD
#define CC_OS_MAX_THREAD		10
#endif

/**
 * @brief	Task priority of IDLE task
 * @note	Possible values : 1 -> 255
 */
#ifndef CC_OS_IDLE_TASK_PRIORITY
#define CC_OS_IDLE_TASK_PRIORITY	0x01
#endif

/**
 * @brief	Stack size used by IDLE task
 * @note	The stack size is either allocated statically or dynamically as
 * 		per the setting of CC_OS_USE_DYNAMIC
 */
#ifndef CC_OS_TASK_STACK_LEN
#define CC_OS_TASK_STACK_LEN		255
#endif

/**
 * @brief	If the Kernel shall enter poer save mode during IDLE
 *
 */
#ifndef CC_OS_POWER_SAVE_EN
#define CC_OS_POWER_SAVE_EN		0
#endif
