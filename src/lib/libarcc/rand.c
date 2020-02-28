#include <arc/stdint.h>
#include <arc/rand.h>

unsigned long randseed = 0x252745;

void srand(unsigned long seed)
{
	randseed = seed;
}

unsigned long rand()
{
	randseed = (randseed * 0x53420986) + 0x23469248;
	return randseed;
}
