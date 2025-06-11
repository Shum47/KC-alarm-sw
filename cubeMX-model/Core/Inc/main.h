/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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
#define k1_pwm3_Pin GPIO_PIN_0
#define k1_pwm3_GPIO_Port GPIOA
#define v_in_mon_Pin GPIO_PIN_1
#define v_in_mon_GPIO_Port GPIOA
#define K1_TX_Pin GPIO_PIN_2
#define K1_TX_GPIO_Port GPIOA
#define K1_RX_Pin GPIO_PIN_3
#define K1_RX_GPIO_Port GPIOA
#define security1_Pin GPIO_PIN_4
#define security1_GPIO_Port GPIOA
#define security2_Pin GPIO_PIN_5
#define security2_GPIO_Port GPIOA
#define security3_Pin GPIO_PIN_6
#define security3_GPIO_Port GPIOA
#define security4_Pin GPIO_PIN_7
#define security4_GPIO_Port GPIOA
#define security5_Pin GPIO_PIN_0
#define security5_GPIO_Port GPIOB
#define security6_Pin GPIO_PIN_1
#define security6_GPIO_Port GPIOB
#define addr_button_Pin GPIO_PIN_13
#define addr_button_GPIO_Port GPIOB
#define k1_pwm1_Pin GPIO_PIN_8
#define k1_pwm1_GPIO_Port GPIOA
#define console_tx_Pin GPIO_PIN_9
#define console_tx_GPIO_Port GPIOA
#define console_rx_Pin GPIO_PIN_10
#define console_rx_GPIO_Port GPIOA
#define k1_pwm2_Pin GPIO_PIN_11
#define k1_pwm2_GPIO_Port GPIOA
#define k1_capture_Pin GPIO_PIN_6
#define k1_capture_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
