#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

void *amrchr(const void *i, int r, size_t size)
{
	const unsigned char *src = i + size - 1;
	while(size--)
	{
		if(*src == (unsigned char)r)
			return (void *)src;
		src--;
	}
	return NULL;
}
