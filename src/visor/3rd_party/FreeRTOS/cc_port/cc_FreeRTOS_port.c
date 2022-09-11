void cc_FreeRTOS_kernel_init(void)
{
	timer_link_callback(1, vTaskSwitchContext);
}
