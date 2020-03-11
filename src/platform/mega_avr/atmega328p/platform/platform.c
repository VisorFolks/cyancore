#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <status.h>
#include <platform.h>
#include <dp.h>
#include <device.h>
#include <machine_call.h>
#include <mega_avr_platform.h>

dp_t device_prop;

void platform_early_setup()
{
	memcpy(device_prop.core[0].name, "avr", 3);
	device_prop.core[0].id = 0x0000;
	device_prop.datawidth = 8;
	device_prop.base_clock = FCLK;
	device_prop.memory.start = 0x00;
	device_prop.memory.size = DMEM_LENGTH;
	device_prop.uart0.id = 0x00;
	device_prop.uart0.baddr = 0xc0;
	device_prop.uart0.stride = 0x06;
	device_prop.uart0.interrupt_id = 19;
	device_prop.uart0.interrupt_trigger = i_level;

	dp_init(&device_prop);

	return;
}

void platform_setup()
{
	return;
}

void platform_cpu_setup()
{
	return;
}

status_t platform_fetch_dp(unsigned int dev_info, unsigned int *ret)
{
	status_t status = error;
	module_t module;
	switch(dev_info)
	{
		case DEV_CONSOLE_ID:
			module = dp_get_uart0_info();
			*ret = module.id;
			status = success;
			break;
		case DEV_CONSOLE_BADDR:
			module = dp_get_uart0_info();
			*ret = module.baddr;
			status = success;
			break;
		default:
			status = error_inval_dev_id;
			break;
	}

	return status;
}
