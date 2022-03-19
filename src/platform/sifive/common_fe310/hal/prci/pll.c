/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: prci.c
 * Description		: This file contains function definitions for
 *			  internal PLL of FE310 chipset.
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <hal/sysclk.h>
#include <string.h>
#include <nmath.h>
#include <assert.h>
#include <syslog.h>
#include <mmio.h>
#include <arch.h>
#include "prci_private.h"

static pllc_t pllc[N_CORES];

static inline void __pll_config_for_nearest_freq(unsigned int base, unsigned int clk, pllc_t *config)
{
	unsigned int ri, fi, qi, ni, f, q, n;
	unsigned int nearest = MAX_PLL_OUT;

	memset(config, 0, sizeof(pllc_t));

	assert(clk < MIN_PLL_OUT || clk > MAX_PLL_OUT);

	for(ri = 8; ri > 0; ri--)
	{
		unsigned int refr = base/ri;
		if(refr < MIN_REFR || refr > MAX_REFR)
			continue;
		for(fi = 0; fi < 64; fi++)
		{
			f = 2 * (fi + 1);
			unsigned int vco = refr * f;
			if(vco < MIN_VCO || vco > MAX_VCO)
				continue;
			for(qi = 1; qi < 4; qi ++)
			{
				q = 1 << qi;
				unsigned int pllout = vco / q;
				if(pllout < MIN_PLLO || pllout > MAX_PLLO)
					continue;
				for(ni = 0; ni < 64; ni++)
				{
					n = 2 * (ni + 1);
					unsigned int div = 1;
					unsigned int diff_div = abs((int)(clk - (pllout / n)));
					unsigned int diff_nodiv = abs((int)(clk - pllout));
					unsigned int diff = diff_nodiv;
					if(diff_div < diff_nodiv)
					{
						diff = diff_div;
						div = n;
					}
					if(diff < nearest)
					{
						nearest = diff;
						config->found = 1;
						config->diven = (div > 1) ? 1 : 0;
						config->n = (uint8_t) ((div > 1) ? ni : 0);
						config->r = (uint8_t) ri;
						config->f = (uint8_t) fi;
						config->q = (uint8_t) qi;
					}
				}
			}
		}
	}
}

status_t _NOINLINE __prci_pll_get_clk(sysclk_port_t *port, unsigned int *clk)
{
	pllc_t *config = &pllc[arch_core_index()];
	unsigned int pllref, refr, vco, pllout, plldivd;
	pllref = port->base_clk;
	sysdbg5("PLL: pllref = %u\n", pllref);

	if(!config->found)
	{
		sysdbg5("PLL: Never caliberated!\n");
		return error_system_clk_caliberation;
	}

	refr = pllref / config->r;
	sysdbg5("PLL: refr = %u\n", refr);
	vco = refr * (2 * (config->f + 1));
	sysdbg5("PLL: vco = %u\n", vco);
	pllout = vco / (1 << config->q);
	sysdbg5("PLL: pllout = %u\n", pllout);
	*clk = pllout;
	if(config->diven)
	{
		sysdbg5("PLL: Output divider is enabled with div = %u\n", config->n);
		plldivd = pllout / (2 * (config->n + 1));
		sysdbg5("PLL: plldivd = %u\n", plldivd);
		*clk = plldivd;
	}
	return success;
}

static inline void __prci_pll_wait_to_lock(sysclk_port_t *port)
{
	TODO(< ! > Add a busy loop delay of 100uS)
	while(MMIO32(port->baddr + PLLCFG_OFFSET) & (1 << PLLLOCK))
		arch_dsb();
}

static inline void __prci_pll_write_config(sysclk_port_t *port, const pllc_t *conf)
{
	if(!conf->found)
		return;

	uint32_t value;

	if(conf->diven)
	{
		value = MMIO32(port->baddr + PLLOUTDIV_OFFSET);
		value |= (conf->n & PLLOUTDIV_MASK) << PLLOUTDIV;
		MMIO32(port->baddr + PLLOUTDIV_OFFSET) = value;
	}
	else
		MMIO32(port->baddr + PLLOUTDIV_OFFSET) |= (1 << PLLOUTDIVBY1);

	value = MMIO32(port->baddr + PLLCFG_OFFSET);
	value &= ~(PLLR_MASK | PLLF_MASK | PLLQ_MASK);
	value |= (conf->r << PLLR) & PLLR_MASK;
	value |= (conf->f << PLLF) & PLLF_MASK;
	value |= (conf->q << PLLQ) & PLLQ_MASK;
	sysdbg5("PLL: PLLCFG = %p", value);
	MMIO32(port->baddr + PLLCFG_OFFSET) = value;
	arch_dsb();
	return;
}

void _NOINLINE __prci_pll_set_clk(sysclk_port_t *port, unsigned int clk)
{
	pllc_t *conf = &pllc[arch_core_index()];
	__pll_config_for_nearest_freq(port->base_clk, clk, conf);
	__prci_pll_write_config(port, conf);
	__prci_pll_wait_to_lock(port);
	return;
}

void _NOINLINE __prci_pll_select_xosc(sysclk_port_t *port)
{
	MMIO32(port->baddr + PLLCFG_OFFSET) |= (1 << PLLREFSEL);
	return;
}

void _NOINLINE __prci_pll_select_rosc(sysclk_port_t *port)
{
	MMIO32(port->baddr + PLLCFG_OFFSET) &= ~(1 << PLLREFSEL);
	return;
}

void _NOINLINE __prci_pll_select_pll(sysclk_port_t *port)
{
	MMIO32(port->baddr + PLLCFG_OFFSET) |= (1 << PLLSEL);
	return;
}

void _NOINLINE __prci_pll_deselect_pll(sysclk_port_t *port)
{
	MMIO32(port->baddr + PLLCFG_OFFSET) &= ~(1 << PLLSEL);
	return;
}

void _NOINLINE __prci_pll_bypass(sysclk_port_t *port)
{
	MMIO32(port->baddr + PLLCFG_OFFSET) &= ~(1 << PLLBYPASS);
	return;
}

void _NOINLINE __prci_pll_inline(sysclk_port_t *port)
{
	MMIO32(port->baddr + PLLCFG_OFFSET) |= (1 << PLLBYPASS);
	return;
}

