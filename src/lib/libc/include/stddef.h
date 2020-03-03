#pragma once
#define _STDDEF_H_

#ifndef NULL
#define NULL		((void *)0x00)
#endif

#define offsetof(st, m)	__builtin_offsetof(st, m)
