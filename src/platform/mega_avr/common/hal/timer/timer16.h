/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: timer16.h
 * Description		: This file contains sources for mega-avr
 *			  16bit timer register offsets and bitfields.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define TCCRA_16B_OFFSET	0x00
#define TCCRB_16B_OFFSET	0x01
#define TCCRC_16B_OFFSET	0x02
#define TCNTL_16B_OFFSET	0x04
#define TCNTH_16B_OFFSET	0x05
#define OCRAL_16B_OFFSET	0x08
#define OCRAH_16B_OFFSET	0x09
#define OCRBL_16B_OFFSET	0x0a
#define OCRBH_16B_OFFSET	0x0b
/* This address is fixed according to arch */
#ifndef TIMSK_BASE
#define TIMSK_BASE		0x6E
#endif

static void timer16_config_mode(const timer_port_t *port, unsigned int mode)
{
	uint8_t reg1, reg2;
	reg1 = MMIO8(port->baddr + TCCRA_16B_OFFSET);
	reg2 = MMIO8(port->baddr + TCCRB_16B_OFFSET);

	if(mode <= 15)
	{	
		reg1 |= (mode & 0x3);
		reg2 |= ((mode & 0xc) << 1);
	}
	else
	{
		/* Syslog print warning message */
	}
	
	MMIO8(port->baddr + TCCRA_16B_OFFSET) = reg1;
	MMIO8(port->baddr + TCCRB_16B_OFFSET) = reg2;
}

static void timer16_config_ps(const timer_port_t *port, unsigned int ps)
{
	uint8_t reg;
	reg = MMIO8(port->baddr + TCCRB_16B_OFFSET);

	if(ps <= 7)
		reg |= ps;
	else
	{
		/* Syslog print warning message */
	}

	MMIO8(port->baddr + TCCRB_16B_OFFSET) = reg;
}

static void timer16_config_op_mode(const timer_port_t *port, bool en, bool inv)
{
	uint8_t reg, id;
	id = port->port_id & 0xf;
	reg = MMIO8(port->baddr + TCCRA_16B_OFFSET);

	if(en)
		reg |= inv ? (3 << ((3 - id) << 1)) : (2 << ((3 - id) << 1));
	else
		reg &= ~(3 << ((3 - id) << 1));
	
	MMIO8(port->baddr + TCCRA_16B_OFFSET) = reg;
	MMIO16(port->baddr + TCNTL_16B_OFFSET) = 0;
}

static void timer16_set(const timer_port_t *port, uint16_t value)
{
	uint8_t id = port->port_id & 0xf;
	if(id == 0)
	{
		MMIO8(port->baddr + OCRAH_16B_OFFSET) = (uint8_t)((value & 0xff00) >> 8);
		MMIO8(port->baddr + OCRAL_16B_OFFSET) = (uint8_t)(value & 0xff);
	}
	else if(id == 1)
	{
		MMIO8(port->baddr + OCRBH_16B_OFFSET) = (uint8_t)((value & 0xff00) >> 8);
		MMIO8(port->baddr + OCRBL_16B_OFFSET) = (uint8_t)(value & 0xff);
	}
	else
	{
		/* Syslog print error message */
	}
}

static void timer16_irq_en(const timer_port_t *port)
{
	uint8_t unit = port->port_id & 0xf;
	uint8_t id = (port->port_id & 0xf0) >> 4;
	MMIO8(TIMSK_BASE + id) |= (1 << (unit+1));
}

static void timer16_irq_dis(const timer_port_t *port)
{
	uint8_t unit = port->port_id & 0xf;
	uint8_t id = (port->port_id & 0xf0) >> 4;
	MMIO8(TIMSK_BASE + id) &= ~(1 << (unit+1));
}

static uint16_t timer16_read(const timer_port_t *port)
{
	return MMIO16(port->baddr + TCNTL_16B_OFFSET);
}
