/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: project.c
 * Description		: This file consists of project srouces
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <terravisor/bootstrap.h>
#include <arch.h>
#include <driver.h>

void plug()
{
	mret_t mres;
	bootstrap();
	driver_setup_all();
	arch_machine_call(0, 100, 200, 300, &mres);
}

void play()
{
	arch_wfi();
}
