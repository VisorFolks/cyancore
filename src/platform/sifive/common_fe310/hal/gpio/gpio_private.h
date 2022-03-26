/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: gpio_private.h
 * Description		: This file contains macors used by gpio HAL
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define INPUTVAL_OFFSET		0x00
#define	INPUTEN_OFFSET		0x04
#define OUTPUTEN_OFFSET		0x08
#define OUTPUTVAL_OFFSET	0x0c
#define PUE_OFFSET		0x10
#define DS_OFFSET		0x14
#define RIE_OFFSET		0x18
#define RIP_OFFSET		0x1c
#define FIE_OFFSET		0x20
#define FIP_OFFSET		0x24
#define HIE_OFFSET		0x28
#define HIP_OFFSET		0x2c
#define LIE_OFFSET		0x30
#define LIP_OFFSET		0x34
#define IOFEN_OFFSET		0x38
#define IOFSEL_OFFSET		0x3c
#define OUTXOR_OFFSET		0x40
#define PHIE_OFFSET		0x44
#define PLIE_OFFSET		0x48

static lock_t gpio_key;
uint8_t port_status[N_PORT];
