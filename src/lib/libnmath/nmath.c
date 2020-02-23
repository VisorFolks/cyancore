#include <nmath.h>

unsigned int clog2(unsigned int num)
{
	return (num > 1) ? (1 + clog2((num % 2) ? ((num + 1) / 2) : (num / 2))) : 0;
}

unsigned long ceiling(unsigned long num, unsigned long den)
{
	return (num % den) ? ((num / den) + 1) : (num / den);
}
