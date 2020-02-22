#include <arc/stdint.h>
#include <arc/string.h>

int astrncmp(const char *i, const char *j, size_t n)
{
	int ret = 0;
	if(!n)
		return 0;
	do
	{
		if(*i != *j++)
		{
			ret = (*(const unsigned char *)i - *(const unsigned char *)(j - 1));
			break;
		}
		if(*i++ == '\0')
		{
			ret = 0;
			break;
		}
	}
	while(--n);
	return ret;
}
