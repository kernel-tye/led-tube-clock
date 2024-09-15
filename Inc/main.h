/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TM1637_CLK_Pin GPIO_PIN_0
#define TM1637_CLK_GPIO_Port GPIOF
#define TM1637_DIO_Pin GPIO_PIN_1
#define TM1637_DIO_GPIO_Port GPIOF
#define LIGHT_Pin GPIO_PIN_0
#define LIGHT_GPIO_Port GPIOA
#define NTC_Pin GPIO_PIN_1
#define NTC_GPIO_Port GPIOA
#define MODE_KEY_Pin GPIO_PIN_2
#define MODE_KEY_GPIO_Port GPIOA
#define MODE_KEY_EXTI_IRQn EXTI2_3_IRQn
#define SET_KEY_Pin GPIO_PIN_3
#define SET_KEY_GPIO_Port GPIOA
#define SET_KEY_EXTI_IRQn EXTI2_3_IRQn
#define BUZZER_Pin GPIO_PIN_6
#define BUZZER_GPIO_Port GPIOA
#define SEC_INT_Pin GPIO_PIN_1
#define SEC_INT_GPIO_Port GPIOB
#define SEC_INT_EXTI_IRQn EXTI0_1_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
