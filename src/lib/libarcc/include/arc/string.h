#pragma once
#define _STRING_H_

#include <stddef.h>

/*
 * Memcpy function
 * i = destination
 * j = source
 * size = number of bytes to be copied
 * ret = destination
 */
void *amcpy(void *i, const void *j, size_t size);

//void *memmove(void *dst, const void *src, size_t len);

/*
 * Memcmp function
 * i = source 1
 * j = source 2
 * size = number of bytes to be compared
 * ret = i - j
 */
int amcmp(const void *i, const void *j, size_t size);

//int strcmp(const char *s1, const char *s2);
//int strncmp(const char *s1, const char *s2, size_t n);
//void *memchr(const void *src, int c, size_t len);
//void *memrchr(const void *src, int c, size_t len);
//char *strchr(const char *s, int c);
//void *memset(void *dst, int val, size_t count);
//size_t strlen(const char *s);
//size_t strnlen(const char *s, size_t maxlen);
//char *strrchr(const char *p, int ch);
//size_t strlcpy(char * dst, const char * src, size_t dsize);
