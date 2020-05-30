#include <stdint.h>
#include <status.h>
#include <mmio.h>
#include <plat_arch.h>
#include <platform.h>

status_t platform_clk_reset()
{
	MMIO8(PRR) = 0xff;
	return success;
}

status_t platform_clk_en(unsigned int id)
{
	if(id >= 8)
		return error_data;
	MMIO8(PRR) &= ~(1 << id);
	return success;
}

status_t platform_clk_dis(unsigned int id)
{
	if(id >= 8)
		return error_data;
	MMIO8(PRR) |= (1 << id);
	return success;
}
