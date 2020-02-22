#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>
#include <arc/stdbool.h>

char *astrchr(const char *i, int r)
{
	char *ret = NULL;
	while(true)
	{
		if(*i == (char)r)
		{
			ret = (char *)i;
			break;
		}
		if(*i == '\0')
		{
			ret = NULL;
			break;
		}
		i++;
	}
	return ret;
}
