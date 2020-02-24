#pragma once
#define _STRING_H_

#include <stddef.h>

/*
 * Memchr like function
 * i = source
 * r = reference
 * n = first n locations
 * ret = source
 */
void *amchr(const void *i, int r, size_t n);

/*
 * Memcmp like function
 * i = source 1
 * j = source 2
 * size = number of bytes to be compared
 * ret = i - j
 */
int amcmp(const void *i, const void *j, size_t size);

/*
 * Memcpy like function
 * i = destination
 * j = source
 * size = number of bytes to be copied
 * ret = destination
 */
void *amcpy(void *i, const void *j, size_t size);

/*
 * Memmove like function
 * i = destination
 * j = source
 * size - number of bytes to be copied
 * ret = destination
 */
void *ammove(void *i, const void *j, size_t size);

/*
 * Memrchr like function
 * i = source
 * r = reference
 * n = first n locations
 * ret = source
 */
void *amchr_rev(const void *i, int r, size_t n);

/*
 * Memset like function
 * i = pointer
 * n = value
 * size = size to be populated
 * ret = source
 */
void *amset(void *i, int n, size_t size);
/*
 * Strchar fcuntion
 * i = source
 * r = reference
 * ret = pointer of reference char in source
 */
char *astrchr(const char *i, int r);

/*
 * Strcmp like function
 * i = source 1
 * j = source 2
 * ret = difference
 */
int astrcmp(const char *i, const char *j);

/*
 * Strlcpy like function
 * i = destination
 * j = source
 * size = size to be copied
 * ret = size copied
 */
size_t astrlcpy(char *i, const char *j, size_t size);

/*
 * Strlen like function
 * i = source
 * ret = length of string
 */
size_t astrlen(const char *i);

/*
 * Strncmp like function
 * i = source 1
 * j = source 1
 * n = locations to be compared
 * ret = difference
 */
int astrncmp(const char *i, const char *j, size_t n);

/*
 * Strnlen like function
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
char *astrchr_rev(const char *i, int r);
