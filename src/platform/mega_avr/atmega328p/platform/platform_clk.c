#include <stdint.h>
#include <status.h>
#include <mmio.h>
#include <mega_avr_platform.h>

#define PRR_BADDR	0x64

status_t platform_clk_reset()
{
	MMIO8(PRR_BADDR) = 0xff;
	return success;
}

status_t platform_clk_en(unsigned int id)
{
	if(id >= 8)
		return error_data;
	MMIO8(PRR_BADDR) &= ~(1 << id);
	return success;
}

status_t platform_clk_dis(unsigned int id)
{
	if(id >= 8)
		return error_data;
	MMIO8(PRR_BADDR) |= (1 << id);
	return success;
}
