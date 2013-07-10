/*
 * mm_sem.c
 *
 *  Created on: Apr 29, 2013
 *      Author: otsaregorodtsev
 */

/* Includes ------------------------------------------------------------------*/
#include <FreeRTOS.h>
#include <task.h>

#include "nuttx/config.h"
#include "nuttx/mm.h"
#include "common.h"

/* Private defines -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions -------------------------------------------------------- */

void mm_seminitialize(FAR struct mm_heap_s *heap)
{
  UNUSED(heap);
}

void mm_takesemaphore(FAR struct mm_heap_s *heap)
{
  UNUSED(heap);
  vTaskSuspendAll();
}

void mm_givesemaphore(FAR struct mm_heap_s *heap)
{
  UNUSED(heap);
  xTaskResumeAll();
}
