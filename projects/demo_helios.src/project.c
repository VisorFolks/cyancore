/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019 - 2023, Cyancore Team
 *
 * File Name		: project.c
 * Description		: This file consists of project srouces
 * Primary Author	: Pranjal Chanda [pranjalchanda08@gmail.com]
 * Organisation		: Cyancore Core-Team
 */
#include <stdio.h>
#include <driver.h>
#include <terravisor/bootstrap.h>
#include <driver/onboardled.h>
#include <terravisor/helios/helios.h>

#define TASK_WAIT_TICKS		10

void task_handler(helios_args args);

static helios_task_t Task_A;
static helios_task_t Task_B;
static helios_task_t Task_C;

/* Define Plug */
void plug()
{
	bootstrap();
	driver_setup_all();

	syslog(info, "Demo HELIOS!\n");
	helios_add_task(&Task_A, "Task A", &task_handler, NULL, 5, 255, (uintptr_t) NULL);
	helios_add_task(&Task_B, "Task B", &task_handler, NULL, 10, 255, (uintptr_t) NULL);
	helios_add_task(&Task_C, "Task C", &task_handler, NULL, 4, 255, (uintptr_t) NULL);
	helios_run();
}

/* Define Play */
void play()
{
	/* < ! > Play looping code here*/
	return;
}

/* Define the Task Handler */
void task_handler(helios_args args _UNUSED)
{
	while(true)
	{
		printf("In Task: %s\n", helios_get_curr_task_name());
		helios_task_wait(TASK_WAIT_TICKS);
	}
}
