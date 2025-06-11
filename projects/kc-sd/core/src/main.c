/// *****************************************************************************
/// @file           : main.c
/// @brief          : main module for KC-SD (smoke detector)
/// *****************************************************************************
/// created 01.06.2025
/// @author A. Shumilov
/// @attention
/// Copyright 2025 (c) KART CONTROLS
/// All rights reserved.
/// *****************************************************************************

#include "main.h"
#include "adc.h"
#include "buttons.h"
#include "device-config.h"
#include "gpio.h"
#include "i2c.h"
#include "k1-addr.h"
#include "settings.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "wwdg.h"



void SystemClock_Config(void);

int main(void)
{
  static uint32_t counter_short_cycle_ms = 0;

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_WWDG_Init();
  buttons_init();

  // initialize settings
  CRC_HandleTypeDef crc_unit = {CRC, HAL_UNLOCKED, HAL_CRC_STATE_RESET};
  settings_init(&crc_unit);

  // initialize k1 addresses
  for(uint8_t i = 0; i < K1_NUM_OF_ITEMS; ++i)
  {
    k1_addr_set(settings_get_k1_address(i), i);
  }

  while (1)
  {
    // short cycle
    if(HAL_GetTick() >= counter_short_cycle_ms)
    {
      // update counter
      counter_short_cycle_ms = HAL_GetTick() + MAIN_SHORT_CYCLE_PERIOD_MS;
      // update buttons
      buttons_handler();
      // process buttns clicks
      // long push ADDR button - address change
      if(buttons_get_long_push_flags() && (1U << BUTTON_FUNC_ADDR))
      {
        // TBD
      }
      // short push ADDR button - test LEDs
      if(buttons_get_short_push_flags() && (1U << BUTTON_FUNC_ADDR))
      {
        // TBD
      }
    }
    // protection of freezing during 0 crossing for short cycle
    if(HAL_GetTick() < MAIN_SHORT_CYCLE_PERIOD_MS)
    {
      counter_short_cycle_ms = 0;
    }
  }
}


/// @brief System Clock Configuration
/// @retval None
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}


/// @brief  This function is executed in case of error occurrence.
/// @retval None
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
