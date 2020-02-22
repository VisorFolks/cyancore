#pragma once
#define _STDIO_H_

#include <stddef.h>

#define EOF		-1

int aprintf(const char *fmt, ...);
int asnprintf(char *s, size_t n, const char *fmt, ...);
int putch(int c);
int puts(const char *s);

#ifdef _STDARG_H_
int vprintf(const char *fmt, va_list args);
#endif
