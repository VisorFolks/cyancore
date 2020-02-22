#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

void *amchr(const void *i, int r, size_t size)
{
	const unsigned char *src = i;
	while(size--)
	{
		if(*src == (unsigned char)r)
			return (void *)src;
		src++;
	}
	return NULL;
}
