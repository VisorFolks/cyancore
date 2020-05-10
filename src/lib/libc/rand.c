#include <stdint.h>
#include <rand.h>

unsigned int randseed = 0x2527;

void srand(unsigned int seed)
{
	randseed = seed;
}

unsigned int rand()
{
	randseed = (randseed * 0x79) + 0x235;
	return randseed;
}
