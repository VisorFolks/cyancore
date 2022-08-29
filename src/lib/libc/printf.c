/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: printf.c
 * Description		: This file contains sources of libc-printf
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stdint.h>
#include <status.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ccpfs.h>
#include <stdio.h>
#include <lock/lock.h>
#include <driver/console.h>


#define get_num_va_args(_args, _lcount)			\
	(((_lcount) >= 2) ? va_arg(_args, int64_t) :	\
	((_lcount) == 1) ? va_arg(_args, long) :	\
			    va_arg(_args, int))

#define get_unum_va_args(_args, _lcount)			\
	(((_lcount) >= 2) ? va_arg(_args, uint64_t) :		\
	((_lcount) == 1) ? va_arg(_args, unsigned long) :	\
			    va_arg(_args, unsigned int))

static int __fputc(const FILE *dev, bool en_stdout, const char c)
{
	int ret;
	ret = ccpdfs_write(dev, c);
	if(en_stdout)
		ccpdfs_write(stdout, c);
	if((c == '\n') && ((dev == stdout) || (dev == stdlog)))
		__fputc(dev, en_stdout, '\r');
	return ret;
}

static int __fputs(const FILE *dev, bool en_stdout, const char *i)
{
	int ret = 0;
	while(*i != '\0')
	{
		__fputc(dev, en_stdout, *i);
		ret++;
		i++;
	}
	return ret;
}

int fputc(const FILE *dev, const char c)
{
	return __fputc(dev, 0, c);
}

int fputs(const FILE *dev, const char *i)
{
	return __fputs(dev, 0, i);
}

static int unumprint(const FILE *dev, bool en_stdout, unsigned long unum,
		unsigned int radix, char padc, int padn)
{
	char buf[20];
	int i = 0, ret = 0;
	do
	{
		unsigned int rem = unum % radix;
		if(rem < 0xa)
			buf[i] = '0' + (char)rem;
		else
			buf[i] = 'a' + (char)(rem - 0xa);
		i++;
		unum /= radix;
	}
	while (unum > 0U);
	if(padn > 0)
	{
		while(i < padn)
		{
			__fputc(dev, en_stdout, padc);
			ret++;
			padn--;
		}
	}
	while(--i >= 0)
	{
		__fputc(dev, en_stdout, buf[i]);
		ret++;
	}
	return ret;
}

int vprintf(const FILE *dev, bool en_stdout, const char *fmt, va_list args)
{
	int l_ret;
	long num;
	unsigned long unum;
	char *str;
	char padc = '\0';
	int padn;
	int ret = 0;

	while(*fmt != '\0')
	{
		l_ret = 0;
		padn = 0;
		if(*fmt == '%')
		{
			fmt++;
loop:
			switch(*fmt)
			{
				case 'i':
				case 'd':
					num = get_num_va_args(args, l_ret);
					if (num < 0)
					{
						__fputc(dev, en_stdout, '-');
						unum = (unsigned long)-num;
						padn--;
					}
					else
						unum = (unsigned long)num;
					ret += unumprint(dev, en_stdout, unum, 10, padc, padn);
					break;
				case 'c':
					str = va_arg(args, char *);
					ret += __fputc(dev, en_stdout, (int)str);
					break;
				case 's':
					str = va_arg(args, char *);
					ret += __fputs(dev, en_stdout, str);
					break;
				case 'p':
					unum = (uintptr_t) va_arg(args, void *);
					ret += __fputs(dev, en_stdout, "0x");
					padn -= 2;
					ret += unumprint(dev, en_stdout, unum, 16, padc, padn);
					break;
				case 'x':
					unum = get_unum_va_args(args, l_ret);
					ret += unumprint(dev, en_stdout, unum, 16, padc, padn);
					break;
				case 'z':
					if (sizeof(size_t) == 8U)
						l_ret = 2;

					fmt++;
					goto loop;
				case 'l':
					l_ret++;
					fmt++;
					goto loop;
				case 'u':
					unum = get_unum_va_args(args, l_ret);
					ret += unumprint(dev, en_stdout, unum, 10, padc, padn);
					break;
				case '0':
					padc = '0';
					padn = 0;
					fmt++;
					char ch;
					while(true)
					{
						ch = *fmt;
						if((ch < '0') || (ch > '9'))
							goto loop;
						padn = (padn * 10) + (ch - '0');
						fmt++;
					}
				case '%':
					ret += __fputc(dev, en_stdout, *fmt);
					break;
				default:
					return -1;
			}
			fmt++;
			continue;
		}

		__fputc(dev, en_stdout, (char)*fmt);
		fmt++;
		ret++;
	}
	return ret;
}

int __printf(const char *fmt, ...)
{
	int ret;
	va_list va;
	va_start(va, fmt);
	ret = vprintf(stdout, 0, fmt, va);
	va_end(va);
	return ret;
}

int __eprintf(const char *fmt, ...)
{
	int ret;
	va_list va;
	va_start(va, fmt);
	ret = vprintf(stderr, 0, fmt, va);
	va_end(va);
	return ret;
}

int fprintf(const FILE *dev, bool en_stdout, const char *fmt, ...)
{
	int ret;
	va_list va;
	va_start(va, fmt);
	ret = vprintf(dev, en_stdout, fmt, va);
	va_end(va);
	return ret;
}
