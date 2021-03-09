/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: nmath.h
 * Description		: This file contains prototypes of neo-math function
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

unsigned int clog2(unsigned long num);

unsigned long ceiling(unsigned long num, unsigned long den);

unsigned long gcd(unsigned long a, unsigned long b);

unsigned long lcd(unsigned int *a, unsigned int n);
