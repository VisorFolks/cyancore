#include <stddef.h>
#include <stdint.h>
#include <status.h>
#include <machine_call.h>
#include <platform.h>

_WEAK status_t platform_dp_setup()
{
	return success;
}

_WEAK mret_t plaform_fetch_dp(unsigned int dev _UNUSED, unsigned int a0 _UNUSED, unsigned int a1 _UNUSED)
{
	mret_t ret;
	ret.p = (uintptr_t)NULL;
	ret.size = 0x00;
	ret.status = error;
	return ret;
}
