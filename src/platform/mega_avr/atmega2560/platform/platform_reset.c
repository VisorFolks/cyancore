/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform_reset.c
 * Description		: This file contains sources for platform
 *			  reset apis
 * Primary Author	: Rahul Goyal [rhgoyal01@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <platform.h>
#include <driver/watchdog.h>
#include <terravisor/platform.h>

extern uint8_t reset_syndrome;

reset_t platform_get_reset_syndrome()
{
	switch(reset_syndrome)
	{
		case 1:
			/* Power on Reset */
			return power_on_reset;
		case 2:
		case 3:
			/* External Reset */
			return external_reset;
		case 4:
		case 5:
		case 6:
		case 7:
		case 12:
		case 13:
		case 14:
		case 15: /* 12 - 0b1100
			  * 13 - 0b1101
			  * 14 - 0b1110
			  * 15 - 0b1111
			  * If wdog and brownout occur together
			  * then server brownout first
			  */
			/* Brown out Reset */
			return brownout_reset;
		case 8:
		case 9:
		case 10:
		case 11:
			/* WDog Reset */
			return wdog_reset;
		default:
			return inval_reset;
	}
}


TODO(This Function needs to be replaced with brownout detection driver api)
_WEAK void brownout_reset_handler()
{
	plat_panic_handler();
}

void platform_reset_handler(reset_t rsyn)
{
	switch(rsyn)
	{
		case power_on_reset:
		case external_reset:
			return;
		case brownout_reset:
			brownout_reset_handler();
		case wdog_reset:
			wdog_reset_handler();
		default:
			plat_panic_handler();
	}
}
