#include <stdint.h>
#include <nmath.h>

uint32_t clog2(uint32_t num)
{
	return (num > 1) ? (1 + clog2((num % 2) ? ((num + 1) / 2) : (num / 2))) : 0;
}

uint64_t ceiling(uint32_t num, uint32_t den)
{
	return (num % den) ? ((num / den) + 1) : (num / den);
}
