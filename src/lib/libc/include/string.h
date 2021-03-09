/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: string.h
 * Description		: This file contains sources of libc-string
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#define _STRING_H_

#include <stddef.h>

/*
 * Memchr function
 * i = source
 * r = reference
 * n = first n locations
 * ret = source
 */
void *memchr(const void *i, int r, size_t n);

/*
 * Memcmp function
 * i = source 1
 * j = source 2
 * size = number of bytes to be compared
 * ret = i - j
 */
int memcmp(const void *i, const void *j, size_t size);

/*
 * Memcpy function
 * i = destination
 * j = source
 * size = number of bytes to be copied
 * ret = destination
 */
void *memcpy(void *i, const void *j, size_t size);

/*
 * Memmove function
 * i = destination
 * j = source
 * size - number of bytes to be copied
 * ret = destination
 */
void *memmove(void *i, const void *j, size_t size);

/*
 * Memrchr function
 * i = source
 * r = reference
 * n = first n locations
 * ret = source
 */
void *memchr_rev(const void *i, int r, size_t n);

/*
 * Memset function
 * i = pointer
 * n = value
 * size = size to be populated
 * ret = source
 */
void *memset(void *i, int n, size_t size);
/*
 * Strchar fcuntion
 * i = source
 * r = reference
 * ret = pointer of reference char in source
 */
char *strchr(const char *i, int r);

/*
 * Strcmp function
 * i = source 1
 * j = source 2
 * ret = difference
 */
int strcmp(const char *i, const char *j);

/*
 * Strlcpy function
 * i = destination
 * j = source
 * size = size to be copied
 * ret = size copied
 */
size_t strlcpy(char *i, const char *j, size_t size);

/*
 * Strlen function
 * i = source
 * ret = length of string
 */
size_t strlen(const char *i);

/*
 * Strncmp function
 * i = source 1
 * j = source 1
 * n = locations to be compared
 * ret = difference
 */
int strncmp(const char *i, const char *j, size_t n);

/*
 * Strnlen function
 * i = source
 * size = size
 * ret = actual size
 */
size_t strnlen(const char *i, size_t size);

/*
 * Strrchr
 * i = source
 * r = reference
 * ret = pointer to first occurance
 */
char *strchr_rev(const char *i, int r);
