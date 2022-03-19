/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: prci_private.h
 * Description		: This file contains defines of platform
 *			  power, reset, clock and interrupt module
 *			  register offsets
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

/* PLL and Clock offsets */
#define HFROSCCFG_OFFSET	0x00
	#define HFROSCDIV	0
	#define HFROSCDIV_MASK	((1 << 6) - 1)
	#define HFROSCTRIM	16
	#define HFROSCTRIM_MASK	(0xff << 16)
	#define HFROSCEN	30
	#define HFROSCRDY	31

#define HFXOSCCFG_OFFSET	0x04
	#define HFXOSCEN	30
	#define HFXOSCRDY	31

#define PLLCFG_OFFSET		0x08
	#define PLLR		0
	#define PLLR_MASK	7
	#define PLLF		4
	#define PLLF_MASK	(0x3f << PLLF)
	#define PLLQ		10
	#define PLLQ_MASK	(3 << PLLQ)
	#define PLLSEL		16
	#define PLLREFSEL	17
	#define PLLBYPASS	18
	#define PLLLOCK		31

#define PLLOUTDIV_OFFSET	0x0c
	#define PLLOUTDIV	0
	#define PLLOUTDIV_MASK	63
	#define PLLOUTDIVBY1	8

#define PROCMONCFG_OFFSET	0xf0

#define MAX_PLL_OUT		384000000U
#define MIN_PLL_OUT		375000U
#define MIN_REFR		6000000U
#define MAX_REFR		12000000U
#define MIN_VCO			384000000U
#define MAX_VCO			768000000U
#define MIN_PLLO		48000000U
#define MAX_PLLO		384000000U

void find_nearest(unsigned int, unsigned int);
typedef struct pll_config
{
	uint8_t found;
	uint8_t r;
	uint8_t f;
	uint8_t q;
	uint8_t diven;
	uint8_t n;
} pllc_t;

void __prci_pll_set_clk(sysclk_port_t *port, unsigned int clk);
status_t __prci_pll_get_clk(sysclk_port_t *port, unsigned int *clk);
void __prci_pll_select_xosc(sysclk_port_t *port);
void __prci_pll_select_rosc(sysclk_port_t *port);
void __prci_pll_select_pll(sysclk_port_t *port);
void __prci_pll_deselect_pll(sysclk_port_t *port);
void __prci_pll_bypass(sysclk_port_t *port);
void __prci_pll_inline(sysclk_port_t *port);

status_t __prci_hfxocs_enable(sysclk_port_t *port);
status_t __prci_hfxocs_disable(sysclk_port_t *port);

status_t __prci_hfosc_enable(sysclk_port_t *port);
status_t __prci_hfosc_disable(sysclk_port_t *port);
status_t __prci_hfosc_set_clk(sysclk_port_t *port, unsigned int clk);
status_t __prci_hfosc_get_clk(sysclk_port_t *port, unsigned int *clk);
