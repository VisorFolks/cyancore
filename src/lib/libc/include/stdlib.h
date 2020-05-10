#pragma once
#define _STDLIB_H_

#define EXIT_FAILURE		1
#define EXIT_SUCCESS		0
#define _ATEXIT_MAX		1

void abort(void);
int atexit(void (*func)(int));
void exit(int status);
