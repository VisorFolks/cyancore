#
# CYANCORE LICENSE
# Copyrights (C) 2019, Cyancore Team
#
# File Name		: config.mk
# Description		: This file defines configuration for atmega328p
# Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
# Organisation		: Cyancore Core-Team
#

#======================================================================
# Configuration file for Platforms
#======================================================================

#======================================================================
# Platform Configuration
# Do not alter below FLAGS unless explicitly mentioned
#======================================================================

configUSE_PREEMPTION                    ?= 1
$(eval $(call add_define,configUSE_PREEMPTION))
configUSE_PORT_OPTIMISED_TASK_SELECTION ?= 0
$(eval $(call add_define,configUSE_PORT_OPTIMISED_TASK_SELECTION))
configUSE_TICKLESS_IDLE                 ?= 0
$(eval $(call add_define,configUSE_TICKLESS_IDLE))
configCPU_CLOCK_HZ                      ?= 60000000
$(eval $(call add_define,configCPU_CLOCK_HZ))
configSYSTICK_CLOCK_HZ                  ?= 1000000
$(eval $(call add_define,configSYSTICK_CLOCK_HZ))
configTICK_RATE_HZ                      ?= 250
$(eval $(call add_define,configTICK_RATE_HZ))
configMAX_PRIORITIES                    ?= 5
$(eval $(call add_define,configMAX_PRIORITIES))
configMINIMAL_STACK_SIZE                ?= 128
$(eval $(call add_define,configMINIMAL_STACK_SIZE))
configMAX_TASK_NAME_LEN                 ?= 16
$(eval $(call add_define,configMAX_TASK_NAME_LEN))
configUSE_16_BIT_TICKS                  ?= 0
$(eval $(call add_define,configUSE_16_BIT_TICKS))
configIDLE_SHOULD_YIELD                 ?= 1
$(eval $(call add_define,configIDLE_SHOULD_YIELD))
configUSE_TASK_NOTIFICATIONS            ?= 1
$(eval $(call add_define,configUSE_TASK_NOTIFICATIONS))
configTASK_NOTIFICATION_ARRAY_ENTRIES   ?= 3
$(eval $(call add_define,configTASK_NOTIFICATION_ARRAY_ENTRIES))
configUSE_MUTEXES                       ?= 0
$(eval $(call add_define,configUSE_MUTEXES))
configUSE_RECURSIVE_MUTEXES             ?= 0
$(eval $(call add_define,configUSE_RECURSIVE_MUTEXES))
configUSE_COUNTING_SEMAPHORES           ?= 0
$(eval $(call add_define,configUSE_COUNTING_SEMAPHORES))
configUSE_ALTERNATIVE_API               ?= 0 /* Deprecated! */
$(eval $(call add_define,configUSE_ALTERNATIVE_API))
configQUEUE_REGISTRY_SIZE               ?= 10
$(eval $(call add_define,configQUEUE_REGISTRY_SIZE))
configUSE_QUEUE_SETS                    ?= 0
$(eval $(call add_define,configUSE_QUEUE_SETS))
configUSE_TIME_SLICING                  ?= 0
$(eval $(call add_define,configUSE_TIME_SLICING))
configUSE_NEWLIB_REENTRANT              ?= 0
$(eval $(call add_define,configUSE_NEWLIB_REENTRANT))
configENABLE_BACKWARD_COMPATIBILITY     ?= 0
$(eval $(call add_define,configENABLE_BACKWARD_COMPATIBILITY))
configNUM_THREAD_LOCAL_STORAGE_POINTERS ?= 5
$(eval $(call add_define,configNUM_THREAD_LOCAL_STORAGE_POINTERS))
configSTACK_DEPTH_TYPE                  ?= uint16_t
$(eval $(call add_define,configSTACK_DEPTH_TYPE))
configMESSAGE_BUFFER_LENGTH_TYPE        ?= size_t
$(eval $(call add_define,configMESSAGE_BUFFER_LENGTH_TYPE))

# Memory allocation related definitions.

configSUPPORT_STATIC_ALLOCATION             ?=1
$(eval $(call add_define,configSUPPORT_STATIC_ALLOCATION))
configSUPPORT_DYNAMIC_ALLOCATION            ?=1
$(eval $(call add_define,configSUPPORT_DYNAMIC_ALLOCATION))
configTOTAL_HEAP_SIZE                       ?=10240
$(eval $(call add_define,configAPPLICATION_ALLOCATED_HEAP))
configAPPLICATION_ALLOCATED_HEAP            ?=1
$(eval $(call add_define,configTOTAL_HEAP_SIZE))
configSTACK_ALLOCATION_FROM_SEPARATE_HEAP   ?=1
$(eval $(call add_define,configSTACK_ALLOCATION_FROM_SEPARATE_HEAP))

#  Hook function related definitions.
configUSE_IDLE_HOOK                     ?= 0
$(eval $(call add_define,configUSE_IDLE_HOOK))
configUSE_TICK_HOOK                     ?= 0
$(eval $(call add_define,configUSE_TICK_HOOK))
configCHECK_FOR_STACK_OVERFLOW          ?= 0
$(eval $(call add_define,configCHECK_FOR_STACK_OVERFLOW))
configUSE_MALLOC_FAILED_HOOK            ?= 0
$(eval $(call add_define,configUSE_MALLOC_FAILED_HOOK))
configUSE_DAEMON_TASK_STARTUP_HOOK      ?= 0
$(eval $(call add_define,configUSE_DAEMON_TASK_STARTUP_HOOK))

