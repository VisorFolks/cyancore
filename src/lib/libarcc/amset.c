#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

void *amset(void *i, int n, size_t size)
{
	char *p = i;
	while(size--)
	{
		*p++ = n;
	}
	return i;
}
