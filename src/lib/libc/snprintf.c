/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: snprintf.c
 * Description		: This file contains sources of libc-snprintf
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

extern void plat_panic_handler();

static void string_print(char **s, size_t n, size_t *chars_printed,
			 const char *str)
{
	while(*str != '\0')
	{
		if(*chars_printed < n)
		{
			*(*s) = *str;
			(*s)++;
		}
		(*chars_printed)++;
		str++;
	}
}

static void unsigned_dec_print(char **s, size_t n, size_t *chars_printed,
			       unsigned int unum)
{
	char num_buf[10];
	int i = 0;
	unsigned int rem;

	do
	{
		rem = unum % 10U;
		num_buf[i++] = '0' + rem;
		unum /= 10U;
	}
	while(unum > 0U);

	while(--i >= 0)
	{
		if (*chars_printed < n)
		{
			*(*s) = num_buf[i];
			(*s)++;
		}
		(*chars_printed)++;
	}
}

int snprintf(char *s, size_t n, const char *fmt, ...)
{
	va_list args;
	int num;
	unsigned int unum;
	char *str;
	size_t chars_printed = 0U;

	if(n == 1U)
	{
		*s = '\0';
		n = 0U;
	}
	else
	{
		n--;
	}

	va_start(args, fmt);
	while(*fmt != '\0')
	{

		if(*fmt == '%')
		{
			fmt++;
			switch(*fmt)
			{
				case 'i':
				case 'd':
					num = va_arg(args, int);
					if (num < 0)
					{
						if(chars_printed < n)
						{
							*s = '-';
							s++;
						}
						chars_printed++;
						unum = (unsigned int)-num;
					}
					else
					{
						unum = (unsigned int)num;
					}
					unsigned_dec_print(&s, n, &chars_printed, unum);
					break;
				case 's':
					str = va_arg(args, char *);
					string_print(&s, n, &chars_printed, str);
					break;
				case 'u':
					unum = va_arg(args, unsigned int);
					unsigned_dec_print(&s, n, &chars_printed, unum);
					break;
				default:
					plat_panic_handler();
			}
			fmt++;
			continue;
		}

		if(chars_printed < n)
		{
			*s = *fmt;
			s++;
		}

		fmt++;
		chars_printed++;
	}

	va_end(args);

	if(n > 0U)
		*s = '\0';

	return (int)chars_printed;
}
