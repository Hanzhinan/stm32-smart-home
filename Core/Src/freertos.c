/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for VoiceTask */
osThreadId_t VoiceTaskHandle;
const osThreadAttr_t VoiceTask_attributes = {
  .name = "VoiceTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal5,
};
/* Definitions for DeviceCtrlTask */
osThreadId_t DeviceCtrlTaskHandle;
const osThreadAttr_t DeviceCtrlTask_attributes = {
  .name = "DeviceCtrlTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow4,
};
/* Definitions for SensorCollectTa */
osThreadId_t SensorCollectTaHandle;
const osThreadAttr_t SensorCollectTa_attributes = {
  .name = "SensorCollectTa",
  .stack_size = 384 * 4,
  .priority = (osPriority_t) osPriorityLow3,
};
/* Definitions for AutoLogicTask */
osThreadId_t AutoLogicTaskHandle;
const osThreadAttr_t AutoLogicTask_attributes = {
  .name = "AutoLogicTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow2,
};
/* Definitions for OledDisplayTask */
osThreadId_t OledDisplayTaskHandle;
const osThreadAttr_t OledDisplayTask_attributes = {
  .name = "OledDisplayTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void VoiceTaskEntry(void *argument);
void DeviceCtrlTaskEntry(void *argument);
void SensorCollectTaskEntry(void *argument);
void AutoLogicTaskEntry(void *argument);
void OledDisplayTaskEntry(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of VoiceTask */
  VoiceTaskHandle = osThreadNew(VoiceTaskEntry, NULL, &VoiceTask_attributes);

  /* creation of DeviceCtrlTask */
  DeviceCtrlTaskHandle = osThreadNew(DeviceCtrlTaskEntry, NULL, &DeviceCtrlTask_attributes);

  /* creation of SensorCollectTa */
  SensorCollectTaHandle = osThreadNew(SensorCollectTaskEntry, NULL, &SensorCollectTa_attributes);

  /* creation of AutoLogicTask */
  AutoLogicTaskHandle = osThreadNew(AutoLogicTaskEntry, NULL, &AutoLogicTask_attributes);

  /* creation of OledDisplayTask */
  OledDisplayTaskHandle = osThreadNew(OledDisplayTaskEntry, NULL, &OledDisplayTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_VoiceTaskEntry */
/**
  * @brief  Function implementing the VoiceTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_VoiceTaskEntry */
void VoiceTaskEntry(void *argument)
{
  /* USER CODE BEGIN VoiceTaskEntry */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END VoiceTaskEntry */
}

/* USER CODE BEGIN Header_DeviceCtrlTaskEntry */
/**
* @brief Function implementing the DeviceCtrlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DeviceCtrlTaskEntry */
void DeviceCtrlTaskEntry(void *argument)
{
  /* USER CODE BEGIN DeviceCtrlTaskEntry */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END DeviceCtrlTaskEntry */
}

/* USER CODE BEGIN Header_SensorCollectTaskEntry */
/**
* @brief Function implementing the SensorCollectTa thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SensorCollectTaskEntry */
void SensorCollectTaskEntry(void *argument)
{
  /* USER CODE BEGIN SensorCollectTaskEntry */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END SensorCollectTaskEntry */
}

/* USER CODE BEGIN Header_AutoLogicTaskEntry */
/**
* @brief Function implementing the AutoLogicTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AutoLogicTaskEntry */
void AutoLogicTaskEntry(void *argument)
{
  /* USER CODE BEGIN AutoLogicTaskEntry */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END AutoLogicTaskEntry */
}

/* USER CODE BEGIN Header_OledDisplayTaskEntry */
/**
* @brief Function implementing the OledDisplayTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OledDisplayTaskEntry */
void OledDisplayTaskEntry(void *argument)
{
  /* USER CODE BEGIN OledDisplayTaskEntry */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END OledDisplayTaskEntry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

