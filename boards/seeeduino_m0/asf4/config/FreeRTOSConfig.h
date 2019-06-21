/* Auto-generated config file FreeRTOSConfig.h */
#ifndef FREERTOSCONFIG_H
#define FREERTOSCONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#if defined(__GNUC__) || defined(__ICCARM__)
/* Important: put #includes here unless they are also meant for the assembler.
 */
#include <stdint.h>
void assert_triggered(const char *file, uint32_t line);
#endif

#include <peripheral_clk_config.h>

// <h> Basic

#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ (CONF_CPU_FREQUENCY)
#endif

// <o> Max Priority for task <5-128>
// <i> Defines the max priority of task
// <i> Default: 5
// <id> freertos_max_priorities
#ifndef configMAX_PRIORITIES
#define configMAX_PRIORITIES (5)
#endif

// <o> Minimal stack size<64-1024>
// <i> Defines minimal number of stack size
// <i> Default: 64
// <id> freertos_minimal_stack_size
#ifndef configMINIMAL_STACK_SIZE
#define configMINIMAL_STACK_SIZE ((uint16_t)64)
#endif

/* configTOTAL_HEAP_SIZE is not used when heap_3.c is used. */
// <o> Heap size<64-1048576:4>
// <i> Defines the heap size(byte) on system
// <i> Default: 2400
// <id> freertos_total_heap_size
#ifndef configTOTAL_HEAP_SIZE
#define configTOTAL_HEAP_SIZE ((size_t)(2400))
#endif

// <q> Enable mutex
// <id> freertos_use_mutexes
#ifndef configUSE_MUTEXES
#define configUSE_MUTEXES 1
#endif

// <q> Enable counting semaphore
// <id> freertos_use_counting_semaphores
#ifndef configUSE_COUNTING_SEMAPHORES
#define configUSE_COUNTING_SEMAPHORES 1
#endif

// </h>

// <e> Advanced
// <id> freertos_advanced
#ifndef FREERTOS_ADVANCED_CONFIG
#define FREERTOS_ADVANCED_CONFIG 0
#endif

// <q> Enable preemption
// <id> freertos_use_preemption
#ifndef configUSE_PREEMPTION
#define configUSE_PREEMPTION 1
#endif

// <q> Use recursive mutex
// <id> freertos_use_recursive_mutexes
#ifndef configUSE_RECURSIVE_MUTEXES
#define configUSE_RECURSIVE_MUTEXES 1
#endif

// <q> Generate runtime stats
// <id> freertos_generate_run_time_stats
#ifndef configGENERATE_RUN_TIME_STATS
#define configGENERATE_RUN_TIME_STATS 0
#endif

// <q> Use 16bit tick
// <id> freertos_use_16_bit_ticks
#ifndef configUSE_16_BIT_TICKS
#define configUSE_16_BIT_TICKS 0
#endif

// <q> Check stack overflow
// <id> freertos_check_for_stack_overflow
#ifndef configCHECK_FOR_STACK_OVERFLOW
#define configCHECK_FOR_STACK_OVERFLOW 0
#endif

// <q> Use maclloc failed hook
// <id> freertos_use_malloc_failed_hook
#ifndef configUSE_MALLOC_FAILED_HOOK
#define configUSE_MALLOC_FAILED_HOOK 0
#endif

// <q> Use idle hook
// <id> freertos_use_idle_hook
#ifndef configUSE_IDLE_HOOK
#define configUSE_IDLE_HOOK 0
#endif

// <q> Use tick hook
// <i> if open, you must realize vApplicationTickHook function
// <id> freertos_use_tick_hook
#ifndef configUSE_TICK_HOOK
#define configUSE_TICK_HOOK 0
#endif

// <q> Use tickless idle
// <id> freertos_use_tickless_idle
#ifndef configUSE_TICKLESS_IDLE
#define configUSE_TICKLESS_IDLE 0
#endif

// <q> Use trace facility
// <id> freertos_use_trace_facility
#ifndef configUSE_TRACE_FACILITY
#define configUSE_TRACE_FACILITY 1
#endif

// <q> Use statistics formating functions
// <id> freertos_use_stats_formatting_functions
#ifndef configUSE_STATS_FORMATTING_FUNCTIONS
#define configUSE_STATS_FORMATTING_FUNCTIONS 1
#endif

// <q> Use port optimised selection functions
// <i> default is not supposed for Cortex-M0
// <id> freertos_use_port_optimised_functions
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#endif

// <q> Use application task tag functions
// <id> freertos_use_application_task_tag_functions
#ifndef configUSE_APPLICATION_TASK_TAG
#define configUSE_APPLICATION_TASK_TAG 0
#endif

// <q> Use co-routines
// <id> freertos_use_co_routines
/* Co-routine definitions. */
#ifndef configUSE_CO_ROUTINES
#define configUSE_CO_ROUTINES 0
#endif

