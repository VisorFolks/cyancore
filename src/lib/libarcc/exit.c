#include <arc/stdlib.h>
#include <arc/stdbool.h>

static void (*exit_func)(int status);

void exit(int status)
{
	if(exit_func)
		(*exit_func)(status);
	while(true);
}

int atexit(void (*func)(int status))
{
	if(exit_func)
		return -1;
	exit_func = func;
	return 0;
}
