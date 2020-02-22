#pragma once
#define _STDINT_H_

#include <limits.h>

#define INT8_C(x)  x
#define INT16_C(x) x
#define INT32_C(x) x
#define INT64_C(x) x ## LL

#define UINT8_C(x)  x
#define UINT16_C(x) x
#define UINT32_C(x) x ## U
#define UINT64_C(x) x ## ULL

#define INTMAX_C(x)  x ## LL
#define UINTMAX_C(x) x ## ULL

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned int size_t;
typedef unsigned long long uint64_t;

typedef signed char int8_least_t;
typedef short int16_least_t;
typedef int int32_least_t;
typedef long long int64_least_t;

typedef unsigned char uint8_least_t;
typedef unsigned short uint16_least_t;
typedef unsigned int uint32_least_t;
typedef unsigned long long uint64_least_t;

typedef int int8_fast_t;
typedef int int16_fast_t;
typedef int int32_fast_t;
typedef long long int64_fast_t;

typedef unsigned int uint8_fast_t;
typedef unsigned int uint16_fast_t;
typedef unsigned int uint32_fast_t;
typedef unsigned long long uint64_fast_t;

#if ARCH_8
typedef int intptr_t;
typedef unsigned int uintptr_t;
#endif

#if ARCH_16
typedef int intptr_t;
typedef unsigned int uintptr_t;
#endif

#if ARCH_32
typedef long intptr_t;
typedef unsigned long uintptr_t;
#endif

#if ARCH_64
typedef long intptr_t;
typedef unsigned long uintptr_t;
#endif
