#include <sp.h>

extern sp_t *sw_prop;

swdev_t *sp_terravisor_dev_info(sw_devid_t devid)
{
	unsigned int i, j, n_devs, n_swdevs;
	n_devs = sw_prop->terravisor->n_dev;
	n_swdevs = sw_prop->n_swdev;
	for(i = 0; i < n_devs; i++)
	{
		if(devid == sw_prop->terravisor->devids[i])
		{
			for(j = 0; j < n_swdevs; j++)
			{
				if(devid == sw_prop->swdev[j]->swdev_id)
					return sw_prop->swdev[j];
			}
		}
	}
	return 0;
}

#if NSEC_HYP == 1
swdev_t *sp_nsec_hypervisor_dev_into(sw_devid_t devid)
{
	unsigned int i, j, n_devs, n_swdevs;
	n_devs = sw_prop->nsec_hypervisor->n_dev;
	n_swdevs = sw_prop->n_swdev;
	for(i = 0; i < n_devs; i++)
	{
		if(devid == sw_prop->nsec_hypervisor->devids[i])
		{
			for(j = 0; j < n_swdevs; j++)
			{
				if(devid == sw_prop->swdev[j]->swdev_id)
					return sw_prop->swdev[j];
			}
		}
	}
	return 0;
}
#endif

#if SEC_HYP == 1
swdev_t *sp_sec_hypervisor_dev_info(sw_devid_t devid)
{
	unsigned int i, j, n_devs, n_swdevs;
	n_devs = sw_prop->sec_hypervisor->n_dev;
	n_swdevs = sw_prop->n_swdev;
	for(i = 0; i < n_devs; i++)
	{
		if(devid == sw_prop->sec_hypervisor->devids[i])
		{
			for(j = 0; j < n_swdevs; j++)
			{
				if(devid == sw_prop->swdev[j]->swdev_id)
					return sw_prop->swdev[j];
			}
		}
	}
	return 0;
}
#endif

#if NSEC_SUP >= 1
swdev_t *sp_nsec_supervisor_dev_info(size_t index, sw_devid_t devid)
{
	unsigned int i, j, n_devs, n_swdevs;
	n_devs = sw_prop->nsec_supervisor[index]->n_dev;
	n_swdevs = sw_prop->n_swdev;
	for(i = 0; i < n_devs; i++)
	{
		if(devid == sw_prop->nsec_supervisor[index]->devids[i])
		{
			for(j = 0; j < n_swdevs; j++)
			{
				if(devid == sw_prop->swdev[j]->swdev_id)
					return sw_prop->swdev[j];
			}
		}
	}
	return 0;
}
#endif

#if SEC_SUP >= 1
swdev_t *sp_sec_supervisor_dev_info(size_t index, sw_devid_t devid)
{
	unsigned int i, j, n_devs, n_swdevs;
	n_devs = sw_prop->sec_supervisor[index]->n_dev;
	n_swdevs = sw_prop->n_swdev;
	for(i = 0; i < n_devs; i++)
	{
		if(devid == sw_prop->sec_supervisor[index]->devids[i])
		{
			for(j = 0; j < n_swdevs; j++)
			{
				if(devid == sw_prop->swdev[j]->swdev_id)
					return sw_prop->swdev[j];
			}
		}
	}
	return 0;
}
#endif
