/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: rand.c
 * Description		: This file contains sources of libc-rand
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <rand.h>

unsigned int randseed = 0x2923;

void srand(unsigned int seed)
{
	randseed = seed;
}

unsigned int rand()
{
	randseed = (unsigned int)(randseed * 0xa5) + 0x2673;
	return randseed;
}
