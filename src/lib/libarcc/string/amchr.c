#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

void *amchr(const void *i, int r, size_t n)
{
	const unsigned char *src = i;
	while(n--)
	{
		if(*src == (unsigned char)r)
			return (void *)src;
		src++;
	}
	return NULL;
}
