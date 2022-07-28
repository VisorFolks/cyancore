/*
 * CYANCORE LICENSE
 * Copyrights (C) 2022, Cyancore Team
 *
 * File Name		: project.c
 * Description		: This file consists of project srouces
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <status.h>
#include <stdio.h>
#include <string.h>
#include <terravisor/bootstrap.h>
#include <driver.h>
#include <driver/onboardled.h>
#include <time.h>

void plug()
{
	bootstrap();
	driver_setup_all();

	printf("Demo Program!\n");
	printf("< ! > Running Blinky ... [");
	return;
}


void play()
{
	char progress[] = "-\\|/";
	static unsigned char i = 0;
	printf("%c]", progress[(i++) % strlen(progress)]);

	onboardled_toggle();

	mdelay(500);

	printf("\b\b");
	return;
}
