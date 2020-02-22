#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

void *amcpy(void *i, const void *j, size_t size)
{
	const char *src = j;
	char *dst = i;
	while(size--)
	{
		*dst++ = *src++;
	}
	return i;
}
