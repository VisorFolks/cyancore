#include <terravisor/cc_os/cc_os_config.h>
#include <terravisor/cc_os/cc_shed.h>

cc_shed_tcb_t g_cc_os_tcb_list [CC_OS_MAX_THREAD];
cc_shed_tcb_t * g_list_head = &(g_cc_os_tcb_list[0]);
cc_shed_tcb_t * g_curr_task = &(g_cc_os_tcb_list[0]);
