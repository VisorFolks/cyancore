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

void platform_dp_setup()
{
	memcpy(device_prop.core[0].name, "avr5", 4);
	device_prop.core[0].id = 0x0000;
	device_prop.datawidth = 8;
	device_prop.base_clock = FCLK;
	device_prop.memory.start = 0x00;
	device_prop.memory.size = DMEM_LENGTH;
	device_prop.uart0.id = 0x00;
	device_prop.uart0.baddr = 0xc0;
	device_prop.uart0.clk_id = 0x01;
	device_prop.uart0.stride = 0x06;
	device_prop.uart0.interrupt_id = 19;
	device_prop.uart0.interrupt_trigger = i_level;

	dp_init(&device_prop);

	return;
}

mret_t platform_fetch_dp(unsigned int dev)
{
	mret_t ret;
	switch(dev)
	{
		case DEV_CONSOLE:
			ret.p = (uintptr_t)dp_get_uart0_info();
			ret.size = sizeof(module_t);
			ret.status = success;
			break;
		default:
			ret.p = (uintptr_t)NULL;
			ret.size = 0x00;
			ret.status = error_inval_dev_id;
			break;
	}

	return ret;
}
