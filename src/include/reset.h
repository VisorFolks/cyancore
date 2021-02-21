#pragma once
#define _RESET_H_

typedef enum reset
{
	power_on_reset		= 0,
	external_reset		= 1,
	brownout_reset		= 2,
	wdog_reset		= 3,
	jtag_reset		= 4,
	inval_reset		= 255
} reset_t;
