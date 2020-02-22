#include <arc/stdint.h>
#include <arc/string.h>

void *ammove(void *i, const void *j, size_t size)
{
	// Check if the source and destination dont overlap
	if((size_t)i - (size_t)j >= size)
	{
		amcpy(i, j, size);
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
