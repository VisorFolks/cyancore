/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: call_type.c
 * Description		: This file consists of call_typedef
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once

#if defined(ARCH_ARM_32)
#define __CALL_ARG_TYPE__ unsigned long

#elif defined(ARCH_RISCV_64) || defined(ARCH_ARM_64)
#define __CALL_ARG_TYPE__ unsigned long

#else
#define __CALL_ARG_TYPE__ unsigned int

#endif

typedef __CALL_ARG_TYPE__ call_args;
