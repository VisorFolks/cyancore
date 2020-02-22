#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

size_t astrlen(const char *i)
{
	const char *p = i;
	while(*p)
		p++;
	return (p - i);
}
