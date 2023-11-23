/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: platform.c
 * Description		: This file contains sources for platform apis
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdint.h>
#include <stdlib.h>
#include <arch.h>
#include <syslog.h>
#include <insignia.h>
#include <platform.h>
#include <syslog.h>

uint32_t reset_syndrome;

void platform_early_setup()
{
	status_t ret = success;

	/* Setup platform memories*/
	ret |= platform_copy_data();
	ret |= platform_bss_clear();
	ret |= platform_init_heap();
	ret |= platform_resources_setup();

	/* Setup memory syslogger*/
	driver_setup("mslog");

	reset_syndrome = MMIO32(CHIP_RESET) & 0x01110100;
	MMIO32(CHIP_RESET) = 0;

	ret |= platform_clk_reset();

	if(ret != success)
		exit(EXIT_FAILURE);
	return;
}

#if PRINT_MEMORY_LAYOUT
static void platform_memory_layout()
{
	extern uint32_t _text_start, _text_size, _text_end,
	_data_vstart, _data_size, _data_end,
	_stack_start, _stack_size, _stack_end,
	_bss_start, _bss_size, _bss_end,
	_heap_start, _heap_size, _heap_end,
	_flash_size, _ram_size;

	syslog(info, "Memory Info >\n");
	syslog(info, "Flash Size : %u\n", &_flash_size);
	syslog(info, "RAM Size    : %u\n", &_ram_size);
	syslog(info, "\n");
	syslog(info, "Program Memory Layout >\n");
	syslog(info, "text Region\t: %06p - %06p : Size: %u\n",
			&_text_start, &_text_end, &_text_size);
	syslog(info, "bss Region\t: %06p - %06p : Size: %u\n",
			&_bss_start, &_bss_end, &_bss_size);
	syslog(info, "data Region\t: %06p - %06p : Size: %u\n",
			&_data_vstart, &_data_vend, &_data_size);
	syslog(info, "stack Region\t: %06p - %06p : Size: %u\n",
			&_stack_start, &_stack_end, &_stack_size);
	syslog(info, "heap Region\t: %06p - %06p : Size: %u\n",
			&_heap_start, &_heap_end, &_heap_size);
	syslog(info, "\n");
}
#endif

/**
 * platform_setup - Executes functions to make platform read to init
 *
 * @brief This function performs calls to function which make the
 * framework ready to execute. This function should be made to run on boot core only.
 */
void platform_setup()
{
	sysdbg3("In %s\n", __func__);
	driver_setup("earlycon");
	bootmsgs_enable();
	cyancore_insignia_lite();
#if PRINT_MEMORY_LAYOUT
	platform_memory_layout();
#endif
	return;
}

/**
 * platform_cpu_setup - Perform platform setup calls on all cpus
 *
 * @brief This function performs calls to functions that should be executed
 * on all cores to make the cpu ready for the platform drivers.
 */
void platform_cpu_setup()
{
	sysdbg3("In %s\n", __func__);
	arch_ei();
	return;
}

void _NAKED plat_panic_handler_callback()
{
	context_frame_t *frame;
	sysdbg3("In %s\n", __func__);
	frame = get_context_frame();
	syslog(info, "SP=%p \tSREG = %P\n", frame, frame->sreg);
	exit(EXIT_FAILURE);
}
