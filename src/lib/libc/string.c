#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

void *memchr(const void *i, int r, size_t n)
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

int memcmp(const void *i, const void *j, size_t size)
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

void *memcpy(void *i, const void *j, size_t size)
{
	const char *src = j;
	char *dst = i;
	while(size--)
	{
		*dst++ = *src++;
	}
	return i;
}

void *memmove(void *i, const void *j, size_t size)
{
	// Check if the source and destination dont overlap
	if((size_t)i - (size_t)j >= size)
	{
		memcpy(i, j, size);
	}
	/*
	 * If memory overlaps the copying backwards is better idea
	 * For example: two memory locations A and B
	 * A = 1 2 3 4
	 * B = 3 4 5 6
	 * A -> B should follow
	 * 6 <- 4, 5 <- 3, 3 <- 2, 2 <- 1
	 */
	else
	{
		const char *end = i;
		const char *src = (const char *)j + size;
		char *dst = (char *)i + size;
		while(dst != end)
		{
			*--dst = *--src;
		}
	}
	return i;
}

void *memchr_rev(const void *i, int r, size_t n)
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

void *memset(void *i, int n, size_t size)
{
	char *p = i;
	while(size--)
	{
		*p++ = n;
	}
	return i;
}

char *strchr(const char *i, int r)
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

int strcmp(const char *i, const char *j)
{
	while(*i == *j++)
		if(*i++ == '\0')
			return 0;
	return (*(const unsigned char *)i - *(const unsigned char *)(j - 1));
}

size_t strlcpy(char *i, const char *j, size_t size)
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

size_t strlen(const char *i)
{
	const char *p = i;
	while(*p)
		p++;
	return (p - i);
}

int strncmp(const char *i, const char *j, size_t n)
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

size_t strnlen(const char *i, size_t size)
{
	size_t ret;
	for(ret = 0; ret < size; ret++, i++)
	{
		if(!*i)
			break;
	}
	return ret;
}

char *strchr_rev(const char *i, int r)
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
