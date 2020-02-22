#include <arc/stdint.h>
#include <arc/string.h>

size_t astrnlen(const char *i, size_t size)
{
	size_t ret;
	for(ret = 0; ret < size; ret++, i++)
	{
		if(!*i)
			break;
	}
	return ret;
}
