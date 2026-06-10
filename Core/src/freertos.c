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

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/* freertos.c — generated skeleton, ready for your code */

void SensorTask(void *argument)
{
  /* USER CODE BEGIN SensorTask */
  for(;;)
  {
    /* YOUR SENSOR CODE HERE */
    osDelay(1);
  }
  /* USER CODE END SensorTask */
}

void LedTask(void *argument)
{
  /* USER CODE BEGIN LedTask */
  for(;;)
  {
    /* YOUR LED CODE HERE */
    osDelay(1);
  }
  /* USER CODE END LedTask */
}

void LoggerTask(void *argument)
{
  /* USER CODE BEGIN LoggerTask */
  for(;;)
  {
    /* YOUR LOGGER CODE HERE */
    osDelay(1);
  }
  /* USER CODE END LoggerTask */
}

void WriterTask(void *argument)
{
  /* USER CODE BEGIN WriterTask */
  for(;;)
  {
    /* YOUR WRITER CODE HERE */
    osDelay(1);
  }
  /* USER CODE END WriterTask */
}
