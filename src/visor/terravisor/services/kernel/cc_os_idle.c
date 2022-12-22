#include <terravisor/cc_os/cc_os.h>

void CC_OS_IDLE_TASK(void * args _UNUSED)
{
	while (1)
	{
		cc_os_task_wait(1);
	}
}
