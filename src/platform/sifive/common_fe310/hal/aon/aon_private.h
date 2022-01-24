/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: aon_private.h
 * Description		: This file contains macors used by AON HAL
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define WDOGCFG_OFFSET		0x000
#define WDOGCOUNT_OFFSET	0x008
#define WDOGS_OFFSET		0x010
#define WDOGFEED_OFFSET		0x018
#define WDOGKEY_OFFSET		0x01c
#define WDOGCMP_OFFSET(X)	0x020 + (0 * X)
#define RTCCFG_OFFSET		0x040
#define RTCCOUNTLO_OFFSET	0x048
#define RTCCOUNTHI_OFFSET	0x04c
#define RTCS_OFFSET		0x050
#define RTCCMP_OFFSET(X)	0x060 + (0 * X)
#define LFROSCCFG_OFFSET	0x070
#define LFCLKMUX_OFFSET		0x07c
#define BACKUP_OFFSET(X)	0x080 + (4 * X)
#define PMUWAKEUPI_OFFSET(X)	0x100 + (4 * X)
#define PMUSLEEPI_OFFSET(X)	0x120 + (4 * X)
#define PMUIE_OFFSET		0x140
#define PMUCAUSE_OFFSET		0x144
#define PMUSLEEP_OFFSET		0x148
#define PMUKEY_OFFSET		0x14c
#define SIFIVEBG_OFFSET		0x210
#define AONCFG_OFFSET		0x300
