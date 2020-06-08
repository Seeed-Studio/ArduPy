/**
 * \file
 *
 * \brief FreeRtos HAL API implementation.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include "hal_rtos.h"

/* Semaphore */

/**
 * \brief Semaphore initialization
 */
int32_t sem_init(sem_t *sem, uint32_t count)
{
	ASSERT(count <= SEMAPHORE_MAX_COUNT);

	*sem = xSemaphoreCreateCounting((uint32_t)SEMAPHORE_MAX_COUNT, count);

	return *sem ? ERR_NONE : ERR_NOT_INITIALIZED;
}

/**
 * \brief Semaphore up
 */
int32_t sem_up(sem_t *sem)
{
	return is_in_isr() ? (xSemaphoreGiveFromISR(*sem, pdFALSE) ? 0 : ERR_ABORTED)
	                   : (xSemaphoreGive(*sem) ? ERR_NONE : ERR_ABORTED);
}

/**
 * \brief Semaphore down, may suspend the caller thread
 */
int32_t sem_down(sem_t *sem, uint32_t timeout)
{
	return xSemaphoreTake(*sem, timeout) ? ERR_NONE : ERR_TIMEOUT;
}

/**
 * \brief Semaphore deinitialization
 */
int32_t sem_deinit(sem_t *sem)
{
	if (*sem != NULL) {
		vSemaphoreDelete(*sem);
		*sem = NULL;
	}

	return ERR_NONE;
}
