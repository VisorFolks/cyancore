#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/cc_os_shed.h>

#if !ccosconfig_CC_OS_USE_DYNAMIC
	cc_shed_tcb_t g_cc_os_tcb_list [ccosconfig_CC_OS_MAX_THREAD];

	cc_shed_tcb_t * g_ready_list_head 	= &(g_cc_os_tcb_list[0]);
	cc_shed_tcb_t * g_curr_task 		= &(g_cc_os_tcb_list[0]);
	cc_shed_tcb_t * g_wait_list_head 	= NULL;
#else
	cc_shed_tcb_t * g_cc_os_tcb_list	= NULL;

	cc_shed_tcb_t * g_ready_list_head 	= NULL;
	cc_shed_tcb_t * g_curr_task 		= NULL;
	cc_shed_tcb_t * g_wait_list_head 	= NULL;
#endif
