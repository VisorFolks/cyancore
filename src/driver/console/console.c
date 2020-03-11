#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <status.h>
#include <driver/console.h>

console_t *con;
bool console_attached = false;

status_t console_attach_device(console_t *pcon)
{
	status_t ret = success;
	console_attached = false;
	con = pcon;
	if(con != NULL)
	{
		console_attached = true;
		ret = con->setup();
	}
	else
		ret = error_inval_arg;
	return ret;
}


status_t console_putc(const char c)
{
	if(console_attached)
		return con->write(c);
	return error_inval_func;
}

status_t console_puts(const char *s)
{
	status_t ret;
	while(*s != '\0')
	{
		ret = console_putc(*s);
		if(ret == error_inval_func)
			return ret;
		s++;
	}
	return success;
}

status_t console_flush()
{
	if(console_attached)
		return con->flush();
	return error_inval_func;
}
