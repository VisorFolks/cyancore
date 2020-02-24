#include <arc/stdio.h>
#include <status.h>
#include <driver.h>

extern device_t *_driver_table_start, *_driver_table_end;

void driver_setup_all()
{
	device_t *ptr = _driver_table_start;
	while(ptr <= _driver_table_end)
	{
		if(ptr->driver_setup)
		{
			aprintf("< ! > %s: Loading... ", ptr->name);
			ptr->driver_setup();
			aprintf("Done!\n");
		}
		ptr++;
	}
}

status_t driver_setup(device_t *dev)
{
	dev->driver_setup();
	return success;
}

status_t driver_register(device_t *dev)
{
	dev->driver_setup();
	return success;
}

status_t driver_deregister(device_t *dev)
{
	dev->driver_setup = NULL;
	return success;
}
