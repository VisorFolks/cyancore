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
void *amchr(const void *i, int r, size_t n);

/*
 * Memcmp function
 * i = source 1
 * j = source 2
 * size = number of bytes to be compared
 * ret = i - j
 */
int amcmp(const void *i, const void *j, size_t size);

/*
 * Memcpy function
 * i = destination
 * j = source
 * size = number of bytes to be copied
 * ret = destination
 */
void *amcpy(void *i, const void *j, size_t size);

/*
 * Memmove function
 * i = destination
 * j = source
 * size - number of bytes to be copied
 * ret = destination
 */
void *ammove(void *i, const void *j, size_t size);

/*
 * Memrchr function
 * i = source
 * r = reference
 * n = first n locations
 * ret = source
 */
void *amrchr(const void *i, int r, size_t n);

/*
 * Memset function
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
 * Strcmp function
 * i = source 1
 * j = source 2
 * ret = difference
 */
int astrcmp(const char *i, const char *j);

/*
 * Strlcpy function
 * i = destination
 * j = source
 * size = size to be copied
 * ret = size copied
 */
size_t astrlcpy(char *i, const char *j, size_t size);

/*
 * Strlen function
 * i = source
 * ret = length of string
 */
size_t astrlen(const char *i);

/*
 * Strncmp function
 * i = source 1
 * j = source 1
 * n = locations to be compared
 * ret = difference
 */
int astrncmp(const char *i, const char *j, size_t n);

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
char *astrrchr(const char *i, int r);
