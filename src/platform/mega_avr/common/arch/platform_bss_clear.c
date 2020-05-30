#include <stdint.h>
#include <string.h>
#include <status.h>
#include <platform.h>

extern uint16_t _bss_start, _bss_size;

status_t platform_bss_clear()
{
	memset(&_bss_start, 0, (size_t)&_bss_size);
	return success;
}
