#include <arc.h>
#include <project.h>
#include <arch.h>

void arc()
{
	arch_init();
	project_setup();
	while(1)
	{
		project_loop();
	}
	return;
}
