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
#ifndef ccosconfig_CC_OS_USE_DYNAMIC
#define ccosconfig_CC_OS_USE_DYNAMIC		0
#endif

/**
 * @brief	Maximum number of threads allowed in static resource allocation
 * @note	The number of allowed threads are dependent of available RAM space.
 * 		User may have to keep it optimised so as to use as low BSS section
 * 		to be used as possible for the application being created.
 */
#ifndef ccosconfig_CC_OS_MAX_THREAD
#define ccosconfig_CC_OS_MAX_THREAD		10
#endif

/**
 * @brief	Max number of characters allowed to be used for task name
 */
#ifndef ccosconfig_CC_OS_TASK_NAME_LEN
#define ccosconfig_CC_OS_TASK_NAME_LEN		16
#endif

/**
 * @brief	Task priority of IDLE task
 * @note	Possible values : 1 -> 255
 */
#ifndef ccosconfig_CC_OS_TASK_PRIORITY
#define ccosconfig_CC_OS_TASK_PRIORITY		1
#endif

/**
 * @brief	Stack size used by IDLE task
 * @note	The stack size is either allocated statically or dynamically as
 * 		per the setting of ccosconfig_CC_OS_USE_DYNAMIC
 */
#ifndef ccosconfig_CC_OS_TASK_STACK_LEN
#define ccosconfig_CC_OS_TASK_STACK_LEN		255
#endif
