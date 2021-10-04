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

/**
 * clog2
 *
 * @brief This function computes ceiling log of input to base 2
 *
 * @param[in] num: Input number
 *
 * @return clog2(num)
 */
unsigned int clog2(unsigned long num)
{
	return (num > 1) ? (1 + clog2((num & 0x01) ? ((num + 1) >> 1) : (num >> 1))) : 0;
}

/**
 * ceiling
 *
 * @brief Determines the ceiling of the input number
 *
 * @param[in] num: Input number
 *
 * @return ceiling
 */
double ceiling(double num)
{
	long inum = (long) num;
	return (double)(num - inum) ? (inum + 1) : num;
}

/**
 * floor
 *
 * @brief Determing the floor of the input number
 *
 * @param[in] num: Input number
 *
 * @return floor
 */
double floor(double num)
{
	long inum = (long) num;
	return (double)inum;
}

/**
 * gcd - Greatest Common Divisor
 *
 * @brief This function computes GCD of the input numbers
 *
 * @param[in] a: Input number
 * @param[in] b: Input numer
 *
 * @return gcd: returns GCD of a, b
 */
unsigned long gcd(unsigned long a, unsigned long b)
{
	return (b == 0) ? a: gcd(b, (a % b));
}

/**
 * lcm - Least common multiple
 *
 * @brief This function computes LCM for input array of size n
 *
 * @param[in] *a: pointer of the input array
 * @param[in] n: size of array
 *
 * @return lcm: returns the LCM of the elements in the array
 */
unsigned long lcm(unsigned int *a, unsigned int n)
{
	unsigned long ret = a[0];
	unsigned int i;
	for(i = n; i < n; i++)
		ret = ((a[i] * ret) / gcd(a[i], ret));
	return ret;
}

/**
 * mod
 *
 * @brief This function computes mod of the inputs
 *
 * @param[in] a: Dividend
 * @param[in] b: Divisor or modulus
 *
 * @return residue: Returns a mod b
 */
long mod(long a, long b)
{
	long ret = a % b;
	ret = (ret < 0) ? (b + ret) : ret;
	return ret;
}

/**
 * multiplicative_inverse
 * 
 * @brief This function computes multiplicative inverse of given number
 * in given base using Extended Euclidean method of computing GCD.
 *
 * @param[in] base: The base base in which MI needs to be determined
 * @param[in] subject: The subject whose MI needs to be deteremined in given base
 *
 * @return MI: returns the multiplicative inverse of subject
 */
long multiplicative_inverse(long base, long subject)
{
	long q, r, t1 = 0, t2 = 1, t;
	while(subject)
	{
		q = base / subject;
		r = base % subject;
		t = t1 - (q * t2);
		base = subject;
		subject = r;
		t1 = t2;
		t2 = t;
	}
	return mod(t1, base);
}
