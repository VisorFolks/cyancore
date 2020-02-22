#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

int amcmp(const void *i, const void *j, size_t size)
{
	int ret = 0;
	const unsigned char *s = i;
	const unsigned char *d = j;
	while(size--)
	{
		ret = (*s++);
		ret -= (*d++);
		if(ret)
			return ret;
	}
	return ret;
}
