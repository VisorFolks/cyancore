/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: dp_module.h
 * Description		: This file contains prototypes of device
 *			  properties - module
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>

typedef const struct module
{
	hw_devid_t id;
	uintptr_t baddr;
	uintptr_t stride;
	unsigned long clk;
	unsigned int clk_id;
	irqs_t interrupt[MAX_INTERRUPTS_PER_DEVICE];
} module_t;

#define add_modules(x)		.modules = x,		\
				.n_mods = propsize(x)

/**
 * add_irq - Adds irq structure to the module
 *
 * @param[in] _index - Index of array to add
 * @param[in] _mod - irq module
 * @param[in] _id - irq id
 * @param[in] _trigger - irq trigger type
 */
#define add_irq(_index, _mod, _id, _trigger)		\
	.interrupt[_index] = {_mod, _id, _trigger}

/**
 * create_module - Instantiates module property structure
 *
 * @param[in] _name - Name of the module or struct
 * @param[in] _id - module ID
 * @param[in] _baddr - base address of the module
 * @param[in] _stride - stride of the address space
 * @param[in] _clk - clock value of used by the module
 * @param[in] _clk_id - clock ID to enable the module
 * @param[in] ... - Variable args for adding irqs, if any IRQ is associated, use
 * add_irq macro to add the value. For example:
 * create_module(test, test | 0, 0x1000, 0x100, 115200, 10,
 * add_irq(int_plat, 10, int_rising edge),
 * add_irq(int_plat, 11, int_rising_edge));
 * if no IRQs are associated, omit the addition.
 */
#define create_module(_name, _id, _baddr, _stride, _clk, _clk_id, ...)\
	module_t _name =					\
	{							\
		.id = _id,					\
		.baddr = _baddr,				\
		.stride = _stride,				\
		.clk = _clk,					\
		.clk_id = _clk_id,				\
		##__VA_ARGS__					\
	}


/**
 * create_module_list - Creates a list of modules
 *
 * @param[in] _name - Name of the module
 * @param[in] mod1 - name of first module
 * @param[in] ... - variable agrs if there are more than 1 module
 */
#define create_module_list(_name, mod1, ...)	\
	module_t * const _name[] =		\
	{					\
		mod1,				\
		##__VA_ARGS__			\
	}

module_t *dp_get_module_info(hw_devid_t dev);
