#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

void *amrchr(const void *i, int r, size_t n)
{
	const unsigned char *src = i + n - 1;
	while(n--)
	{
		if(*src == (unsigned char)r)
			return (void *)src;
		src--;
	}
	return NULL;
}
