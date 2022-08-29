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

int __printf(const char *fmt, ...);
int __eprintf(const char *fmt, ...);
int fputs(const FILE *, const char *);
int fputc(const FILE *, const char);
int fgetc(const FILE *, char *);
char getch();
char getchar();

#ifdef _STDBOOL_H_
int fprintf(const FILE *, bool, const char *fmt, ...);
#ifdef _STDARG_H_
int vprintf(const FILE *, bool, const char *fmt, va_list args);
#endif
#endif

#define printf(fmt, ...)	if(!NOLOGS) __printf(fmt, ##__VA_ARGS__)
#define eprintf(fmt, ...)	if(!NOLOGS) __eprintf(fmt, ##__VA_ARGS__))
