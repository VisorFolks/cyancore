/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: gpio.c
 * Description		: This file contains macors used by gpio HAL
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdint.h>
#include <stdbool.h>
#include <syslog.h>
#include <assert.h>
#include <mmio.h>
#include <arch.h>
#include <aon.h>
#include "aon_private.h"

/**
 * aon_pmu_unlock - Unlocks write access to PMU registers
 *
 * @brief This function writes SIFIVE SECRET to key register
 * which unlocks write access to any PMU Registers.
 * This function needs to be called before performing writes
 * PMU registers. Upon successful write, the PMU register
 * gets locked and again this function needs to be called
 * for further writes.
 *
 * @param[in] *port - HAL driver port pointer
 */
static void aon_pmu_unlock(const aon_port_t *port)
{
	/* Writing SECRET to key register unlocks write access */
	MMIO32(port->baddr + PMUKEY_OFFSET) = SIFIVE_PMU_SECRET;
	arch_dsb();
}

/**
 * aon_pmucause - Returns cause for PMU wakeup event
 *
 * @brief This function reads and returns PMU event value.
 *
 * @param[in] *port - HAL driver port pointer
 * @param[out] *reset_val - Pointer to store the result
 * @return status: function status
 */
status_t aon_pmucause(const aon_port_t *port, uint32_t *reset_val)
{
	RET_ON_FAIL(port, error_func_inval_arg);
	*reset_val = MMIO32(port->baddr + PMUCAUSE_OFFSET);
	return success;
}

/**
 * aon_pmusleep_program - api to program sleep routine
 *
 * @brief This api needs to be invoked to program the sleep
 * instructions into the PMU module. Input array should be
 * PMU_PROGRAM_SIZE * 16 Bytes wide.
 *
 * @param[in] *port - HAL driver port pointer
 * @param[in] *arr - Array consisting of sleep instructions
 * @return status: function status
 */
status_t aon_pmusleep_program(const aon_port_t *port, const uint16_t *arr)
{
	RET_ON_FAIL(port, error_func_inval_arg);
	sysdbg4("Programming sleep sequence...\n");
	for(size_t i = 0; i < PMU_PROGRAM_SIZE; i++)
	{
		/* Unlock writes to PMU Register */
		aon_pmu_unlock(port);
		MMIO32(port->baddr + PMUSLEEPI_OFFSET(i)) = arr[i];
		/* Make sure the instructions are stored */
		arch_dsb();
	}

	sysdbg4("Verifying sleep sequence...\n");
	for(size_t i = 0; i < PMU_PROGRAM_SIZE; i++)
		if(MMIO32(port->baddr + PMUSLEEPI_OFFSET(i)) != arr[i])
			return error_system_prog_fail;
	return success;
}

/**
 * aon_pmuwake_program - api to program wake up routine
 *
 * @brief This api needs to be invoked to program the wake up
 * instructions into the PMU module. Input array should be
 * PMU_PROGRAM_SIZE * 16 Bytes wide.
 *
 * @param[in] *port - HAL driver port pointer
 * @param[in] *arr - Array consisting of wake up instructions
 * @return status: function status
 */
status_t aon_pmuwake_program(const aon_port_t *port, const uint16_t *arr)
{
	RET_ON_FAIL(port, error_func_inval_arg);
	sysdbg4("Programming wake up sequence...\n");
	for(size_t i = 0; i < PMU_PROGRAM_SIZE; i++)
	{
		/* Unlock writes to PMU Register */
		aon_pmu_unlock(port);
		MMIO32(port->baddr + PMUWAKEUPI_OFFSET(i)) = arr[i];
		/* Make sure the instructions are stored */
		arch_dsb();
	}

	sysdbg4("Verifying wake up sequence...\n");
	for(size_t i = 0; i < PMU_PROGRAM_SIZE; i++)
		if(MMIO32(port->baddr + PMUWAKEUPI_OFFSET(i)) != arr[i])
			return error_system_prog_fail;
	return success;
}

/**
 * aon_pmu_ie - api to enable pmu interrupt
 *
 * @brief This api needs to be invoked when higher level
 * driver needs to enable wake up trigger before executing
 * sleep routine.
 *
 * @param[in] *port - HAL driver port pointer
 * @param[in] index - Index of wake up source
 * @return status: function status
 */
status_t aon_pmu_ie(const aon_port_t *port, uint32_t index)
{
	RET_ON_FAIL(port, error_func_inval_arg);
	aon_pmu_unlock(port);
	MMIO32(port->baddr + PMUIE_OFFSET) |= (1 << index);
	arch_dsb();
	return success;
}

/**
 * aon_pmusleep_trigger - api to trigger execution of sleep program
 *
 * @brief This api is used to execute sleep program and put
 * platform to sleep.
 *
 * @param[in] *port - HAL driver port pointer
 * @return status: function status
 */
status_t aon_pmusleep_trigger(const aon_port_t *port)
{
	RET_ON_FAIL(port, error_func_inval_arg);
	aon_pmu_unlock(port);
	MMIO32(port->baddr + PMUSLEEP_OFFSET) = 1;
	arch_dsb();
	return success;
}
