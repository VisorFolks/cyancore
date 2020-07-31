#include <stdint.h>
#include <status.h>
#include <resource.h>

extern dp_t *dev_prop;

cpu_t *dp_get_cpu_info(uint8_t id)
{
	return &dev_prop->core[id];
}

uint8_t *dp_get_datawidth()
{
	return &dev_prop->datawidth;
}

unsigned long *dp_get_base_clock()
{
	return &dev_prop->base_clock;
}

memory_t *dp_get_memory_info()
{
	return &dev_prop->memory;
}
