#pragma once

extern void plat_panic_handler();
#define assert(X)	if(!(X)){plat_panic_handler();}