// <o> Co-routine max priority <1-2>
// <i> Default is 2
// <id> freertos_max_co_routine_priorities
#ifndef configMAX_CO_ROUTINE_PRIORITIES
#define configMAX_CO_ROUTINE_PRIORITIES (2)
#endif

// <o> Tick Rate (Hz) <1-1000000>
// <i> Default is 1KHz
// <id> freertos_tick_rate_hz
#ifndef configTICK_RATE_HZ
#define configTICK_RATE_HZ ((TickType_t)1000)
#endif

/* Software timer definitions. */
// <q> Enable timer
// <id> freertos_use_timers
#ifndef configUSE_TIMERS
#define configUSE_TIMERS 1
#endif

// <o> Timer task priority <1-10>
// <i> Default is 2
// <id> freertos_timer_task_priority
#ifndef configTIMER_TASK_PRIORITY
#define configTIMER_TASK_PRIORITY (2)
#endif

#define configTIMER_QUEUE_LENGTH 2

// <o> Timer task stack size <32-512:4>
// <i> Default is 64
// <id> freertos_timer_task_stack_depth
#ifndef TIMER_TASK_STACK_DEPTH
#define configTIMER_TASK_STACK_DEPTH (64)
#endif

#define configPRIO_BITS 3

#define configMAX_TASK_NAME_LEN (8)
#define configIDLE_SHOULD_YIELD 1
#define configQUEUE_REGISTRY_SIZE 0
#define configUSE_QUEUE_SETS 1
#define configENABLE_BACKWARD_COMPATIBILITY 1

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

// <q> Include function to set task priority
// <id> freertos_vtaskpriorityset
#ifndef INCLUDE_vTaskPrioritySet
#define INCLUDE_vTaskPrioritySet 0
#endif

// <q> Include function to get task priority
// <id> freertos_uxtaskpriorityget
#ifndef INCLUDE_uxTaskPriorityGet
#define INCLUDE_uxTaskPriorityGet 0
#endif

// <q> Include function to delete task
// <id> freertos_vtaskdelete
#ifndef INCLUDE_vTaskDelete
#define INCLUDE_vTaskDelete 0
#endif

// <q> Include function to suspend task
// <id> freertos_vtasksuspend
#ifndef INCLUDE_vTaskSuspend
#define INCLUDE_vTaskSuspend 1
#endif

// <q> Include function to resume task from ISR
// <id> freertos_xresumefromisr
#ifndef INCLUDE_xResumeFromISR
#define INCLUDE_xResumeFromISR 0
#endif

// <q> Include task delay utilities
// <id> freertos_vtaskdelayuntil
#ifndef INCLUDE_vTaskDelayUntil
#define INCLUDE_vTaskDelayUntil 0
#endif

// <q> Include task delay function
// <id> freertos_vtaskdelay
#ifndef INCLUDE_vTaskDelay
#define INCLUDE_vTaskDelay 1
#endif

#define INCLUDE_xTaskGetSchedulerState 0

// <q> Include the function to get current task handler
// <id> freertos_xtaskgetcurrenttaskhandle
#ifndef INCLUDE_xTaskGetCurrentTaskHandle
#define INCLUDE_xTaskGetCurrentTaskHandle 0
#endif

#define INCLUDE_uxTaskGetStackHighWaterMark 0

// <q> Include the function to get idle task handler
// <id> freertos_xtaskgetidletaskhandle
#ifndef INCLUDE_xTaskGetIdleTaskHandle
#define INCLUDE_xTaskGetIdleTaskHandle 0
#endif

#define INCLUDE_xTimerGetTimerDaemonTaskHandle 0

// <q> Include the function to get task name
// <id> freertos_pctaskgettaskname
#ifndef INCLUDE_pcTaskGetTaskName
#define INCLUDE_pcTaskGetTaskName 0
#endif

// <q> Include the function to get task state
// <id> freertos_etaskgetstate
#ifndef INCLUDE_eTaskGetState
#define INCLUDE_eTaskGetState 0
#endif

// <q> Include the function to clean task resources
// <id> freertos_vtaskcleanupresources
#ifndef INCLUDE_vTaskCleanUpResources
#define INCLUDE_vTaskCleanUpResources 0
#endif

// <q> Include the function to pend timer call
// <id> freertos_xtimerpendfunctioncall
#ifndef INCLUDE_xTimerPendFunctionCall
#define INCLUDE_xTimerPendFunctionCall 0
#endif

// </e>

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT(x)                                                                                                \
	if ((x) == 0) {                                                                                                    \
		taskDISABLE_INTERRUPTS();                                                                                      \
		for (;;)                                                                                                       \
			;                                                                                                          \
	}

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */

#define vPortSVCHandler SVCall_Handler

#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

/* Used when configGENERATE_RUN_TIME_STATS is 1. */
#if configGENERATE_RUN_TIME_STATS
extern void     vConfigureTimerForRunTimeStats(void);
extern uint32_t vGetRunTimeCounterValue(void);
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() vGetRunTimeCounterValue()
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 0x07

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 4

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

// <<< end of configuration section >>>

#endif // FREERTOSCONFIG_H
