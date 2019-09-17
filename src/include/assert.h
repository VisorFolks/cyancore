#pragma once

extern void plat_panic_handler();

void assert(char condition)
{
	if(!condition)
	{
		plat_panic_handler();
	}
}
