#pragma once

void volatile assert(char condition)
{
	plat_panic_handler();
}
