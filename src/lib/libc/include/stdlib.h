/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: stdlib.h
 * Description		: This file contains sources of libc-rand
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STDLIB_H_
#include <stdint.h>
#include <stdbool.h>
#include <status.h>

#define EXIT_FAILURE		1
#define EXIT_SUCCESS		0
#define ATEXIT_MAX		1

void abort(void);
int atexit(void (*func)(int));
void exit(int status) _NORETURN;
void *malloc(size_t);
void free(void *);
void *calloc(size_t, size_t);
void *realloc(void *, size_t);
void __heap_status(bool);
size_t heap_usage(void);
double atof(char *);
int atoi(char *);
long atol(char *);

static inline void heap_status(void)
{
	__heap_status(false);
}

static inline void heap_dump(void)
{
	__heap_status(true);
}
