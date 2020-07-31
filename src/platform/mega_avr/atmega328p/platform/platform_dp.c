#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <status.h>
#include <plat_mem.h>
#include <resource.h>
#include <device.h>
#include <machine_call.h>
#include <platform.h>

#ifndef FCLK
#define FCLK 0
WARN(< ! > FCLK is not defined!)
#endif

dp_t device_prop;

status_t platform_dp_setup()
{
	status_t ret;
	memcpy(device_prop.core[0].name, "avr5", 4);
	device_prop.core[0].id = 0x0000;
	device_prop.datawidth = 8;
	device_prop.base_clock = FCLK;

	device_prop.memory.start = 0x00;
	device_prop.memory.size = DMEM_LENGTH;

#if UART0
	device_prop.uart0.id = 0x00;
	device_prop.uart0.baddr = 0xc0;
	device_prop.uart0.clk_id = 0x01;
	device_prop.uart0.stride = 0x06;
	device_prop.uart0.clk = 19200;
	device_prop.uart0.interrupt_id[0] = 18;
	device_prop.uart0.interrupt_id[1] = 20;
	device_prop.uart0.interrupt_trigger[0] = i_level;
	device_prop.uart0.interrupt_trigger[1] = i_level;
#endif

#if GPIO
	device_prop.port[0].baddr = 0x23;
	device_prop.port[0].stride = 3;
	device_prop.port[1].baddr = 0x26;
	device_prop.port[1].stride = 3;
	device_prop.port[2].baddr = 0x29;
	device_prop.port[2].stride = 3;
#endif

	ret = dp_init(&device_prop);

	return ret;
}

mret_t platform_fetch_dp(unsigned int dev, unsigned int a0 _UNUSED)
{
	mret_t ret;
	switch(dev)
	{
		case DEV_CLOCK:
			ret.p = (uintptr_t)dp_get_base_clock();
			ret.size = sizeof(unsigned long);
			ret.status = success;
			break;
#if UART0==1
		case DEV_CONSOLE:
			ret.p = (uintptr_t)dp_get_uart0_info();
			ret.size = sizeof(module_t);
			ret.status = success;
			break;
#endif
#if GPIO==1
		case DEV_GPIO:
			ret.p = (uintptr_t)dp_get_port_info(a0);
			ret.size = sizeof(gpio_module_t);
			ret.status = success;
			break;
#endif
		default:
			ret.p = (uintptr_t)NULL;
			ret.size = 0x00;
			ret.status = error_inval_dev_id;
			break;
	}

	return ret;
}
