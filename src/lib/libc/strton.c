/*
 * CYANCORE LICENSE
 * Copyrights (C) 2023, Cyancore Team
 *
 * File Name		: strton.c
 * Description		: This file contains sources of libc-stdlib
 *			  string/ascii to number functions
 * Primary Author	: Sagar Ladla [sagarladla@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdlib.h>
#include <ctype.h>

#define isSign(c) (c == '-' || c=='+')

/**
 * trail_whitespace
 *
 * @brief This function will trim trailing whitespaces and return resulting string.
*/
static inline char * trail_whitespace(char *s)
{
	while (isSpace(*s))
	{
		s++;
	}
	return s;
}

/**
 * set_negative_flag
 *
 * @brief This function will seg negative flag if found `-` sign.
*/
static inline char * set_negative_flag(char *s, bool *N)
{
	if (*s != '\0' && isSign(*s))
	{
		*N = (*s++ == '-');
	}
	return s;
}

/**
 * integer_traverse
 *
 * @brief This function will parse integral part of number.
*/
static inline char * integer_traverse(char *s, long *a)
{
	while (*s != '\0' && *s != '.' && !isSpace(*s) && isDigit(*s))
	{
		*a = (*a)*10 + (*s++ - '0');
	}
	return s;
}

/**
 * mantissa traverse
 *
 * @brief This function will parse fractional part of number.
*/
static inline char * mantissa_traverse(char *s, double *m, double *e)
{
	if (*s == '.' && isSpace(*s))
	{
		s++;
	}
	while (*s != '\0' && *s != '.' && !isSpace(*s) && isDigit(*s))
	{
		*e *= 0.1;
		*m += *e * (*s++ - '0');
	}
	return s;
}

/**
 * scientific_notation
 *
 * @brief This function will parse scientific notations such as `23e-1`.
*/
static inline char * scientific_notation(char *s, long *a, double *r, double *e)
{
	*a = 0;
	if ((*s == 'e' || *s == 'E') && isSign(s[1]))
	{
		s++;
		if (*s == '-')
		{
			*e = 0.1;
		}
		else if (*s == '+')
		{
			*e = 10;
		}
		s++;
		while (*s != '\0' && !isSpace(*s) && isDigit(*s))
		{
			*a = *a * 10 + (*s++ - '0');
		}
		while ((*a)--)
		{
			*r *= *e;
		}
	}
	return s;
}

/**
 * atof - convert ascii to double
 *
 * @brief This function will parse the string
 * and convert numeric ASCII to its equivalent double.
 * Trim trailing whitespaces, set negative flag if found sign.
 * Calculate integral and fractional part of number.
 * Add both parts to get double result.
*/
double atof(char *s)
{
	long	a = 0;	/* accumulator	 */
	double	r = 0;	/* result	 */
	double	m = 0;	/* mantissa 	 */
	double	e = 1;	/* exponent 	 */
	bool	N = 0;	/* negative flag */

	/**
	 * Trim trailing whitespaces
	*/
	s = trail_whitespace(s);

	/**
	 * Parse and set negative flag if any sign found
	*/
	s = set_negative_flag(s, &N);

	/**
	 * Parse integral part of the number
	*/
	s = integer_traverse(s, &a);

	/**
	 *  Parse fractional part of the number
	 */
	s = mantissa_traverse(s, &m, &e);
	r = (a+m);

	/**
	 * Parse scientific notation of form xe-2 or xe+2
	*/
	s = scientific_notation(s, &a, &r, &e);
	return (N && r != 0.0) ? -r : r;
}

/**
 * atol - convert ascii to long
 *
 * @brief This function will parse the string
 * and convert numeric ascii to its equivalent long value.
*/
long atol(char *s)
{
	long	a = 0;	/* accumulator	 */
	bool	N = 0;	/* negative flag */

	/**
	 * Trim trailing whitespaces
	*/
	s = trail_whitespace(s);

	/**
	 * Parse and set negative flag if any sign found
	*/
	s = set_negative_flag(s, &N);

	/**
	 * Parse integral part of the number
	*/
	s = integer_traverse(s, &a);
	return (N && a != 0) ? -a : a;
}

/**
 * atoi - convert ascii to integer
 *
 * @brief This function calls atol(char *) and type casts to integer.
*/
int atoi(char *s)
{
	return (int)atol(s);
}
