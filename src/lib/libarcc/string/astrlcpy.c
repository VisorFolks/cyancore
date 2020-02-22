#include <arc/stdint.h>
#include <arc/string.h>

size_t astrlcpy(char *i, const char *j, size_t size)
{
	const char *j1 = j;
	size_t end = size;
	if(size)
	{
		while(--size)
		{
			if((*i++ = *j++) == '\0')
				break;
		}
	}
	if(!size)
	{
		if(end)
			*i = '\0';
	}
	return (j - j1 - 1);
}
