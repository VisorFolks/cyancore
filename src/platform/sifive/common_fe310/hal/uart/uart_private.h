/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: uart_private.h
 * Description		: This file contains macors used by uart HAL
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define TXDATA_OFFSET	0x00
#define RXDATA_OFFSET	0x04
#define TXCTRL_OFFSET	0x08
#define RXCTRL_OFFSET	0x0c
#define UARTIE_OFFSET	0x10
#define UARTIP_OFFSET	0x14
#define UARTBR_OFFSET	0x18

#define TX_FULL		31
#define RX_EMPTY	31

#define TXEN		0
#define NSTOP		1
#define TXCNT		16

#define RXEN		0
#define RXCNT		16

#define TXWM		0
#define RXWM		1

#define BAUD_DIV(F, X)	((uint32_t)(F/X)-1)
