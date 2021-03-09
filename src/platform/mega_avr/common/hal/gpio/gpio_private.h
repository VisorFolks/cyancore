/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: gpio_private.h
 * Description		: This file contains macors used by gpio HAL
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _GPIO_PRIVATE_H_

#define PIN_OFFSET	0x00
#define DDR_OFFSET	0x01
#define PORT_OFFSET	0x02

lock_t gpio_lock;
uint8_t port_status[N_PORT];

