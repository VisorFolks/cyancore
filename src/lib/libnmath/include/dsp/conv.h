/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: conv.h
 * Description		: This file contains prototypes of dsp/conv function
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#define conv(x, y, z)	__conv(x, sizeof(x)/sizeof(x[0]), y, sizeof(y)/sizeof(y[0]), z, sizeof(z)/sizeof(z[0]))

status_t __conv(float *a, int size_a, float *b, int size_b, float *c, int size_c);
