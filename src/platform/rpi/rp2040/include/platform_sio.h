/*
 * CYANCORE LICENSE
 * Copyrights (C) 2023, Cyancore Team
 *
 * File Name		: platform_sio.h
 * Description		: This file contains functions for accessing
 *			  SIO register space on RP2040.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _PLATFORM_SIO_H_

#include <status.h>
#include <mmio.h>

#define SIO_BASE			0xd0000000
#define SIO_OFFSET_END			0x17c

/**
 * platform_sio_read - Performs mmio reads on SIO reg space
 *
 * @brief This function reads SIO registers using mmio. These
 * reads happen in 1 clk cycle as per the rp2040 documentation.
 *
 * @param[in] offset: offset of register
 * @param[out] *val: pointer of variable to store the reads
 * @return status
 */
static inline status_t platform_sio_read(uint32_t offset, uint32_t *val)
{
	RET_ON_FAIL((offset <= SIO_OFFSET_END), error_func_inval_arg);
	*val = MMIO32(SIO_BASE + offset);
	return success;
}

/**
 * platform_sio_write - Performs mmio write on SIO reg space
 *
 * @brief This function writes to SIO registers using mmio. 
 * These writes happen in 1 clk cycle as per the rp2040
 * documentation.
 *
 * Note: Read-Modify-Write needs to be performed by programmer.
 * This function ONLY performs write.
 *
 * @param[in] offset: offset of register
 * @param[in] val: value to write to register
 * @return status
 */
static inline status_t platform_sio_write(uint32_t offset, uint32_t val)
{
	RET_ON_FAIL((offset <= SIO_OFFSET_END), error_func_inval_arg);
	MMIO32(SIO_BASE + offset) = val;
	return success;
}
