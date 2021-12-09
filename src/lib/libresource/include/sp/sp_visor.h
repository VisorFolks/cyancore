/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: sp_visor.h
 * Description		: This file contains data structures of software 
 *			  properties
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#include <stdint.h>
#include <sp/sp_device.h>
#include <dp/dp_device.h>

typedef struct swdev
{
	sw_devid_t swdev_id;
	hw_devid_t hwdev_id;
} swdev_t;

typedef struct visor
{
	sw_devid_t *devids;
	size_t n_dev;
} visor_t;
