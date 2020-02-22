#include <arc/stddef.h>
#include <arc/stdbool.h>
#include <arc/stdint.h>
#include <arc/string.h>

char *astrrchr(const char *i, int r)
{
	char *ret = NULL;
	while(true)
	{
		if(*i == (char)r)
			ret = (char *)i;
		if(*i == '\0')
			break;
		i++;
	}
	return ret;
}
