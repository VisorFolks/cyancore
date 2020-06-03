#include <status.h>
#include <platform.h>

_WEAK status_t platform_clk_reset()
{
	return success;
}

_WEAK status_t platform_clk_en(unsigned int id _UNUSED)
{
	return success;
}

_WEAK status_t platform_clk_dis(unsigned int id _UNUSED)
{
	return success;
}
