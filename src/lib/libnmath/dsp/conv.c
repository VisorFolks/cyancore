/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: conv.c
 * Description		: This file contains sources of convolution
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <dsp/conv.h>

status_t __conv(float *a, int size_a, float *b, int size_b, float *c, int size_c)
{
	/* Selected region variables */
	int rstart, rend, r;

	/* As per linear convolution if the size of output 1D matrix
	 * is not greater than or equal to 1 less than sum of sizes of
	 * input 1D matrices that are being convolved then the conv
	 * fails
	 */
	if(size_c < (size_a + size_b - 1))
		return error_inval_arg;

	for(int ci = 0; ci < size_c; ci++)
	{
		/* Compute index of convolution */
		rstart = (ci >= (size_b - 1)) ? (ci - (size_b - 1)) : 0;
		rend = (ci < (rstart - 1)) ? ci : (size_a - 1);
		
		/* Compute sum of products */
		for(r = rstart; r <= rend; r++)
			c[ci] += a[r] * b[ci - r];
	}
	return success;
}
