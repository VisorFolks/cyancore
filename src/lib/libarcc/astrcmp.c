#include <arc/stddef.h>
#include <arc/stdint.h>
#include <arc/string.h>

int astrcmp(const char *i, const char *j)
{
	while(*i == *j++)
		if(*i++ == '\0')
			return 0;
	return (*(const unsigned char *)i - *(const unsigned char *)(j - 1));
}
