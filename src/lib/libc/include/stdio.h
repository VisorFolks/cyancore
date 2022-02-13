/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: stdio.h
 * Description		: This file contains sources of libc-stdio
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STDIO_H_

#include <stddef.h>
#include <stdint.h>
#include <status.h>
#include <ccpfs.h>

#define EOF		-1

typedef ccpdfs_t FILE;

extern FILE stddev[];

#define stdin		&stddev[0]
#define stdout		&stddev[1]
#define stderr		&stddev[2]
#define stdlog		&stddev[3]

int printf(const char *fmt, ...);
int snprintf(char *s, size_t n, const char *fmt, ...);
int putch(int c);
int puts(const char *s);

char getch();
char getchar();

#ifdef _STDARG_H_
int vprintf(const char *fmt, va_list args);
#endif
