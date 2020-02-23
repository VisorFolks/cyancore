#include <arc/assert.h>
#include <arc/stddef.h>
#include <arc/stdarg.h>
#include <arc/stdbool.h>
#include <arc/stdint.h>
#include <arc/stdio.h>
#include <driver/console.h>


#define get_num_va_args(_args, _lcount)			\
	(((_lcount) >= 1)  ? va_arg(_args, long) :	\
			    va_arg(_args, int))

#define get_unum_va_args(_args, _lcount)			\
	(((_lcount) >= 1)  ? va_arg(_args, unsigned long) :	\
			    va_arg(_args, unsigned int))

int putch(int i)
{
	int ret;
	ret = console_putc(i);
	return ret;
}

int puts(const char *i)
{
	int ret;
	ret = console_puts(i);
	return ret;
}

static int unumprint(unsigned long unum, unsigned int radix, char padc, int padn)
{
	char buf[20];
	int i = 0, ret = 0;
	unsigned int rem;
	do
	{
		rem = unum % radix;
		if(rem < 0xa)
			buf[i] = '0' + rem;
		else
			buf[i] = 'a' + (rem - 0xa);
		i++;
		unum /= radix;
	}
	while (unum > 0U);
	if(padn > 0)
	{
		while(i < padn)
		{
			(void)putch((int)padc);
			ret++;
			padn--;
		}
	}
	while(--i >= 0)
	{
		(void)putch((int)buf[i]);
		ret++;
	}
	return ret;
}

int vprintf(const char *fmt, va_list args)
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
						(void)putch((int)'-');
						unum = (unsigned long)-num;
						padn--;
					}
					else
						unum = (unsigned long)num;
					ret += unumprint(unum, 10, padc, padn);
					break;
				case 'c':
					str = va_arg(args, char *);
					ret += putch((int)str);
					break;
				case 's':
					str = va_arg(args, char *);
					ret += puts(str);
					break;
				case 'p':
					unum = (uintptr_t)va_arg(args, void *);
					if (unum > 0U)
					{
						ret += puts("0x");
						padn -= 2;
					}

					ret += unumprint(unum, 16, padc, padn);
					break;
				case 'x':
					unum = get_unum_va_args(args, l_ret);
					ret += unumprint(unum, 16, padc, padn);
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
					ret += unumprint(unum, 10, padc, padn);
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
				default:
					return -1;
			}
			fmt++;
			continue;
		}
		(void)putch((int)*fmt);
		fmt++;
		ret++;
	}
	return ret;
}

int aprintf(const char *fmt, ...)
{
	int ret;
	va_list va;
	va_start(va, fmt);
	ret = vprintf(fmt, va);
	va_end(va);
	return ret;
}
