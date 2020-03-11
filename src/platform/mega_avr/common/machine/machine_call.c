#include <stdint.h>
#include <stddef.h>
#include <status.h>
#include <platform.h>
#include <machine_call.h>
#include <mega_avr_platform.h>
#include <dp.h>

void machine_call(unsigned int code, unsigned int a0, unsigned int a1, unsigned int a2, unsigned int *ret, status_t *status)
{
	switch(code)
	{
		case FETCH_DP:
			*status = platform_fetch_dp(a0, ret);
			break;
		default:
			*ret = 0;
			*status = error_inval_code;
			a2 = a1 + a2;
			break;
	}

	return;
}
