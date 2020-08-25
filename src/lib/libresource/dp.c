#include <stdint.h>
#include <status.h>
#include <resource.h>

dp_t *dev_prop;

status_t dp_init(dp_t *plat_dev_prop)
{
	status_t ret;

	if(plat_dev_prop)
	{
		dev_prop = plat_dev_prop;
		ret = success;
	}
	else
		ret = error_inval_arg;
	return ret;
}
