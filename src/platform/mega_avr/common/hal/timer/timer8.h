/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: timer8.h
 * Description		: This file contains sources for mega-avr
 *			  8bit timer register offsets and bitfields.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define TCCRA_8B_OFFSET		0x00
#define TCCRB_8B_OFFSET		0x01
#define TCNT_8B_OFFSET		0x02
#define OCRA_8B_OFFSET		0x03
#define OCRB_8B_OFFSET		0x04
/* This address is fixed according to arch and applies only for timer2 */
#define ASSR_8B			0xB6
/* This address is fixed according to arch */
#define TIMSK_BASE		0x6E

static void timer8_config_mode(const timer_port_t *port, unsigned int mode)
{
	uint8_t reg1, reg2;
	reg1 = MMIO8(port->baddr + TCCRA_8B_OFFSET);
	reg2 = MMIO8(port->baddr + TCCRB_8B_OFFSET);

	if(mode <= 7)
	{
		reg1 |= (mode & 0x3);
		reg2 |= ((mode & 0x4) << 1);
	}
	else
	{
		/* Syslog print warning message */
	}
	
	MMIO8(port->baddr + TCCRA_8B_OFFSET) = reg1;
	MMIO8(port->baddr + TCCRB_8B_OFFSET) = reg2;
}

static void timer8_config_ps(const timer_port_t *port, unsigned int ps)
{
	uint8_t reg;
	reg = MMIO8(port->baddr + TCCRB_8B_OFFSET);

	if(ps <= 7)
		reg |= ps;
	else
	{
		/* Syslog print warning message */
	}

	MMIO8(port->baddr + TCCRB_8B_OFFSET) = reg;
}

static void timer8_config_op_mode(const timer_port_t *port, bool en, bool inv)
{
	uint8_t reg, id;
	id = port->port_id & 0xf;
	reg = MMIO8(port->baddr + TCCRA_8B_OFFSET);

	if(en)
		reg |= inv ? (3 << ((3 - id) << 1)) : (2 << ((3 - id) << 1));
	else
		reg &= ~(3 << ((3 - id) << 1));
	
	MMIO8(port->baddr + TCCRA_8B_OFFSET) = reg;
}

static void timer8_set(const timer_port_t *port, uint8_t value)
{
	uint8_t id = port->port_id & 0xf;
	if(id == 0)
		MMIO8(port->baddr + OCRA_8B_OFFSET) = value;
	else if(id == 1)
		MMIO8(port->baddr + OCRB_8B_OFFSET) = value;
	else
	{
		/* Syslog print error message */
	}
}

static void timer8_irq_en(const timer_port_t *port)
{
	uint8_t unit = port->port_id & 0xf;
	uint8_t id = (port->port_id & 0xf0) >> 4;
	MMIO8(TIMSK_BASE + id) |= (1 << (unit+1));
}

static void timer8_irq_dis(const timer_port_t *port)
{
	uint8_t unit = port->port_id & 0xf;
	uint8_t id = (port->port_id & 0xf0) >> 4;
	MMIO8(TIMSK_BASE + id) &= ~(1 << (unit+1));
}

static uint8_t timer8_read(const timer_port_t *port)
{
	return (uint8_t)MMIO8(port->baddr + TCNT_8B_OFFSET);
}
