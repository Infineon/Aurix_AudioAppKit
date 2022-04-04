
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION				1
#define configUSE_IDLE_HOOK					0

#define configCPU_CLOCK_HZ					( ( unsigned long ) 300000000UL )
#define configTICK_RATE_HZ					( ( TickType_t ) 1000UL )

#define configMAX_PRIORITIES				( 10 )
#define configMINIMAL_STACK_SIZE			( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE				( ( size_t ) ( 32U * 1024U ) )
#define configMAX_TASK_NAME_LEN				( 32 )

#define configENABLE_BACKWARD_COMPATIBILITY 0
#define configUSE_16_BIT_TICKS				0
#define configIDLE_SHOULD_YIELD				0
#define configUSE_MALLOC_FAILED_HOOK 		0
#define configCHECK_FOR_STACK_OVERFLOW		0
#define configUSE_TICK_HOOK					0
#define configUSE_COUNTING_SEMAPHORES 		1
#define configUSE_RECURSIVE_MUTEXES			1
#define configUSE_MUTEXES					1

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 5

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 				0
#define configMAX_CO_ROUTINE_PRIORITIES 	( 2 )

/* Software timer configuration. */
#define configUSE_TIMERS					(1)
#define configTIMER_TASK_PRIORITY			( 9 )
#define configTIMER_QUEUE_LENGTH			( 5 )
#define configTIMER_TASK_STACK_DEPTH		configMINIMAL_STACK_SIZE

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS           1
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1

/* Set the following definitions to 1 to include the API function, or zero
 to exclude the API function. */
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources			1
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_uxTaskGetStackHighWaterMark     1

/* Interrupt above priority 64 are not effected by critical sections, but cannot call interrupt safe FreeRTOS functions. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY	31 
#define configMAX_API_CALL_INTERRUPT_PRIORITY   31 
#define configKERNEL_INTERRUPT_PRIORITY			1  /* This value must not be changed from 1. */

/* Default definition of configASSERT(). */
#define configASSERT( x ) if( ( x ) == 0 ) 		{ portDISABLE_INTERRUPTS(); TriCore__debug(); vPortLoopForever();}

/* AURIX TCxxx definitions */
#define configAURIX_GENERATION  TRICORE_AURIX_TC3XX
#define configSTM_MODULE        (MODULE_STM0)
#define configSTM_CLOCK_HZ		(configCPU_CLOCK_HZ/3)
#define configSTM_TOS           (0)
#define configCONTEXT_SRC       (SRC_GPSR00)
#define configCONTEXT_TOS       (0)

#endif /* FREERTOS_CONFIG_H */

