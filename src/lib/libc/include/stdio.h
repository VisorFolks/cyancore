#pragma once
#define _STDIO_H_

#include <stddef.h>

#define EOF		-1

int printf(const char *fmt, ...);
int snprintf(char *s, size_t n, const char *fmt, ...);
int putch(int c);
int puts(const char *s);

char getch();
char getchar();

#ifdef _STDARG_H_
int vprintf(const char *fmt, va_list args);
#endif
