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
typedef unsigned long call_args;

#elif defined(ARCH_RISCV_64) || defined(ARCH_ARM_64)
typedef unsigned long long call_args;

#else
typedef unsigned int call_args;
#endif
