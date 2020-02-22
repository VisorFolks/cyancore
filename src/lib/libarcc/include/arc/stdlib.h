#pragma once
#define _STDLIB_H_

#define EXIT_FAILURE		1
#define EXIT_SUCCESS		0
#define _ATEXIT_MAX		1

extern void abort(void);
extern int atexit(void (*func)(void));
extern void exit(int status);

