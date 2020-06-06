#include <stdint.h>
#include <status.h>
#include <dp.h>

extern dp_t *dev_prop;

#if N_PORT
gpio_module_t *dp_get_port_info(uint8_t id)
{
	return &dev_prop->port[id];
}
#endif
