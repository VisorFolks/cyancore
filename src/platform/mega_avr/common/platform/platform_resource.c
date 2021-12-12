/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_dp.c
 * Description		: This file contains sources for platform
 *			  device properties dummy apis. This is necessary
 *			  to avoid comilation failure when device
 *			  properties arent setup. Original file can be
 *			  found at <Platform>/platform/platform_dp.c
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stddef.h>
#include <stdint.h>
#include <status.h>
#include <machine_call.h>
#include <platform.h>

/**
 * platform_dp_setup - Updates platform DP
 *
 * @brief This function is responsible to update platform DP
 * and make it accessible to the system. This function needs
 * to be called during platform setup. In this file this
 * function is weak and will be replaced with file mentioned
 * in the file description.
 *
 * @return status: return the function execution status
 */
_WEAK status_t platform_resources_setup()
{
	return success;
}

/**
 * platform_fetch_sp - mcall handler for fetch_sp
 *
 * @brief This function is a machine call hander for fetch_sp
 * access code. It is responsible to respond with hardware ID
 * to corresponding software properties. In this file this
 * function is weak and will be replaced with file mentioned
 * in the file description.
 *
 * @param[in] a0: arg0
 * @param[in] a1: arg1
 * @param[in] a2: arg2
 *
 * @return status: return the function execution status
 */
_WEAK mret_t platform_fetch_sp(unsigned int a0 _UNUSED, unsigned int a1 _UNUSED, unsigned int a2 _UNUSED)
{
	mret_t ret;
	ret.p = (uintptr_t) NULL;
	ret.size = 0;
	ret.status = error_inval_dev_id;
	return ret;
}

/**
 * platform_fetch_dp - mcall handler for fetch_dp
 *
 * @brief This function is a machine call hander for fetch_dp
 * access code. It is responsible to respond with pointer to
 * corresponding device properties. In this file this
 * function is weak and will be replaced with file mentioned
 * in the file description.
 *
 * @param[in] dev: device ID
 * @param[in] a0: arg0
 * @param[in] a1: arg1
 *
 * @return status: return the function execution status
 */
_WEAK mret_t plaform_fetch_dp(unsigned int dev _UNUSED, unsigned int a0 _UNUSED, unsigned int a1 _UNUSED)
{
	mret_t ret;
	ret.p = (uintptr_t)NULL;
	ret.size = 0x00;
	ret.status = error;
	return ret;
}