#  Run time and task stats gathering related definitions.
configGENERATE_RUN_TIME_STATS           ?= 0
$(eval $(call add_define,configGENERATE_RUN_TIME_STATS))
configUSE_TRACE_FACILITY                ?= 0
$(eval $(call add_define,configUSE_TRACE_FACILITY))
configUSE_STATS_FORMATTING_FUNCTIONS    ?= 0
$(eval $(call add_define,configUSE_STATS_FORMATTING_FUNCTIONS))

#  Co-routine related definitions.
configUSE_CO_ROUTINES                   ?= 0
$(eval $(call add_define,configUSE_CO_ROUTINES))
configMAX_CO_ROUTINE_PRIORITIES         ?= 1
$(eval $(call add_define,configMAX_CO_ROUTINE_PRIORITIES))

#  Software timer related definitions.
configUSE_TIMERS                        ?= 1
$(eval $(call add_define,configUSE_TIMERS))
configTIMER_TASK_PRIORITY               ?= 3
$(eval $(call add_define,configTIMER_TASK_PRIORITY))
configTIMER_QUEUE_LENGTH                ?= 10
$(eval $(call add_define,configTIMER_QUEUE_LENGTH))
configTIMER_TASK_STACK_DEPTH            ?= configMINIMAL_STACK_SIZE
$(eval $(call add_define,configTIMER_TASK_STACK_DEPTH))

#  Interrupt nesting behaviour configuration.
configKERNEL_INTERRUPT_PRIORITY         ?= [dependent of processor]
$(eval $(call add_define,configKERNEL_INTERRUPT_PRIORITY))
configMAX_SYSCALL_INTERRUPT_PRIORITY    ?= [dependent on processor and application]
$(eval $(call add_define,configMAX_SYSCALL_INTERRUPT_PRIORITY))
configMAX_API_CALL_INTERRUPT_PRIORITY   ?= [dependent on processor and application]
$(eval $(call add_define,configMAX_API_CALL_INTERRUPT_PRIORITY))

#  Define to trap errors during development.
configASSERT( ( x ) ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )
$(eval $(call add_define,configASSERT( ( x ) ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )))

#  FreeRTOS MPU specific definitions.
configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS ?= 0
$(eval $(call add_define,configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS))
configTOTAL_MPU_REGIONS                                ?= 8 # Default value.
$(eval $(call add_define,configTOTAL_MPU_REGIONS))
configTEX_S_C_B_FLASH                                  ?= 0x07UL # Default value.
$(eval $(call add_define,configTEX_S_C_B_FLASH))
configTEX_S_C_B_SRAM                                   ?= 0x07UL # Default value.
$(eval $(call add_define,configTEX_S_C_B_SRAM))
configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY            ?= 1
$(eval $(call add_define,configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY))
configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS             ?= 1
$(eval $(call add_define,configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS))

#  ARMv8-M secure side port related definitions.
secureconfigMAX_SECURE_CONTEXTS         ?= 5
$(eval $(call add_define,secureconfigMAX_SECURE_CONTEXTS))

#  Optional functions - most linkers will remove unused functions anyway.
INCLUDE_vTaskPrioritySet                ?= 1
$(eval $(call add_define,INCLUDE_vTaskPrioritySet))
INCLUDE_uxTaskPriorityGet               ?= 1
$(eval $(call add_define,INCLUDE_uxTaskPriorityGet))
INCLUDE_vTaskDelete                     ?= 1
$(eval $(call add_define,INCLUDE_vTaskDelete))
INCLUDE_vTaskSuspend                    ?= 1
$(eval $(call add_define,INCLUDE_vTaskSuspend))
INCLUDE_xResumeFromISR                  ?= 1
$(eval $(call add_define,INCLUDE_xResumeFromISR))
INCLUDE_vTaskDelayUntil                 ?= 1
$(eval $(call add_define,INCLUDE_vTaskDelayUntil))
INCLUDE_vTaskDelay                      ?= 1
$(eval $(call add_define,INCLUDE_vTaskDelay))
INCLUDE_xTaskGetSchedulerState          ?= 1
$(eval $(call add_define,INCLUDE_xTaskGetSchedulerState))
INCLUDE_xTaskGetCurrentTaskHandle       ?= 1
$(eval $(call add_define,INCLUDE_xTaskGetCurrentTaskHandle))
INCLUDE_uxTaskGetStackHighWaterMark     ?= 0
$(eval $(call add_define,INCLUDE_uxTaskGetStackHighWaterMark))
INCLUDE_xTaskGetIdleTaskHandle          ?= 0
$(eval $(call add_define,INCLUDE_xTaskGetIdleTaskHandle))
INCLUDE_eTaskGetState                   ?= 0
$(eval $(call add_define,INCLUDE_eTaskGetState))
INCLUDE_xEventGroupSetBitFromISR        ?= 1
$(eval $(call add_define,INCLUDE_xEventGroupSetBitFromISR))
INCLUDE_xTimerPendFunctionCall          ?= 0
$(eval $(call add_define,INCLUDE_xTimerPendFunctionCall))
INCLUDE_xTaskAbortDelay                 ?= 0
$(eval $(call add_define,INCLUDE_xTaskAbortDelay))
INCLUDE_xTaskGetHandle                  ?= 0
$(eval $(call add_define,INCLUDE_xTaskGetHandle))
INCLUDE_xTaskResumeFromISR              ?= 1
$(eval $(call add_define,INCLUDE_xTaskResumeFromISR))
