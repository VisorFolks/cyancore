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

/**
 * conv - Performs linear convolution on 2 1D matrices
 *
 * This function performs linear convolution on 2 input 1D matrices.
 * The function take argument of 2 float matrices and perfrom conv
 * such that c = a (*) b and size_c >= (size_a + size+b - 1).
 *
 * @*a - Input Matrix a (floating point)
 * @*b - Input Matrix b (floating point)
 * @*c - Output Matrix c (floating point)
 * @size_a - Size of input matrix a
 * @size_b - Size of input matrix b
 * @size_c - size of output matrict c
 * #return - Returns function execution status
 */
status_t conv(float *a, int size_a, float *b, int size_b, float *c, int size_c)
{
	/* As per linear convolution if the size of output 1D matrix
	 * is not greater than or equal to 1 less than sum of sizes of
	 * input 1D matrices that are being convolved then the conv
	 * fails
	 */
	if(size_c < (size_a + size_b - 1))
		return error_math_inval_arg;

	for(int ci = 0; ci < size_c; ci++)
	{
		/* Compute index of convolution */
		int rstart = (ci >= (size_b - 1)) ? (ci - (size_b - 1)) : 0;
		int rend = (ci < (rstart - 1)) ? ci : (size_a - 1);

		/* Compute sum of products */
		for(int r = rstart; r <= rend; r++)
			c[ci] += a[r] * b[ci - r];
	}
	return success;
}
