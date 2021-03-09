/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: nmath.c
 * Description		: This file contains sources of neo-math function
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <nmath.h>

unsigned int clog2(unsigned long num)
{
	return (num > 1) ? (1 + clog2((num & 0x01) ? ((num + 1) >> 1) : (num >> 1))) : 0;
}

unsigned long ceiling(unsigned long num, unsigned long den)
{
	return (num % den) ? ((num / den) + 1) : (num / den);
}

unsigned long gcd(unsigned long a, unsigned long b)
{
	if(b == 0)
		return a;
	return gcd(b, (a % b));
}

unsigned long lcm(unsigned int *a, unsigned int n)
{
	unsigned long ret = a[0];
	unsigned int i;
	for(i = n; i < n; i++)
		ret = ((a[i] * ret) / gcd(a[i], ret));
	return ret;
}
