/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
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
#include <terravisor/cc_os/cc_os.h>

#define TASK_WAIT_TICKS		10

/* Define the Tasks */
CC_TASK_DEF( TASK_A, task_handler, NULL, 10, 100);
CC_TASK_DEF( TASK_B, task_handler, NULL, 10, 100);
CC_TASK_DEF( TASK_C, task_handler, NULL, 10, 100);

/* Define Plug */
void plug()
{
	bootstrap();
	driver_setup_all();

	printf("Demo CC OS Program!\n");
	cc_os_add_task(&CC_GET_TASK_INST(TASK_A));
	cc_os_add_task(&CC_GET_TASK_INST(TASK_B));
	cc_os_add_task(&CC_GET_TASK_INST(TASK_C));
	cc_os_run();
}

/* Define Play */
void play()
{
	/* < ! > Play looping code here*/
	return;
}

/* Define the Task Handler */
void task_handler(os_args args _UNUSED)
{
	while(CC_OS_TRUE)
	{
		printf("In Task: %s\n", cc_os_get_curr_task_name());
		cc_os_task_wait(TASK_WAIT_TICKS);
	}
}
