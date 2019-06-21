/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */
#include "atmel_start.h"
#include "rtos_start.h"

#define TASK_EXAMPLE_STACK_SIZE (128 / sizeof(portSTACK_TYPE))
#define TASK_EXAMPLE_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
static TaskHandle_t      xCreatedExampleTask;
static SemaphoreHandle_t disp_mutex;

/**
 * OS example task
 *
 * \param[in] p The void pointer for OS task Standard model.
 *
 */
static void example_task(void *p)
{
	(void)p;
	while (1) {
		if (xSemaphoreTake(disp_mutex, ~0)) {
			/* add your code */
			xSemaphoreGive(disp_mutex);
		}
		os_sleep(500);
	}
}

/*
 * Example
 */
void FREERTOS_V1000_0_example(void)
{
	disp_mutex = xSemaphoreCreateMutex();

	if (disp_mutex == NULL) {
		while (1) {
			;
		}
	}

	if (xTaskCreate(
	        example_task, "Example", TASK_EXAMPLE_STACK_SIZE, NULL, TASK_EXAMPLE_STACK_PRIORITY, xCreatedExampleTask)
	    != pdPASS) {
		while (1) {
			;
		}
	}

	vTaskStartScheduler();

	return;
}
