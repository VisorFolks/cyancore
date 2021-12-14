/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: spi.c
 * Description		: This file contains sources for mega-avr
 *			  HAL spi apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <mmio.h>
#include <platform.h>
#include <interrupt.h>
#include <hal/gpio.h>
#include <hal/spi.h>
#include "spi_private.h"


status_t spi_master_setup(spi_port_t *port, dataframe_format_t df_format, clk_pol_t cpol, clk_ph_t cpha)
{
	status_t ret = success;
	uint8_t spcr_value = 0;
	gpio_port_t spi_mosi, spi_miso, spi_sck, spi_ss;
	assert(port);
	platform_clk_en(port->clk_id);
	spcr_value |= (1 << SPE) | (1 << MSTR);
	switch(port->fdiv)
	{
		case 4:
			spcr_value |= (fdiv4 << SPR0);
			break;
		case 16:
			spcr_value |= (fdiv16 << SPR0);
			break;
		case 64:
			spcr_value |= (fdiv64 << SPR0);
			break;
		case 128:
			spcr_value |= (fdiv128 << SPR0);
			break;
		default:
			ret = error_func_inval_arg;
			break;
	}
	spcr_value |= df_format ? (1 << DODR) : 0;
	spcr_value |= cpol ? (1 << CPOL) : 0;
	spcr_value |= cpha ? (1 << CPHA) : 0;

	ret |= gpio_pin_alloc(&spi_mosi, port->com_port, port->com_pins[0]);
	ret |= gpio_pin_alloc(&spi_miso, port->com_port, port->com_pins[1]);
	ret |= gpio_pin_alloc(&spi_sck, port->com_port, port->com_pins[2]);
	ret |= gpio_pin_alloc(&spi_ss, port->com_port, port->com_pins[3]);

	ret |= gpio_pin_mode(&spi_mosi, out);
	ret |= gpio_pin_mode(&spi_miso, in);
	ret |= gpio_pin_mode(&spi_sck, out);
	ret |= gpio_pin_mode(&spi_ss, out);
	MMIO8(port->baddr | SPCR_OFFSET) = spcr_value;
	return ret;
}

status_t spi_slave_setup(spi_port_t *port, dataframe_format_t df_format, clk_pol_t cpol, clk_ph_t cpha)
{
	status_t ret = success;
	uint8_t spcr_value = 0;
	gpio_port_t spi_mosi, spi_miso, spi_sck, spi_ss;
	assert(port);
	platform_clk_en(port->clk_id);
	spcr_value |= (1 << SPE);
	switch(port->fdiv)
	{
		case 4:
			spcr_value |= (fdiv4 << SPR0);
			break;
		case 16:
			spcr_value |= (fdiv16 << SPR0);
			break;
		case 64:
			spcr_value |= (fdiv64 << SPR0);
			break;
		case 128:
			spcr_value |= (fdiv128 << SPR0);
			break;
		default:
			ret = error_func_inval_arg;
			break;
	}
	spcr_value |= df_format ? (1 << DODR) : 0;
	spcr_value |= cpol ? (1 << CPOL) : 0;
	spcr_value |= cpha ? (1 << CPHA) : 0;

	ret |= gpio_pin_alloc(&spi_mosi, port->com_port, port->com_pins[0]);
	ret |= gpio_pin_alloc(&spi_miso, port->com_port, port->com_pins[1]);
	ret |= gpio_pin_alloc(&spi_sck, port->com_port, port->com_pins[2]);
	ret |= gpio_pin_alloc(&spi_ss, port->com_port, port->com_pins[3]);

	ret |= gpio_pin_mode(&spi_mosi, in);
	ret |= gpio_pin_mode(&spi_miso, out);
	ret |= gpio_pin_mode(&spi_sck, in);
	ret |= gpio_pin_mode(&spi_ss, in);
	MMIO8(port->baddr | SPCR_OFFSET) = spcr_value;
	return ret;
}

bool spi_wcol_error(spi_port_t *port)
{
	assert(port);
	return (MMIO8(port->baddr + SPSR_OFFSET) & (1 << WCOL)) ? true : false;
}

bool spi_trx_done(spi_port_t *port)
{
	assert(port);
	return (MMIO8(port->baddr + SPSR_OFFSET) & (1 << SPIF)) ? true : false;
}

status_t spi_int_en(spi_port_t *port)
{
	assert(port);
	MMIO8(port->baddr + SPCR_OFFSET) |= (1 << SPIE);
	return success;
}

status_t spi_int_dis(spi_port_t * port)
{
	assert(port);
	MMIO8(port->baddr + SPCR_OFFSET) &= ~(1 << SPIE);
	return success;
}

status_t spi_tx(spi_port_t *port, char data)
{
	assert(port);
	MMIO8(port->baddr + SPDR_OFFSET) = data;
	return success;
}

status_t spi_rx(spi_port_t *port, char *data)
{
	assert(port);
	*data = MMIO8(port->baddr + SPDR_OFFSET);
	return success;
}
