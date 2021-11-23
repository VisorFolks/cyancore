/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_clk.c
 * Description		: This file contains platform clock apis for MegaAVR chips
 *			  that dont support pico power hardware feature. These
 *			  function shall prevent compilation failure in cyancore build.
 *			  Actual source file can be found in <Platform>/platform/platform_clk.c
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <platform.h>

/**
 * platform_clk_reset - Reset all the clocks to peripherals
 *
 * @brief This function is responsible to reset all the clocks
 * associated with peripherals. This is a weak and dummy function.
 * The original functions can be found in the file mentioned in
 * file description.
 *
 * @return status: return the execution status of the function
 */
_WEAK status_t platform_clk_reset()
{
	return success;
}

/**
 * platform_clk_en - enable clock to peripheral
 *
 * @brief This function is responsible to enable the clock
 * associated with peripherals. This is a weak and dummy function.
 * The original functions can be found in the file mentioned in
 * file description.
 *
 * @param[in] id: Clock ID associalted with the peripheral
 *
 * @return status: return the execution status of the function
 */
_WEAK status_t platform_clk_en(unsigned int id _UNUSED)
{
	return success;
}

/**
 * platform_clk_dis - disable clock to peripheral
 *
 * @brief This function is responsible to disable the clock
 * associated with peripherals. This is a weak and dummy function.
 * The original functions can be found in the file mentioned in
 * file description.
 *
 * @param[in] id: Clock ID associalted with the peripheral
 *
 * @return status: return the execution status of the function
 */
_WEAK status_t platform_clk_dis(unsigned int id _UNUSED)
{
	return success;
}
